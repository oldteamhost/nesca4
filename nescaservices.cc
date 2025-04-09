/*
 * Copyright (c) 2024, oldteam. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "include/nescaservices.h"

#include "include/nescadata.h"
#include "include/nescaengine.h"
#include "libncsnet/ncsnet/socket.h"
#include "libncsnet/ncsnet/http.h"
#include "libncsnet/ncsnet/ftp.h"
#include "libncsnet/ncsnet/utils.h"
#include <bits/types/struct_timeval.h>
#include <cstdio>
#include <map>
#include <sys/select.h>
#include <vector>
#include <string.h>

#define ___VERBOSE							\
	if (ncsdata->opts.check_stats_flag())				\
		std::cout << "NESCASERVICES EXEC " << __FUNCTION__ <<	\
			"()" << std::endl

void NESCAPROCESSINGCORPUS::__exec_check(NESCATARGET *target,
	int port, long long timeout, NESCADATA *ncsdata, size_t num)
{
	if (num>=numchecks)
		return;
	if ((this->checks[num](target,port,timeout,ncsdata)))
		this->checksstate=1;
}

void NESCAPROCESSINGCORPUS::__exec_method(NESCATARGET *target,
	int port, long long timeout, NESCADATA *ncsdata, size_t num)
{
	if (!this->checksstate)
		return;
	if (num>=nummethods)
		return;
	this->methods[num](target,port,timeout,ncsdata);
}

/*
void NESCAPROCESSINGCORPUS::exec(NESCATARGET *target,
	int port, long long timeout, NESCADATA *ncsdata)
{
	size_t i;
	for (i=0;i<numchecks;i++)
		__exec_check(target, port, timeout, ncsdata, i);
	for (i=0;i<nummethods;i++)
		__exec_method(target, port, timeout, ncsdata, i);
}
*/

void NESCAPROCESSINGCORPUS::exec(NESCATARGET *target,
	int port, long long timeout, NESCADATA *ncsdata)
{
	std::vector<std::future<void>>	futures;
	size_t				threads, i;
	bool				methods, all;

	methods=all=0;
	threads=numchecks;
	futures.clear();

_try:
	NESCAPOOL pool(threads);
	if (methods)
		all=1;
	for (i=0;i<threads;i++) {

		if (methods)
			futures.emplace_back(pool.enqueue(std::bind(
				&NESCAPROCESSINGCORPUS::__exec_method, this,
				target, port, timeout, ncsdata, i)));
		else
			futures.emplace_back(pool.enqueue(std::bind(
				&NESCAPROCESSINGCORPUS::__exec_check, this,
				target, port, timeout, ncsdata, i)));

		if (futures.size()>=static_cast<size_t>(threads)) {
			for (auto&future:futures)
				future.get();
			futures.clear();
		}
	}
	for (auto&future:futures)
		future.get();

	if (!all) {
		threads=nummethods;
		methods=1;
		goto _try;
	}
}

std::map<NESCATARGET*, std::vector<int>> forprobe(NESCADATA *ncsdata, int service)
{
	std::map<NESCATARGET*, std::vector<int>>	res;
	std::vector<int>				ports;
	NESCAPORT					p;
	bool						yes;
	size_t						i;

	for (const auto &t:ncsdata->targets) {
		for (i=yes=0;i<t->get_num_port();i++) {
			for (const auto&p:ncsdata->opts.get_s_param()) {
				NESCAPORT pp=t->get_port(i);
				if (pp.port==p.port&&isokport(&pp)
						&&p.proto==service) {
					ports.push_back(pp.port);
					yes=1;
				}
			}
		}
		if (yes) {
			res[t]=ports;
			ports.clear();
		}
	}

	return res;
}

void NESCAPROCESSING::INIT(NESCADATA *ncsdata, int service)
{
	switch (service) {
		case S_HTTP: {
			NESCAPROCESSINGCORPUS http;
			http.setcheck(http_chk_0);
			http.setmethod(http_m_htmlredirtitle);
			this->methods.push_back(http);
			return;
		}
		case S_FTP: {
			NESCAPROCESSINGCORPUS ftp;
			ftp.setcheck(ftp_chk_0);
			this->methods.push_back(ftp);
			return;
		}
	}
}

void NESCAPROCESSING::EXECMETHOD(NESCATARGET *target,
	std::vector<int> ports, NESCADATA *ncsdata)
{
	for (auto&m:this->methods)
		for (const auto&p:ports)
			m.exec(target,p,to_ns(500),ncsdata);
}

void NESCAPROCESSING::EXEC(NESCADATA *ncsdata)
{
	std::vector<std::future<void>>	futures;
	size_t				threads, i;

	threads=this->targets.size();
	futures.clear();
	i=0;

	NESCAPOOL pool(threads);
	for (;i<threads;i++) {
		auto tmp=std::next(targets.begin(), i);
		futures.emplace_back(pool.enqueue(std::bind(
			&NESCAPROCESSING::EXECMETHOD, this,
			tmp->first, tmp->second, ncsdata)));
		if (futures.size()>=static_cast<size_t>(threads)) {
			for (auto&future:futures)
				future.get();
			futures.clear();
		}
	}
	for (auto&future:futures)
		future.get();
}

void NESCAPROCESSING::NULLVARS(void)
{
	this->methods.clear();
	this->targets.clear();
}

NESCAPROCESSING::NESCAPROCESSING(NESCADATA *ncsdata)
{
	size_t i;
	for (i=0;i<S_NUM;i++) {
		(void)NULLVARS();
		this->targets=forprobe(ncsdata,i);
		if (targets.empty())
			continue;
		(void)INIT(ncsdata, i);
		(void)EXEC(ncsdata);
	}
}


/*
 * From old nesca4
 */
#define HTTP_BUFLEN 65535
static std::string clearbuf(const std::string& input)
{
	std::string result;
	result.reserve(input.size());

	for (char ch:input) {
		if (ch=='\t'||ch=='\n')
			result+=' ';
		else if (ch!='\r'&&ch!='\a')
			result+=ch;
	}

	return result;
}
static void prepare_redirect(const char* redirect, char* reshost,
	char* respath, ssize_t buflen)
{
	const char	*ptr, *hostend;
	char		*newurl=NULL;
	bool		aee=false;
	int		len=0;

	if (IS_NULL_OR_EMPTY(redirect))
		redirect="/";
	if (redirect[0]=='.')
		++redirect;

	for (ptr=redirect;*ptr!='\0';++ptr){
		if (*ptr=='/') {
			++len;
			if (len==4) {
				if (*(ptr+1)!='\0')
					aee=true;
				break;
			}
		}
	}
	if (aee) {
		ptr=strstr(redirect, "://");
		if (ptr) {
			ptr+=3;
			hostend=strchr(ptr, '/');
			if (!hostend)
				hostend=ptr+strlen(ptr);
			strncpy(reshost, ptr, hostend-ptr);
			reshost[hostend-ptr]='\0';
			ptr=hostend;

			if (ptr)
				memmove((void*)redirect, ptr, strlen(ptr)+1);
			else
				redirect = "/";
		}
		snprintf(respath, buflen, "%s", redirect);
	}
	else {
		if (find_word(redirect, "http://")==0||find_word(redirect, "https://")==0) {
			newurl=clean_url(redirect);
			if (newurl) {
				strncpy(reshost, newurl, buflen-1);
				reshost[buflen-1]='\0';
			}
			strncpy(respath, "/",	buflen-1);
			respath[buflen-1]='\0';
		}
		else
			if (redirect[0]!='/')
				snprintf(respath, HTTP_BUFLEN, "/%s", redirect);
	}
	if (newurl)
		free(newurl);
}
void send_http(struct http_request *r, NESCADATA *ncsdata, NESCATARGET *target,
		const u16 port, long long timeout)
{
	struct http_response	response;
	u8			resbuf[HTTP_BUFLEN];
	char			redirect[HTTP_BUFLEN];
	u8			newbuf[HTTP_BUFLEN];
	char			respath[HTTP_BUFLEN];
	char			reshost[HTTP_BUFLEN];
	char			title[HTTP_BUFLEN];
	std::string		res, dns;
	struct timeval		s, e;
	size_t			pos;

	dns=ncsdata->rawtargets.getdns(target->get_mainip());
	if (!dns.empty())
		http_add_hdr(r, "Host", dns.c_str());
	else
		http_add_hdr(r, "Host", (target->get_mainip().c_str()));

	gettimeofday(&s, NULL);
	http_qprc_pkt(target->get_mainip().c_str(), port, timeout, r,
		 &response, resbuf, HTTP_BUFLEN);
	res=(char*)resbuf;
	gettimeofday(&e, NULL);

	for (pos=0;pos<target->get_num_port();pos++)
		if (target->get_port(pos).port==port)
			break;

	if (!res.empty())
		target->add_service(target->get_real_port(pos), S_HTTP, s, e);
	http_qprc_redirect(response.hdr, resbuf, redirect, HTTP_BUFLEN);
	if (!std::string(redirect).empty()) {
		target->add_info_service(target->get_real_port(pos),
				S_HTTP, (char*)redirect, "redirect");
		prepare_redirect(redirect, reshost, respath, HTTP_BUFLEN);
		http_update_uri(&r->uri, "", "", 0, respath);
		http_modify_hdr(r, "Host", reshost);
		http_qprc_pkt(target->get_mainip().c_str(), port, timeout,
			 r, &response, newbuf, HTTP_BUFLEN);
		res=std::string((char*)newbuf);
	}
	if (!res.empty()) {
		res=clearbuf(res);
		target->add_info_service(target->get_real_port(pos),
				S_HTTP, res, "html");
		http_qprc_title(res.c_str(), title, sizeof(title));
		if (!std::string(title).empty()&&strcmp(title,"n/a"))
			target->add_info_service(target->get_real_port(pos),
					S_HTTP, title, "title");
	}
	http_free_res(&response);
}

bool http_m_htmlredirtitle(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata)
{
	struct http_request r;

	___VERBOSE;
	http_init_req(&r, "GET", "", "", 0, "/", 0, 0);
	http_add_hdr(&r, "User-Agent", "oldteam");
	http_add_hdr(&r, "Connection", "close");

	send_http(&r, ncsdata, target, port, timeout);

	http_free_req(&r);
	return 1;
}

bool http_chk_0(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata)
{
	___VERBOSE;
	return 1;
}

bool ftp_chk_0(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata)
{
	struct timeval	s, e;
	u8		receive[BUFSIZ];
	std::string	tmp;
	size_t		pos;
	bool		res=0;
	int		ret;

	___VERBOSE;
	gettimeofday(&s, NULL);
	ret=sock_session(target->get_mainip().c_str(), port,
		timeout, receive, sizeof(receive));
	gettimeofday(&e, NULL);
	if (ret<0)
		return res;
	tmp=std::string((char*)receive);
	tmp=clearbuf(tmp);
	res=1;

	for (pos=0;pos<target->get_num_port();pos++)
		if (target->get_port(pos).port==port)
			break;

	/*
	 * Добавляем FTP заголовок, который приходит в сообщении приветствия,
	 * в ответ на подключение. Типа такого, 220 Welcome to Pure-FTPd
	 * 1.0.52 [privsep] [TLS]
	 */
	if (tmp.length()>0) {
		target->add_service(target->get_real_port(pos), S_FTP, s, e);
		target->add_info_service(target->get_real_port(pos),
				S_FTP, tmp, "header");
		target->set_bruteforce(S_FTP, port, "");
	}

	return res;
}
#undef ___VERBOSE
