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

#include "include/nescadata.h"
#include "include/nescaengine.h"
#include "include/nescaprint.h"
#include "libncsnet/ncsnet/cidr.h"
#include "libncsnet/ncsnet/eth.h"
#include "libncsnet/ncsnet/hex.h"
#include "libncsnet/ncsnet/intf.h"
#include "libncsnet/ncsnet/ip.h"
#include "libncsnet/ncsnet/ip4addr.h"
#include "libncsnet/ncsnet/ip6addr.h"

#include "include/nescaprint.h"
#include "libncsnet/ncsnet/linuxread.h"
#include "libncsnet/ncsnet/mac.h"
#include "libncsnet/ncsnet/ncsnet.h"
#include "libncsnet/ncsnet/random.h"
#include "libncsnet/ncsnet/utils.h"
#include <bits/types/struct_timeval.h>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <linux/if_link.h>
#include <net/if.h>
#include <netinet/in.h>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <vector>

struct option longopts[]={
	{"help", 0, 0, IDOPT_HELP},
	{"import", 1, 0, IDOPT_IMPORT},
	{"gmax", 1, 0, IDOPT_GMAX},
	{"gmin", 1, 0, IDOPT_GMIN},
	{"gplus", 1, 0, IDOPT_GPLUS},
	{"pe", 0, 0, IDOPT_PE},
	{"pi", 0, 0, IDOPT_PI},
	{"pm", 0, 0, IDOPT_PM},
	{"ps", 1, 0, IDOPT_PS},
	{"pa", 1, 0, IDOPT_PA},
	{"py", 1, 0, IDOPT_PY},
	{"pu", 1, 0, IDOPT_PU},
	{"dev", 1, 0, IDOPT_DEV},
	{"ip4", 1, 0, IDOPT_IP4},
	{"ip6", 1, 0, IDOPT_IP6},
	{"src", 1, 0, IDOPT_SRC},
	{"dst", 1, 0, IDOPT_DST},
	{"dlen", 1, 0, IDOPT_DLEN},
	{"dhex", 1, 0, IDOPT_DHEX},
	{"dstr", 1, 0, IDOPT_DSTR},
	{"ttl", 1, 0, IDOPT_TTL},
	{"off", 1, 0, IDOPT_OFF},
	{"ipopt", 1, 0, IDOPT_IPOPT},
	{"badsum", 0, 0, IDOPT_BADSUM},
	{"cfg", 1, 0, IDOPT_CFG},
	{"n", 0, 0, IDOPT_N},
	{"n-ping", 0, 0, IDOPT_N_PING},
	{"wait-ping", 1, 0, IDOPT_WAIT_PING},
	{"num-ping", 1, 0, IDOPT_NUM_PING},
	{"pr", 0, 0, IDOPT_PR},
	{"all-ping", 0, 0, IDOPT_ALL_PING},
	{"syn", 0, 0, IDOPT_SYN},
	{"p", 1, 0, IDOPT_P},
	{"sn", 0, 0, IDOPT_SN},
	{"n-scan", 0, 0, IDOPT_SN},
	{"xmas", 0, 0, IDOPT_XMAS},
	{"fin", 0, 0, IDOPT_FIN},
	{"null", 0, 0, IDOPT_NULL},
	{"psh", 0, 0, IDOPT_PSH},
	{"ack", 0, 0, IDOPT_ACK},
	{"window", 0, 0, IDOPT_WINDOW},
	{"maimon", 0, 0, IDOPT_MAIMON},
	{"init", 0, 0, IDOPT_INIT},
	{"cookie", 0, 0, IDOPT_COOKIE},
	{"udp", 0, 0, IDOPT_UDP},
	{"wait-scan", 1, 0, IDOPT_WAIT_SCAN},
	{"mtpl-scan", 1, 0, IDOPT_MTPL_SCAN},
	{"pps", 1, 0, IDOPT_PPS},
	{"stats", 0, 0, IDOPT_STATS},
	{"maxfds", 1, 0, IDOPT_MAXFDS},
	{"all-scan", 0, 0, IDOPT_ALL_SCAN},
	{"num-scan", 1, 0, IDOPT_NUM_SCAN},
	{"random-ip", 1, 0, IDOPT_RADNOM_IP},
	{"detal", 0, 0, IDOPT_DETAL},
	{"v", 0, 0, IDOPT_V},
	{"html", 1, 0, IDOPT_HTML},
	{"win", 1, 0, IDOPT_WIN},
	{"ackn", 1, 0, IDOPT_ACKN},
	{"dbpath", 1, 0, IDOPT_DBPATH},
	{"n-db", 0, 0, IDOPT_N_DB},
	{"n-brute", 0, 0, IDOPT_N_BRUTE},
	{"login", 1, 0, IDOPT_LOGIN},
	{"pass", 1, 0, IDOPT_PASS},
	{"wait-brute", 1, 0, IDOPT_WAIT_BRUTE},
	{"delay-brute", 1, 0, IDOPT_DELAY_BRUTE},
	{"threads-brute", 1, 0, IDOPT_THREADS_BRUTE},
	{"adler32", 0, 0, IDOPT_ADLER32},
	{"onlyopen", 0, 0, IDOPT_ONLYOPEN},
	{"s", 1, 0, IDOPT_S}
};

void NESCAOPTS::opts_init(void)
{
	ncsprint=NULL;
	runcmd="";
	import_param="";
	import_flag=0;
	gmax_param=gmin_param=gplus_param=0;
	gmax_flag=gmin_flag=gplus_flag=0;
	pe_flag=pi_flag=pm_flag=
		ps_flag=pa_flag=py_flag=
		pu_flag=pr_flag=0;
	pa_param.clear();
	ps_param.clear();
	pu_param.clear();
	py_param.clear();
	random_ip_flag=0;
	random_ip_param=0;
	dev_flag=ip4_flag=ip6_flag=src_flag=dst_flag=0;
	dev_param=ip4_param=ip6_param=src_param=dst_param="";
	dlen_flag=dhex_flag=dstr_flag=0;
	dlen_param=dhex_param=dstr_param="";
	ttl_flag=off_flag=ipopt_flag=0;
	ttl_param=off_param=ipopt_param="";
	badsum_flag=0;
	cfg_flag=0;
	cfg_param="";
	n_flag=0;
	n_ping_flag=0;
	wait_ping_flag=0;
	wait_ping_param="";
	num_ping_flag=0;
	num_ping_param="";
	all_ping_flag=0;
	syn_flag=0;
	p_flag=0;
	p_param.clear();
	sn_flag=0;
	xmas_flag=0;
	fin_flag=0;
	null_flag=0;
	psh_flag=0;
	ack_flag=0;
	window_flag=0;
	maimon_flag=0;
	init_flag=0;
	cookie_flag=0;
	udp_flag=0;
	wait_scan_flag=0;
	wait_scan_param="";
	mtpl_scan_flag=0;
	mtpl_scan_param="";
	pps_flag=0;
	pps_param="";
	stats_flag=0;
	maxfds_flag=0;
	maxfds_param="";
	all_scan_flag=0;
	num_scan_flag=0;
	num_scan_param="";
	s_flag=0;
	s_param.clear();
	detal_flag=0;
	v_flag=0;
	html_flag=0;
	html_param="";
	win_flag=0;
	win_param="";
	ackn_flag=0;
	ackn_param="";
	dbpath_flag=0;
	dbpath_param="";
	n_db_flag=0;
	n_brute_flag=0;
	login_flag=0;
	login_param="";
	pass_flag=0;
	pass_param="";
	wait_brute_flag=0;
	wait_brute_param="";
	delay_brute_flag=0;
	delay_brute_param="";
	threads_brute_flag=0;
	threads_brute_param="";
	adler32_flag=0;
	onlyopen_flag=0;
}

static bool is_valid_ipv4(const std::string &txt);
static bool is_valid_ipv6(const std::string &txt);

static std::vector<int> split_string_int(const std::string& str, char del, int max, int min, NESCAPRINT *ncsprint)
{
	std::stringstream	ss(str);
	std::vector<int>	res;
	std::string		token;
	int			ret=0;

	while (std::getline(ss, token, del)) {
		ret=std::stoi(token);
		if (ret>max||ret<min)
			ncsprint->error("here \""+str+"\" out of range ("+
				std::to_string(min)+"-"+std::to_string(max)+")!");
		res.push_back(ret);
	}

	return res;
}

bool NESCATARGET::openports(void)
{
	for (auto&port:this->ports)
		if (isokport(&port))
			return 1;
	return 0;
}

bool NESCATARGET::initservices(void)
{
	for (const auto&port:this->ports)
		for (const auto&s:port.services)
			if (s.init)
				return 1;
	return 0;
}

void NESCATARGET::set_ok(void)
{
	this->ok=1;
}

bool NESCATARGET::isok(void)
{
	return this->ok;
}

bool NESCATARGET::portcompare(NESCAPORT *first, NESCAPORT *second)
{
	if (first->method!=second->method)
		return 0;
	if (first->num!=second->num)
		return 0;
	if (first->port!=second->port)
		return 0;
	if (first->state!=second->state)
		return 0;
	return 1;
}

void NESCATARGET::add_port(int state, int method, int proto, int port)
{
	NESCAPORT p;
	p.state=state;
	p.method=method;
	p.proto=proto;
	p.port=port;
	p.num=0;
	p.services.clear();
	this->ports.push_back(p);
}

NESCAPORT NESCATARGET::get_port(size_t id)
{
	return this->ports.at(id);
}

NESCAPORT *NESCATARGET::get_real_port(size_t id)
{
	return &this->ports.at(id);
}

void NESCATARGET::add_service(NESCAPORT *port, int service,
	struct timeval tstamp1, struct timeval tstamp2)
{
	NESCASERVICE res={};

	res.rtt.tstamp1=tstamp1;
	res.rtt.tstamp2=tstamp2;
	res.service=service;
	res.info.clear();
	res.init=1;

	port->services.push_back(res);
}

void NESCATARGET::add_dbres(const std::string &info, const std::string &find)
{
	NESCADBRES res;
	if (info.empty())
		return;
	res.info=info;
	res.find=find;
	this->dbresults.push_back(res);
}

size_t NESCATARGET::get_num_dbres(void)
{
	return this->dbresults.size();
}

NESCADBRES NESCATARGET::get_dbres(size_t id)
{
	if (id<=this->dbresults.size())
		return this->dbresults.at(id);
	return {};
}

void NESCATARGET::add_info_service(NESCAPORT *port, int service,
		const std::string &info, const std::string type)
{
	NESCASERVICE *_service=nullptr;
	NESCAINFO i={};

	for (auto /* dont touch & */&s:port->services)
		if (s.service==service)
			_service=&s;
	if (!_service)
		return;

	i.info=info;
	i.type=type;
	_service->info.push_back(i);
}

void NESCATARGET::set_bruteforce(int service, int port, const std::string &other)
{
	NESCABRUTEI i;
	i.other=other;
	i.service=service;
	i.port=port;
	this->bruteforce.push_back(i);
}

NESCABRUTEI NESCATARGET::get_bruteforce(size_t id)
{
	if (id>bruteforce.size())
		return {};
	return this->bruteforce.at(id);
}

size_t NESCATARGET::get_num_bruteforce(void)
{
	return this->bruteforce.size();
}

NESCASERVICE NESCATARGET::get_service(NESCAPORT *port, int service)
{
	for (auto &s:port->services)
		if (s.service==service)
			return s;
	return {};
}

bool NESCATARGET::check_service(void)
{
	for (const auto&p:this->ports)
		if (!p.services.empty())
			return 1;
	return 0;
}


size_t NESCATARGET::get_num_port(void)
{
	return this->ports.size();
}

void NESCATARGET::removedublports(void)
{
	std::unordered_map<int, int> portnum;
	std::vector<NESCAPORT> unique;

	for (const auto&p:this->ports)
		portnum[p.port]++;
	for (auto&p:ports) {
		if (portnum[p.port]>0) {
			p.num=portnum[p.port];
			unique.push_back(p);
			portnum[p.port]=0;
		}
	}

	this->ports=std::move(unique);
}

void NESCATARGET::add_ip(const std::string &ip)
{
	if (!ip.empty()) {
		if (mainip.empty()) {
			if (is_valid_ipv4(ip))
				this->ip6=0;
			else if (is_valid_ipv6(ip))
				this->ip6=1;
			this->mainip=ip;
		}
		else
			this->ips.push_back(ip);
	}
}

void NESCATARGET::add_mac(const std::string &mac)
{
	this->mac=mac;
}

std::string NESCATARGET::get_mac(void)
{
	return this->mac;
}

void NESCATARGET::set_no_ok(void)
{
	this->ok=0;
}

bool NESCATARGET::is_ip6host(void)
{
	return this->ip6;
}

void NESCATARGET::add_dns(const std::string &dns)
{
	if (!dns.empty())
		this->dns.push_back(dns);
}

void NESCATARGET::add_time(struct timeval tstamp1, struct timeval tstamp2, int type)
{
	NESCATIME res;
	res.tstamp1=tstamp1;
	res.tstamp2=tstamp2;
	res.type=type;
	this->rtts.push_back(res);
}

long long NESCATARGET::get_time_ns(size_t id)
{
	NESCATIME tmp;
	if (id>get_num_time())
		return 0;
	tmp=this->rtts.at(id);
	return ((tmp.tstamp2.tv_sec*1000000000LL+tmp.tstamp2.tv_usec*1000LL)-
		(tmp.tstamp1.tv_sec*1000000000LL+tmp.tstamp1.tv_usec*1000LL));
}

NESCATIME NESCATARGET::get_time(size_t id)
{
	NESCATIME tmp;
	if (id>get_num_time())
		return {};
	tmp=this->rtts.at(id);
	return tmp;
}

size_t NESCATARGET::get_type_time(size_t id)
{
	NESCATIME tmp;
	if (id>get_num_time())
		return 0;
	tmp=this->rtts.at(id);
	return tmp.type;
}

size_t NESCATARGET::get_num_time(void)
{
	return this->rtts.size();
}

void NESCADATA::clear_targets(void)
{
	for (auto t:targets)
		delete t;
	this->targets.clear();
}

std::vector<NESCATARGET*> NESCADATA::get_oktargets(void)
{
	std::vector<NESCATARGET*> res;
	for (const auto&t:targets)
		if (t->isok())
			res.push_back(t);
	return res;
}

void NESCADATA::add_target(const std::string &ip)
{
	NESCATARGET *target = new NESCATARGET;
	target->add_ip(ip);
	this->targets.push_back(target);
}

void NESCADATA::set_all_targets_ok(void)
{
	for (const auto&t:targets)
		t->set_ok();
}

size_t NESCATARGET::get_num_ip(void)
{
	size_t ret;
	ret=this->ips.size();
	return ret;
}

size_t NESCATARGET::get_num_dns(void)
{
	size_t ret;
	ret=this->dns.size();
	return ret;
}

std::string NESCATARGET::get_mainip(void)
{
	if (this->mainip.empty())
		return "";
	return this->mainip;
}

std::string NESCATARGET::get_ip(size_t id)
{
	if (id>get_num_ip())
		return "";
	return (this->ips[id]);
}

std::string NESCATARGET::get_dns(size_t id)
{
	if (id>get_num_dns())
		return "";
	return this->dns[id];
}


/*
 * Clear string from spaces, tabs, newlines, and etc.
 */
static std::string trim(const std::string& str)
{
	auto is_not_space=[](u8 ch) { return !std::isspace(ch); };
	auto start=std::find_if(str.begin(), str.end(), is_not_space);
	auto end=std::find_if(str.rbegin(), str.rend(), is_not_space).base();
	return (start<end)?std::string(start, end):std::string();
}


/*
 * Apply option by id
 */
void NESCAOPTS::opts_apply(int rez, std::string val)
{
	switch (rez) {
		case IDOPT_IMPORT:    set_import_flag();     set_import_param(val);                   break;
		case IDOPT_GMAX:      set_gmax_flag();       set_gmax_param(atoll(val.c_str()));      break;
		case IDOPT_GMIN:      set_gmin_flag();       set_gmin_param(atoll(val.c_str()));      break;
		case IDOPT_GPLUS:     set_gplus_flag();      set_gplus_param(atoll(val.c_str()));     break;
		case IDOPT_PE:        set_pe_flag();                                                  break;
		case IDOPT_PI:        set_pi_flag();                                                  break;
		case IDOPT_PM:        set_pm_flag();                                                  break;
		case IDOPT_PS:        set_ps_flag();         set_ps_param(val);                       break;
		case IDOPT_PA:        set_pa_flag();         set_pa_param(val);                       break;
		case IDOPT_PY:        set_py_flag();         set_py_param(val);                       break;
		case IDOPT_PU:        set_pu_flag();         set_pu_param(val);                       break;
		case IDOPT_RADNOM_IP: set_random_ip_flag();  set_random_ip_param(atoll(val.c_str())); break;
		case IDOPT_DEV:       set_dev_flag();        set_dev_param(val);                      break;
		case IDOPT_IP4:       set_ip4_flag();        set_ip4_param(val);                      break;
		case IDOPT_IP6:       set_ip6_flag();        set_ip6_param(val);                      break;
		case IDOPT_SRC:       set_src_flag();        set_src_param(val);                      break;
		case IDOPT_DST:       set_dst_flag();        set_dst_param(val);                      break;
		case IDOPT_DLEN:      set_dlen_flag();       set_dlen_param(val);                     break;
		case IDOPT_DHEX:      set_dhex_flag();       set_dhex_param(val);                     break;
		case IDOPT_DSTR:      set_dstr_flag();       set_dstr_param(val);                     break;
		case IDOPT_TTL:       set_ttl_flag();        set_ttl_param(val);                      break;
		case IDOPT_OFF:       set_off_flag();        set_off_param(val);                      break;
		case IDOPT_IPOPT:     set_ipopt_flag();      set_ipopt_param(val);                    break;
		case IDOPT_BADSUM:    set_badsum_flag();                                              break;
		case IDOPT_CFG:       set_cfg_flag();        set_cfg_param(val);                      break;
		case IDOPT_N:         set_n_flag();                                                   break;
		case IDOPT_N_PING:    set_n_ping_flag();                                              break;
		case IDOPT_WAIT_PING: set_wait_ping_flag();  set_wait_ping_param(val);                break;
		case IDOPT_NUM_PING:  set_num_ping_flag();   set_num_ping_param(val);                 break;
		case IDOPT_PR:        set_pr_flag();                                                  break;
		case IDOPT_ALL_PING:  set_all_ping_flag();                                            break;
		case IDOPT_SYN:       set_syn_flag();                                                 break;
		case IDOPT_P:         set_p_flag();          set_p_param(val);                        break;
		case IDOPT_SN:        set_sn_flag();                                                  break;
		case IDOPT_XMAS:      set_xmas_flag();                                                break;
		case IDOPT_FIN:       set_fin_flag();                                                 break;
		case IDOPT_NULL:      set_null_flag();                                                break;
		case IDOPT_PSH:       set_psh_flag();                                                 break;
		case IDOPT_ACK:       set_ack_flag();                                                 break;
		case IDOPT_WINDOW:    set_window_flag();                                              break;
		case IDOPT_MAIMON:    set_maimon_flag();                                              break;
		case IDOPT_INIT:      set_init_flag();                                                break;
		case IDOPT_COOKIE:    set_cookie_flag();                                              break;
		case IDOPT_UDP:       set_udp_flag();                                                 break;
		case IDOPT_WAIT_SCAN: set_wait_scan_flag();  set_wait_scan_param(val);                break;
		case IDOPT_MTPL_SCAN: set_mtpl_scan_flag();  set_mtpl_scan_param(val);                break;
		case IDOPT_PPS:       set_pps_flag();        set_pps_param(val);                      break;
		case IDOPT_STATS:     set_stats_flag();                                               break;
		case IDOPT_MAXFDS:    set_maxfds_flag();     set_maxfds_param(val);                   break;
		case IDOPT_ALL_SCAN:  set_all_scan_flag();                                            break;
		case IDOPT_NUM_SCAN:  set_num_scan_flag();   set_num_scan_param(val);                 break;
		case IDOPT_S:         set_s_flag();          set_s_param(val);                        break;
		case IDOPT_DETAL:     set_detal_flag();                                               break;
		case IDOPT_V:         set_v_flag();                                                   break;
		case IDOPT_HTML:      set_html_flag();       set_html_param(val);                     break;
		case IDOPT_WIN:       set_win_flag();        set_win_param(val);                      break;
		case IDOPT_ACKN:      set_ackn_flag();       set_ackn_param(val);                     break;
		case IDOPT_DBPATH:    set_dbpath_flag();     set_dbpath_param(val);                   break;
		case IDOPT_N_DB:      set_n_db_flag();                                                break;
		case IDOPT_N_BRUTE:   set_n_brute_flag();                                             break;
		case IDOPT_LOGIN:     set_login_flag();      set_login_param(val);                    break;
		case IDOPT_PASS:      set_pass_flag();       set_pass_param(val);                     break;
		case IDOPT_WAIT_BRUTE: set_wait_brute_flag();      set_wait_brute_param(val);         break;
		case IDOPT_DELAY_BRUTE: set_delay_brute_flag();       set_delay_brute_param(val);     break;
		case IDOPT_THREADS_BRUTE: set_threads_brute_flag(); set_threads_brute_param(val);     break;
		case IDOPT_ADLER32:   set_adler32_flag();                                             break;
		case IDOPT_ONLYOPEN:   set_onlyopen_flag();                                           break;
	}
}


/*
 * Parse arguments and apply options of which.
 */
void NESCAOPTS::args_apply(int argc, char **argv, NESCADATA *ncsdata, NESCAPRINT *ncsprint)
{
	int rez, index=0, i;

	for (i=0;i<argc;i++) {
		this->runcmd+=argv[i];
		this->runcmd+=" ";
	}
	this->runcmd.pop_back();

	this->ncsprint=ncsprint;
	while ((rez=getopt_long_only(argc, argv, "", longopts, &index))!=-1) {
		if (rez==IDOPT_HELP) ncsprint->usage(argc, argv);
		else opts_apply(rez, (optarg)?optarg:"");
	}
}


/*
 * Processing escape special symbols
 * \; \' \= \\, if only \, skip he.
 */
static std::string escape(const std::string& input)
{
	std::string	output=input;
	size_t		pos=0;

	while ((pos=output.find("\\\\", pos))!=std::string::npos) {
		output.replace(pos, 2, "\\");
		pos++;
	}
	pos=0;
	while ((pos=output.find("\\'", pos))!=std::string::npos) {
		output.replace(pos, 2, "'");
		pos++;
	}
	pos=0;
	while ((pos=output.find("\\=", pos))!=std::string::npos) {
		output.replace(pos, 2, "=");
		pos++;
	}
	pos=0;
	while ((pos=output.find("\\;", pos))!=std::string::npos) {
		output.replace(pos, 2, ";");
		pos++;
	}
	pos=0;
	while ((pos=output.find("\\'", pos))!=std::string::npos) {
		output.erase(pos, 2);
		pos++;
	}

	return output;
}


/*
 * Input "config/default.cfg"
 * Output "config/"
 */
static std::string removelastpath(const std::string &path)
{
	size_t found=path.find_last_of("/\\");
	if (found!=std::string::npos)
		return path.substr(0, found+1);
	return path;
}


/*
 * Parses a line like this 'name'=val; into _cfgopt
 * structure, if an error occurs, saves in errbuf,
 * special characters \' \; \\\ \\= are not
 * considered as tokens.
 */
bool NESCAOPTS::parse_cfgopt(std::string line, struct _cfgopt *res, char *errbuf)
{
	bool	inside=0, escapenxt=0, end=0, equal=0;
	size_t	quotes=0, i=0;
	u8	c;

	res->nullval=0;
	res->name=res->val="";

	/* getting number quotes */
	for (i=0;i<line.length();++i)
		if (line[i]==OPENCLOSEOPT&&line[(i-1)]!=SPECOPT)
			quotes++;

	/* miss (')name'=val; */
	if (line[0]!=OPENCLOSEOPT) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing an opening quote (')! %s",
			line.c_str());
		return false;
	}

	/* miss 'name(')=val; */
	if (quotes!=2) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing an close quote or semicolon (') or (;)! %s",
			line.c_str());
		return false;
	}

	/* parse name opt */
	for (i=0;i<line.length();++i) {
		c=(char)line[i];
		if (escapenxt) {
			res->name+=c;
			escapenxt=0;
			continue;
		}

		/*
		 * find special symbol
		 * \'
		 */
		if (c==SPECOPT) {
			escapenxt=1;
			continue;
		}

		if (c==OPENCLOSEOPT&&!inside)
			inside=1;
		else if (c==OPENCLOSEOPT&&inside) {
			inside=0;
			break;
		}
		else if (inside)
			res->name+=c;
	}

	/* miss '(name)'=val; */
	if (res->name.length()<=0) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing name! %s",
			line.c_str());
		return false;
	}

	/* find (=) symbol ignore (\=) */
	while (line[i]!='\0')	{
		if (line[i]==ASSIGNMENTVAL&&line[i-1]!=SPECOPT) {
			equal=1;
			break;
		}
		i++;
	}
	/* miss 'name'(=)val; */
	if (!equal) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing equal sign (=)! %s",
			line.c_str());
		return false;
	}
	i++; /* nxt symbol after = */

	/* find (;) ignore (\;) */
	for (;i<line.length();++i) {
		if (line[i]==ENDOPT&&line[i-1]!=SPECOPT) {
			end=1;
			break;
		}
		res->val+=line[i];
	}

	/* miss 'name'=val(;) */
	if (!end) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing semicolon (;)! %s",
			line.c_str());
		return false;
	}

	/* miss 'name'=(val);*/
	if (res->val.length()<=0) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing value! %s",
			line.c_str());
		return false;
	}

	/* apply espace \; \' \\ \= */
	res->val=escape(res->val);
	res->name=escape(res->name);

	res->id=-1;
	if (res->name==INCLUDE_TOKEN)
		return true;

	/* find id name */
	for (const auto&o:longopts) {
		if (res->name==std::string(o.name)) {
			if (o.has_arg==0)
				res->nullval=1;
			res->id=o.val;
		}
	}

	if (res->id==-1) {
		snprintf(errbuf, _ERRBUFMAXLEN, "option not found! %s",
			res->name.c_str());
		return false;
	}

	return true;
}


/*
 * Parses and stores in opts, options from the specified
 * lines of the file, also applies a preprocessor,
 * if so, can be called recursively. Before parsing, it
 * clears the line from spaces \n \t etc. Also, for
 * parsing, replaces all \; with \1, and back again
 * after parsing.
 */
bool NESCAOPTS::parse_cfg(std::vector<std::string> file, char *errbuf)
{
	std::vector<std::string>	res;
	std::string			item, tmp, tmp1;
	size_t				i=0, pos=0;

	/* remove \n \t and etc. */
	for (auto&l:file) {
		l.erase(std::remove_if(l.begin(), l.end(), [](u8 c) {
			return std::isspace(c);
		}),l.end());
		if (!l.empty())
			tmp+=l;
	}

	/* check last semicolon on last line */
	if ((tmp.back()!=ENDOPT)||(tmp.back()==ENDOPT&&tmp[tmp.length()-2]==SPECOPT)) {
		snprintf(errbuf, _ERRBUFMAXLEN, "missing semicolon (;)! %s",
			tmp.c_str());
		return 0;
	}

	/* replace all \; on \1 */
	for (;i<tmp.length();++i)
		if (tmp[i]==ENDOPT&&tmp[i-1]==SPECOPT)
			tmp[i]='\1';

	/* parse result in vector */
	std::stringstream ss(tmp);
	while (std::getline(ss, item, ENDOPT))
		if (!item.empty())
			res.push_back(item+ENDOPT);

	/* return all \;, replace \1 on \; */
	for (auto&str:res) {
		pos=str.find('\1');
		while (pos!=std::string::npos) {
			str.replace(pos, 1, ";"); /* ENDOPT */
			pos=str.find('\1', pos+2);
		}
	}

	/* apply preproc */
	parse_preproc(res, errbuf);
	if (*errbuf!='\0')
		return 0;

	/* add options in opts */
	for (const auto&r:res) {
		_cfgopt opt;

		/* parse options */
		parse_cfgopt(r, &opt, errbuf);
		if (*errbuf!='\0')
			return 0;

		/* this preproc, skip */
		if (opt.name==INCLUDE_TOKEN)
			continue;

		opts.push_back(opt);
	}

	return 1;
}


/*
 * Reading file and skip all comment at like this comment,
 * save all lines in lines and return this vector. If file was
 * fail open, return "-1" in first vector element, otherwise,
 * return vector with lines.
 */
static std::vector<std::string> fileread(const std::string& path)
{
	std::vector<std::string>	lines;
	bool				inside_comment=false;
	std::ifstream			file(path);
	std::string			line;

	if (!file.is_open()) {
		lines = {"-1"};
		return lines;
	}

	while (std::getline(file, line)) {
		std::string	processed_line;
		size_t		i=0;

		/* skip comment like this */
		while (i<line.size()) {
			if (!inside_comment) {
				if (i+1<line.size()&&line[i]=='/'&&line[i+1]=='*') {
					inside_comment=true;
					i+=2;
				}
				else {
					processed_line+=line[i];
					i++;
				}
			}
			else {
				if (i+1<line.size()&&line[i]=='*'&&line[i+1]=='/') {
					inside_comment=false;
					i+=2;
				}
				else
					i++;
			}
		}

		/* add line */
		if (!processed_line.empty())
			lines.push_back(processed_line);
	}

	file.close();
	return lines;
}


/*
 * Apply directive preproc include, to start, get file
 * from path specifying res->val, and save all his lines in
 * newres. Then, apply config on this file.
 */
bool NESCAOPTS::include_apply(struct _cfgopt *res, char *errbuf)
{
	std::vector<std::string>	newres;
	std::string			path;
	size_t				pos;

	pos=res->val.find("*");
	if (pos!=std::string::npos)
		res->val.replace(pos, 1, this->cfgpath);
	newres=fileread(res->val);
	if (newres.empty())
		return 0;
	if (newres[0]=="-1") {
		this->ncsprint->error("failed open file \""+res->val+"\"!");
		return 0;
	}
	return parse_cfg(newres, errbuf);
}


/*
 * Find and apply preprocessor.
 */
bool NESCAOPTS::parse_preproc(std::vector<std::string> file, char *errbuf)
{
	for (auto f:file) {
		_cfgopt opt;
		if (!parse_cfgopt(f, &opt, errbuf))
			continue;
		if (opt.name==INCLUDE_TOKEN)
			include_apply(&opt, errbuf);
	}
	return 1;
}


/*
 * Apply config file. Main func for config.
 */
void NESCAOPTS::cfg_apply(const std::string &path, NESCADATA *ncsdata, NESCAPRINT *ncsprint)
{
	std::vector<std::string>	file;
	char				errbuf[_ERRBUFMAXLEN];

	this->cfgpath=removelastpath(path);
	this->ncsprint=ncsprint;
	*errbuf='\0';

	file=fileread(path);
	if (file.empty())
		return;
	if (file[0]=="-1")
		this->ncsprint->error("failed open file \""+path+"\"!");
	if (!(parse_cfg(file, errbuf)))
		if (*errbuf!='\0')
			this->ncsprint->error(errbuf);
	for (const auto&o:opts) {
		if (o.nullval&&o.val!="1")
			continue;
		opts_apply(o.id, o.val);
	}
}


/*
 * -import <import_param>
 */
void NESCAOPTS::set_import_param(const std::string &import_param)
{
	struct stat	buf;
	bool		ret=0;

	ret=((stat(import_param.c_str(), &buf)==0));
	if (!ret)
		ncsprint->error("import_param file \"" + import_param+ "\" not found!");
	this->import_param=import_param;
}
void NESCAOPTS::set_import_flag(void) { this->import_flag=1; }
std::string NESCAOPTS::get_import_param(void) { return this->import_param; }
bool NESCAOPTS::check_import_flag(void) { return this->import_flag; }


/*
 * -gmax <gmax_param>
 * -gmin <gmin_param>
 * -gplus <gplus_param>
 */
void NESCAOPTS::set_gmax_param(size_t gmax_param)
{
	if (gmax_param<=0)
		this->ncsprint->error("wrong group max size!");
	this->gmax_param=gmax_param;
}
void NESCAOPTS::set_gmin_param(size_t gmin_param)
{
	if (gmin_param<=0)
		this->ncsprint->error("wrong group min size!");
	this->gmin_param=gmin_param;
}
void NESCAOPTS::set_gplus_param(size_t gplus_param)
{
	if (gplus_param<=0)
		this->ncsprint->error("wrong group plus size!");
	this->gplus_param=gplus_param;
}
void NESCAOPTS::set_gmax_flag(void) { this->gmax_flag=1; }
void NESCAOPTS::set_gmin_flag(void) { this->gmin_flag=1; }
void NESCAOPTS::set_gplus_flag(void) { this->gplus_flag=1; }
bool NESCAOPTS::check_gmax_flag(void) { return this->gmax_flag; }
bool NESCAOPTS::check_gmin_flag(void) { return this->gmin_flag; }
bool NESCAOPTS::check_gplus_flag(void){ return this->gplus_flag; }
size_t NESCAOPTS::get_gmax_param(void) { return this->gmax_param; }
size_t NESCAOPTS::get_gmin_param(void) { return this->gmin_param; }
size_t NESCAOPTS::get_gplus_param(void) { return this->gplus_param; }


/*
 * -ps <ps_param>
 * -pa <pa_param>
 * -py <py_param>
 * -pu <pu_param>
 * -pe
 * -pi
 * -pm
 * -pr
 */
void NESCAOPTS::set_pe_flag(void) { this->pe_flag=1; }
void NESCAOPTS::set_pi_flag(void) { this->pi_flag=1; }
void NESCAOPTS::set_pm_flag(void) { this->pm_flag=1; }
void NESCAOPTS::set_ps_flag(void) { this->ps_flag=1; }
void NESCAOPTS::set_pa_flag(void) { this->pa_flag=1; }
void NESCAOPTS::set_py_flag(void) { this->py_flag=1; }
void NESCAOPTS::set_pu_flag(void) { this->pu_flag=1; }
void NESCAOPTS::set_pr_flag(void) { this->pr_flag=1; }
void NESCAOPTS::set_ps_param(const std::string &ps_param) {
	this->ps_param=split_string_int(ps_param, SPLITOPT_DEL, USHRT_MAX, 0, this->ncsprint);
}
void NESCAOPTS::set_pa_param(const std::string &pa_param) {
	this->pa_param=split_string_int(pa_param, SPLITOPT_DEL, USHRT_MAX, 0, this->ncsprint);
}
void NESCAOPTS::set_py_param(const std::string &py_param) {
	this->py_param=split_string_int(py_param, SPLITOPT_DEL, USHRT_MAX, 0, this->ncsprint);
}
void NESCAOPTS::set_pu_param(const std::string &pu_param) {
	this->pu_param=split_string_int(pu_param, SPLITOPT_DEL, USHRT_MAX, 0, this->ncsprint);
}
std::vector<int> NESCAOPTS::get_ps_param(void) { return this->ps_param; }
std::vector<int> NESCAOPTS::get_pa_param(void) { return this->pa_param; }
std::vector<int> NESCAOPTS::get_py_param(void) { return this->py_param; }
std::vector<int> NESCAOPTS::get_pu_param(void) { return this->pu_param; }
bool NESCAOPTS::check_pe_flag(void) { return this->pe_flag; }
bool NESCAOPTS::check_pi_flag(void) { return this->pi_flag; }
bool NESCAOPTS::check_pm_flag(void) { return this->pm_flag; }
bool NESCAOPTS::check_ps_flag(void) { return this->ps_flag; }
bool NESCAOPTS::check_pa_flag(void) { return this->pa_flag; }
bool NESCAOPTS::check_py_flag(void) { return this->py_flag; }
bool NESCAOPTS::check_pu_flag(void) { return this->pu_flag; }
bool NESCAOPTS::check_pr_flag(void) { return this->pr_flag; }


/*
 * -random-ip <random_ip_param>
 */
void NESCAOPTS::set_random_ip_flag(void) { this->random_ip_flag=1; }
void NESCAOPTS::set_random_ip_param(size_t random_ip_param)
{
	if (random_ip_param<=0)
		this->ncsprint->error("wrong count random ips!");
	this->random_ip_param=random_ip_param;
}
size_t NESCAOPTS::get_random_ip_param(void) { return this->random_ip_param; }
bool NESCAOPTS::check_random_ip_flag(void) { return this->random_ip_flag; }


/*
 * -dev <dev_param>
 * -dst <dst_param>
 * -src <src_param>
 * -ip4 <ip4_param>
 * -ip6 <ip6_param>
 */
void NESCAOPTS::set_dev_flag(void) { this->dev_flag=1; }
void NESCAOPTS::set_ip4_flag(void) { this->ip4_flag=1; }
void NESCAOPTS::set_ip6_flag(void) { this->ip6_flag=1; }
void NESCAOPTS::set_src_flag(void) { this->src_flag=1; }
void NESCAOPTS::set_dst_flag(void) { this->dst_flag=1; }
void NESCAOPTS::set_dev_param(const std::string &dev_param) { this->dev_param=dev_param; }
void NESCAOPTS::set_ip4_param(const std::string &ip4_param) { this->ip4_param=ip4_param; }
void NESCAOPTS::set_ip6_param(const std::string &ip6_param) { this->ip6_param=ip6_param; }
void NESCAOPTS::set_src_param(const std::string &src_param) { this->src_param=src_param; }
void NESCAOPTS::set_dst_param(const std::string &dst_param) { this->dst_param=dst_param; }
std::string NESCAOPTS::get_dev_param(void) { return this->dev_param; }
std::string NESCAOPTS::get_ip4_param(void) { return this->ip4_param; }
std::string NESCAOPTS::get_ip6_param(void) { return this->ip6_param; }
std::string NESCAOPTS::get_src_param(void) { return this->src_param; }
std::string NESCAOPTS::get_dst_param(void) { return this->dst_param; }
bool NESCAOPTS::check_dev_flag(void) { return this->dev_flag; }
bool NESCAOPTS::check_ip4_flag(void) { return this->ip4_flag; }
bool NESCAOPTS::check_ip6_flag(void) { return this->ip6_flag; }
bool NESCAOPTS::check_src_flag(void) { return this->src_flag; }
bool NESCAOPTS::check_dst_flag(void) { return this->dst_flag; }


/*
 * -dlen <dlen_param>
 * -dhex <dhex_param>
 * -dstr <dstr_param>
 */
void NESCAOPTS::set_dlen_flag(void) { this->dlen_flag=1; }
void NESCAOPTS::set_dhex_flag(void) { this->dhex_flag=1; }
void NESCAOPTS::set_dstr_flag(void) { this->dstr_flag=1; }
void NESCAOPTS::set_dlen_param(const std::string &dlen_param)
{
	int len;
	len=std::stoi(dlen_param);
	if (len>1400)
		this->ncsprint->error("max data len for eth is 1400 \"" + dlen_param + "\"");
	this->dlen_param=dlen_param;
}
void NESCAOPTS::set_dhex_param(const std::string &dhex_param)
{
	std::string	tmp1;
	size_t		len;
	char		*tmp;

	tmp1=dhex_param;
	tmp=tmp1.data();
	hex_ahtoh(tmp, &len);
	if (len>1400)
		this->ncsprint->error("max data hex for eth is 1400 \"" + dhex_param + "\"");
	this->dhex_param=dhex_param;
}
void NESCAOPTS::set_dstr_param(const std::string &dstr_param)
{
	if ((strlen(dstr_param.c_str()))>1400)
		this->ncsprint->error("max data string for eth is 1400 \"" + dstr_param + "\"");
	this->dstr_param=dstr_param;
}
std::string NESCAOPTS::get_dlen_param(void) { return this->dlen_param; }
std::string NESCAOPTS::get_dhex_param(void) { return this->dhex_param; }
std::string NESCAOPTS::get_dstr_param(void) { return this->dstr_param; }
bool NESCAOPTS::check_dlen_flag(void) { return this->dlen_flag; }
bool NESCAOPTS::check_dhex_flag(void) { return this->dhex_flag; }
bool NESCAOPTS::check_dstr_flag(void) { return this->dstr_flag; }


/*
 * -ttl <ttl_param>
 * -off <off_param>
 * -ipopt <ipopt_param>
 */
void NESCAOPTS::set_ttl_flag(void) { this->ttl_flag=1; }
void NESCAOPTS::set_off_flag(void) { this->off_flag=1; }
void NESCAOPTS::set_ipopt_flag(void) { this->ipopt_flag=1; }
void NESCAOPTS::set_ttl_param(const std::string &ttl_param)
{
	if (std::stoi(ttl_param)>UCHAR_MAX)
		this->ncsprint->error("please set ttl in this range (0-255), \"" + ttl_param + "\"");
	this->ttl_param=ttl_param;
}
void NESCAOPTS::set_off_param(const std::string &off_param)
{
	this->off_param=off_param;
}
void NESCAOPTS::set_ipopt_param(const std::string &ipopt_param)
{
	this->ipopt_param=ipopt_param;
}
std::string NESCAOPTS::get_ttl_param(void) { return this->ttl_param; }
std::string NESCAOPTS::get_off_param(void) { return this->off_param; }
std::string NESCAOPTS::get_ipopt_param(void) { return this->ipopt_param; }
bool NESCAOPTS::check_ttl_flag(void) { return this->ttl_flag; }
bool NESCAOPTS::check_off_flag(void) { return this->off_flag; }
bool NESCAOPTS::check_ipopt_flag(void) { return this->ipopt_flag; }


/*
 * -badsum
 */
void NESCAOPTS::set_badsum_flag(void) { this->badsum_flag=1; }
bool NESCAOPTS::check_badsum_flag(void) { return this->badsum_flag; }


/*
 * -cfg <cfg_param>
 */
void NESCAOPTS::set_cfg_flag(void) { this->cfg_flag=1; }
void NESCAOPTS::set_cfg_param(const std::string &cfg_param)
{
	std::string	newpath;
	size_t		i;
	bool		t;

	for (i=t=0;i<cfg_param.length();i++) {
		if (cfg_param.at(i)=='-'&&cfg_param.at(i+1)=='-') {
			newpath="resources/config/";
			t=1;
			i+=2;
		}
		if (t) newpath+=cfg_param[i];
	}
	if (newpath.empty())
		newpath=cfg_param;
	this->cfg_param=newpath;
}
std::string NESCAOPTS::get_cfg_param(void) { return this->cfg_param; }
bool NESCAOPTS::check_cfg_flag(void) { return this->cfg_flag; }


/*
 * -n
 */
void NESCAOPTS::set_n_flag(void) { this->n_flag=1; }
bool NESCAOPTS::check_n_flag(void) { return this->n_flag; }


/*
 * -n-ping
 */
void NESCAOPTS::set_n_ping_flag(void) { this->n_ping_flag=1; }
bool NESCAOPTS::check_n_ping_flag(void) { return this->n_ping_flag; }


/*
 * -wait-ping <wait_ping_param>
 */
void NESCAOPTS::set_wait_ping_flag(void) { this->wait_ping_flag=1; }
void NESCAOPTS::set_wait_ping_param(const std::string &wait_ping_param)
{
	this->wait_ping_param=wait_ping_param;
	if (delayconv(get_wait_ping_param().c_str())<=1)
		ncsprint->warning("a timeout of 1 or 0 nanoseconds is unlikely to accept packets");
}
std::string NESCAOPTS::get_wait_ping_param(void) { return this->wait_ping_param; }
bool NESCAOPTS::check_wait_ping_flag(void) { return this->wait_ping_flag; }


/*
 * -num-ping <num_ping_param>
 */
void NESCAOPTS::set_num_ping_flag(void) { this->num_ping_flag=1; }
void NESCAOPTS::set_num_ping_param(const std::string &num_ping_param) { this->num_ping_param=num_ping_param; }
std::string NESCAOPTS::get_num_ping_param(void) { return this->num_ping_param; }
bool NESCAOPTS::check_num_ping_flag(void) { return this->num_ping_flag; }


/*
 * -all-ping
 */
void NESCAOPTS::set_all_ping_flag(void)
{
	set_pe_flag();
	set_pm_flag();
	set_pi_flag();
	set_pr_flag();
	if (!check_pa_flag()) {
		set_pa_flag();
		set_pa_param("80,443");
	}
	if (!check_ps_flag()) {
		set_ps_flag();
		set_ps_param("80,443");
	}
	if (!check_pu_flag()) {
		set_pu_flag();
		set_pu_param("80,53");
	}
	if (!check_py_flag()) {
		set_py_flag();
		set_py_param("80");
	}
	this->all_ping_flag=1;
}

bool NESCAOPTS::check_all_ping_flag(void) { return this->all_ping_flag; }


/*
 * -syn
 */
void NESCAOPTS::set_syn_flag(void) { this->syn_flag=1; }
bool NESCAOPTS::check_syn_flag(void) { return this->syn_flag; }


/*
 * -p <p_param>
 */
static std::vector<int> __portrange(const std::string& range)
{
	size_t			pos, start, end, i;
	std::vector<int>	res;

	pos=range.find('-');
	if (pos==std::string::npos)
		return res;

	start=std::stoi(range.substr(0, pos));
	end=std::stoi(range.substr(pos+1));

	for (i=start;i<=end;++i)
		res.push_back(i);

	return res;
}
void NESCAOPTS::set_p_param(const std::string &p_param)
{
	std::stringstream	ss(p_param);
	std::vector<int>	tmp;
	std::string		token;
	size_t			isrange;
	int			proto;

	/*
	 * -p S:80,10-12
	 *	 80 proto:132
	 *	 10 proto:132
	 *	 11 proto:132
	 *	 12 proto:132
	 *
	 * -p 80,10-12
	 *	 80 proto:6
	 *	 10 proto:6
	 *	 11 proto:6
	 *	 12 proto:6
	 *
	 * -p 80,10-12,U:10,2,S:1-2
	 *	 80 proto:6
	 *	 10 proto:6
	 *	 11 proto:6
	 *	 12 proto:6
	 *	 10 proto:17
	 *	 2 proto:17
	 *	 1 proto:132
	 *	 2 proto:132
	 */
	proto=IPPROTO_TCP;
	while (std::getline(ss, token, SPLITOPT_DEL)) {
		if (!std::isdigit(token[0])) {
			switch (token[0]) {
				case 't':
				case 'T': proto=IPPROTO_TCP; break;
				case 'u':
				case 'U': proto=IPPROTO_UDP; break;
				case 's':
				case 'S': proto=IPPROTO_SCTP; break;
			}
			token.erase(0,2); /* delete (<T,U,S>:) */
		}

		/* is port range */
		isrange=token.find('-');
		if (isrange!=std::string::npos) {
			tmp=__portrange(token);

			/* add ports */
			for (const auto&p:tmp) {
				NESCAPORT port={};
				port.port=p;
				port.proto=proto;
				this->p_param.push_back(port);
			}
		}
		/* is port */
		else {
			NESCAPORT port={};
			port.port=std::stoi(token);
			port.proto=proto;
			this->p_param.push_back(port);
		}
	}
}
std::vector<NESCAPORT> NESCAOPTS::get_p_param(void) { return this->p_param; }
void NESCAOPTS::set_p_flag(void) { this->p_flag=1; }
bool NESCAOPTS::check_p_flag(void) { return this->p_flag; }


/*
 * -sn
 */
void NESCAOPTS::set_sn_flag(void) { this->sn_flag=1; }
bool NESCAOPTS::check_sn_flag(void) { return this->sn_flag; }


/*
 * -xmas
 */
void NESCAOPTS::set_xmas_flag(void) { this->xmas_flag=1; }
bool NESCAOPTS::check_xmas_flag(void) { return this->xmas_flag; }


/*
 * -fin
 */
void NESCAOPTS::set_fin_flag(void) { this->fin_flag = 1; }
bool NESCAOPTS::check_fin_flag(void) { return this->fin_flag; }


/*
 * -null
 */
void NESCAOPTS::set_null_flag(void) { this->null_flag = 1; }
bool NESCAOPTS::check_null_flag(void) { return this->null_flag; }


/*
 * -psh
 */
void NESCAOPTS::set_psh_flag(void) { this->psh_flag = 1; }
bool NESCAOPTS::check_psh_flag(void) { return this->psh_flag; }


/*
 * -ack
 */
void NESCAOPTS::set_ack_flag(void) { this->ack_flag = 1; }
bool NESCAOPTS::check_ack_flag(void) { return this->ack_flag; }


/*
 * -window
 */
void NESCAOPTS::set_window_flag(void) { this->window_flag = 1; }
bool NESCAOPTS::check_window_flag(void) { return this->window_flag; }


/*
 * -mainmon
 */
void NESCAOPTS::set_maimon_flag(void) { this->maimon_flag = 1; }
bool NESCAOPTS::check_maimon_flag(void) { return this->maimon_flag; }


/*
 * -init
 */
void NESCAOPTS::set_init_flag(void) { this->init_flag = 1; }
bool NESCAOPTS::check_init_flag(void) { return this->init_flag; }


/*
 * -cookie
 */
void NESCAOPTS::set_cookie_flag(void) { this->cookie_flag = 1; }
bool NESCAOPTS::check_cookie_flag(void) { return this->cookie_flag; }


/*
 * -udp
 */
void NESCAOPTS::set_udp_flag(void) { this->udp_flag = 1; }
bool NESCAOPTS::check_udp_flag(void) { return this->udp_flag; }


/*
 * -wait-scan <wait_scan_param>
 */
void NESCAOPTS::set_wait_scan_flag(void) { this->wait_scan_flag=1; }
void NESCAOPTS::set_wait_scan_param(const std::string &wait_scan_param)
{
	this->wait_scan_param=wait_scan_param;
	if (delayconv(get_wait_scan_param().c_str())<=1)
		ncsprint->warning("a timeout of 1 or 0 nanoseconds is unlikely to accept packets");
}
std::string NESCAOPTS::get_wait_scan_param(void) { return this->wait_scan_param; }
bool NESCAOPTS::check_wait_scan_flag(void) { return this->wait_scan_flag; }


/*
 * -mtpl-scan <mtpl_scan_param>
 */
void NESCAOPTS::set_mtpl_scan_flag(void) { this->mtpl_scan_flag=1; }
void NESCAOPTS::set_mtpl_scan_param(const std::string &mtpl_scan_param) { this->mtpl_scan_param=mtpl_scan_param; }
std::string NESCAOPTS::get_mtpl_scan_param(void) { return this->mtpl_scan_param; }
bool NESCAOPTS::check_mtpl_scan_flag(void) { return this->mtpl_scan_flag; }


/*
 * -pps <pps_param>
 */
void NESCAOPTS::set_pps_flag(void) { this->pps_flag=1; }
void NESCAOPTS::set_pps_param(const std::string &pps_param) { this->pps_param=pps_param; }
std::string NESCAOPTS::get_pps_param(void) { return this->pps_param; }
bool NESCAOPTS::check_pps_flag(void) { return this->pps_flag; }


/*
 * -stats
 */
void NESCAOPTS::set_stats_flag(void) { this->stats_flag=1; }
bool NESCAOPTS::check_stats_flag(void) { return this->stats_flag; }


/*
 * -maxfds <maxfds_param>
 */
void NESCAOPTS::set_maxfds_flag(void) { this->maxfds_flag=1; }
void NESCAOPTS::set_maxfds_param(const std::string &maxfds_param) { this->maxfds_param=maxfds_param; }
std::string NESCAOPTS::get_maxfds_param(void) { return this->maxfds_param; }
bool NESCAOPTS::check_maxfds_flag(void) { return this->maxfds_flag; }


/*
 * -all-scan
 */
void NESCAOPTS::set_all_scan_flag(void)
{
	set_xmas_flag();
	set_syn_flag();
	set_fin_flag();
	set_null_flag();
	set_psh_flag();
	set_maimon_flag();
	set_window_flag();
	set_ack_flag();
	set_init_flag();
	set_cookie_flag();
	set_udp_flag();
	this->all_scan_flag=1;
}
bool NESCAOPTS::check_all_scan_flag(void) { return this->all_scan_flag; }


/*
 * -num-scan <num_scan_param
 */
void NESCAOPTS::set_num_scan_flag(void) { this->num_scan_flag=1; }
void NESCAOPTS::set_num_scan_param(const std::string &num_scan_param) { this->num_scan_param=num_scan_param; }
std::string NESCAOPTS::get_num_scan_param(void) { return this->num_scan_param; }
bool NESCAOPTS::check_num_scan_flag(void) { return this->num_scan_flag; }


/*
 * -s <s_param>
 */
void NESCAOPTS::set_s_flag(void) { this->s_flag=1; }
void NESCAOPTS::set_s_param(const std::string &s_param)
{
	std::stringstream	ss(s_param);
	size_t			rem=0, isrange=0;
	std::vector<int>	tmp;
	std::string		token;
	int			service=0;

	while (std::getline(ss, token, SPLITOPT_DEL)) {

		if (!isdigit(token[0])) {
			rem=0;
			if (!find_word(token.c_str(), "http")) {
				service=S_HTTP;
				rem=(std::string("http").length());
			}
			if (!find_word(token.c_str(), "ftp")) {
				service=S_FTP;
				rem=(std::string("ftp").length());
			}
			rem++;
			token.erase(0,rem);
		}

		/* is port range */
		isrange=token.find('-');
		if (isrange!=std::string::npos) {
			tmp=__portrange(token);

			/* add ports */
			for (const auto&p:tmp) {
				NESCAPORT port={};
				port.port=p;
				port.proto=service;
				this->s_param.push_back(port);
			}
		}
		/* is port */
		else {
			NESCAPORT port={};
			port.port=std::stoi(token);
			port.proto=service;
			this->s_param.push_back(port);
		}
	}
}
std::vector<NESCAPORT> NESCAOPTS::get_s_param(void) { return this->s_param; }
bool NESCAOPTS::check_s_flag(void) { return this->s_flag; }


/*
 * -detal
 */
void NESCAOPTS::set_detal_flag(void) { this->detal_flag=1; }
bool NESCAOPTS::check_detal_flag(void) { return this->detal_flag; }


/*
 * -v
 */
void NESCAOPTS::set_v_flag(void) { this->v_flag=1; this->stats_flag=1; }
bool NESCAOPTS::check_v_flag(void) { return this->v_flag; }


/*
 * -html <html_param>
 */
void NESCAOPTS::set_html_param(const std::string &html_param) { this->html_param=html_param; }
std::string NESCAOPTS::get_html_param(void) { return this->html_param; }
void NESCAOPTS::set_html_flag(void) { this->html_flag=1; }
bool NESCAOPTS::check_html_flag(void) { return this->html_flag; }


/*
 * -win <win_param>
 */
void NESCAOPTS::set_win_param(const std::string &win_param)
{
	if (std::stoi(win_param)>USHRT_MAX)
		this->ncsprint->error("please set win in this range (0-65535), \"" + win_param + "\"");
	this->win_param=win_param;
}
std::string NESCAOPTS::get_win_param(void) { return this->win_param; }
void NESCAOPTS::set_win_flag(void) { this->win_flag=1; }
bool NESCAOPTS::check_win_flag(void) { return this->win_flag; }


/*
 * -ackn <ackn_param>
 */
void NESCAOPTS::set_ackn_param(const std::string &ackn_param) {
	if (std::stoul(ackn_param)>UINT_MAX)
		this->ncsprint->error("please set ack in this range (0-4294967295), \"" + ackn_param + "\"");
	this->ackn_param=ackn_param;
}
std::string NESCAOPTS::get_ackn_param(void) { return this->ackn_param; }
void NESCAOPTS::set_ackn_flag(void) { this->ackn_flag=1; }
bool NESCAOPTS::check_ackn_flag(void) { return this->ackn_flag=1; }


/*
 * -dbpath <dbpath_param>
 */
void NESCAOPTS::set_dbpath_param(const std::string &dbpath_param) { this->dbpath_param=dbpath_param; }
std::string NESCAOPTS::get_dbpath_param(void) { return this->dbpath_param; }
void NESCAOPTS::set_dbpath_flag(void) { this->dbpath_flag=1; }
bool NESCAOPTS::check_dbpath_flag(void) { return this->dbpath_flag; }


/*
 * -n-db
 */
void NESCAOPTS::set_n_db_flag(void) { this->n_db_flag=1; }
bool NESCAOPTS::check_n_db_flag(void) { return this->n_db_flag; }


/*
 * -n-brute
 */
void NESCAOPTS::set_n_brute_flag(void) { this->n_brute_flag=1; }
bool NESCAOPTS::check_n_brute_flag(void) { return this->n_brute_flag; }


/*
 * -login <login_param>
 * -pass <pass_param>
 */
void NESCAOPTS::set_login_param(const std::string &login_param) { this->login_param=login_param; }
std::string NESCAOPTS::get_login_param(void) { return this->login_param; }
void NESCAOPTS::set_login_flag(void) { this->login_flag=1; }
bool NESCAOPTS::check_login_flag(void) { return this->login_flag; }
void NESCAOPTS::set_pass_param(const std::string &pass_param) { this->pass_param=pass_param; }
std::string NESCAOPTS::get_pass_param(void) { return this->pass_param; }
void NESCAOPTS::set_pass_flag(void) { this->pass_flag=1; }
bool NESCAOPTS::check_pass_flag(void) { return this->pass_flag; }


/*
 * -delay-brute <delay_brute_param>
 */
void NESCAOPTS::set_delay_brute_param(const std::string &delay_brute_param) { this->delay_brute_param=delay_brute_param; }
std::string NESCAOPTS::get_delay_brute_param(void) { return this->delay_brute_param; }
void NESCAOPTS::set_delay_brute_flag(void) { this->delay_brute_flag=1; }
bool NESCAOPTS::check_delay_brute_flag(void) { return this->delay_brute_flag; }


/*
 * -wait-brute <wait_brute_param>
 */
void NESCAOPTS::set_wait_brute_param(const std::string &wait_brute_param) { this->wait_brute_param=wait_brute_param; }
std::string NESCAOPTS::get_wait_brute_param(void) { return this->wait_brute_param; }
void NESCAOPTS::set_wait_brute_flag(void) { this->wait_brute_flag=1; }
bool NESCAOPTS::check_wait_brute_flag(void) { return this->wait_brute_flag; }


/*
 * -threads-brute <threads_brute_param>
 */
void NESCAOPTS::set_threads_brute_param(const std::string &threads_brute_param) { this->threads_brute_param=threads_brute_param; }
std::string NESCAOPTS::get_threads_brute_param(void) { return this->threads_brute_param; }
void NESCAOPTS::set_threads_brute_flag(void) { this->threads_brute_flag=1; }
bool NESCAOPTS::check_threads_brute_flag(void) { return this->threads_brute_flag; }


/*
 * -adler32
 */
void NESCAOPTS::set_adler32_flag(void) { this->adler32_flag=1; }
bool NESCAOPTS::check_adler32_flag(void) { return this->adler32_flag; }


/*
 * -onlyopen
 */
void NESCAOPTS::set_onlyopen_flag(void) { this->onlyopen_flag=1; }
bool NESCAOPTS::check_onlyopen_flag(void) { return this->onlyopen_flag; }


/*
 * It searches the longopts array, looks for the <opt> option, if it finds it,
 * checks if it has a parameter, if so, it returns true, otherwise it returns
 * false.
 */
bool NESCAOPTS::is_requiread_options(const std::string &opt)
{
	for (const auto&o:longopts) {
		if (!strcmp(o.name, opt.c_str())) {
			if (o.has_arg==1)
				return true;
			else
				break;
		}
	}
	return false;
}


/*
 * Check options.
 */
void NESCAOPTS::opts_validate(void)
{
	bool ret;
	if (check_syn_flag()||check_xmas_flag()||
			check_fin_flag()||check_ack_flag()||
			check_psh_flag()||check_null_flag()||
			check_window_flag()||check_maimon_flag()||
			check_udp_flag()||check_init_flag()||
			check_cookie_flag()) {
		if (!check_p_flag())
			ncsprint->error("please specify ports (Ex: -p 80,443)");
		if (check_udp_flag()) {
			ret=0;
			for (const auto&p:this->p_param)
				if (p.proto==PR_UDP)
					ret=1;
			if (!ret)
				ncsprint->error("please specify UDP ports (Ex: -p U:80,443)");
		}
		if (check_init_flag()||check_cookie_flag()) {
			ret=0;
			for (const auto&p:this->p_param)
				if (p.proto==PR_SCTP)
					ret=1;
			if (!ret)
				ncsprint->error("please specify SCTP ports (Ex: -p S:80,443)");
		}
		if (check_syn_flag()||check_xmas_flag()||
				check_fin_flag()||check_ack_flag()||
				check_psh_flag()||check_null_flag()||
				check_window_flag()||check_maimon_flag()) {
			ret=0;
			for (const auto&p:this->p_param)
				if (p.proto==PR_TCP)
					ret=1;
			if (!ret)
				ncsprint->error("please specify TCP ports (Ex: -p T:80,443)");
		}
	}
}


/*
 * Parse file by path starting from start, up to num,
 * and return vector with lines.
 */
std::vector<std::string> fileparse(const std::string& path, size_t start, size_t num)
{
	std::vector<std::string>	lines;
	std::ifstream			file(path);
	std::string			line;
	size_t				cur=0;

	if (!file.is_open())
		return lines;

	while (std::getline(file, line)) {
		if (cur<start) {
			++cur;
			continue;
		}
		if (cur<start+num) {
			lines.push_back(line);
			++cur;
		}
		else
			break;
	}

	file.close();
	return lines;
}


/*
 * copy one vector to two vector
 */
template<typename T>
static void copyvec(const std::vector<T>& source, std::vector<T>& destination)
{
	destination.reserve(source.size());
	std::copy(source.begin(), source.end(), std::back_inserter(destination));
}


/*
 * Extracts targets from the startup string, for this purpose it searches through
 * the arguments and checks if the argument starts with -, if yes then it is not
 * a target this argument is skipped, and also, if this argument can have a
 * parameter, it skips it too. If it is wrong, it is a target.
 */
void NESCARAWTARGETS::load(int argc, char **argv, NESCAOPTS *ncsopts, NESCAPRINT *ncsprint, NESCADEVICE *ncsdev)
{
	std::vector<std::string>	targets;
	std::string			txt, line;
	int				i=1;
	bool				opt=0;

	this->ncsdev=ncsdev;
	for (;i<argc;++i) {
		txt=argv[i];
		if (txt.empty())
			continue;
		if (txt[0]=='-') {
			if (ncsopts->is_requiread_options(txt.erase(0,1)))
				i++;
			continue;
		}
		targets.push_back(txt);
	}
	if (!targets.empty())
		opt=1;

	check_from_file=ncsopts->check_import_flag();
	check_randomips=ncsopts->check_random_ip_flag();
	from_file=ncsopts->get_import_param();
	randomips=ncsopts->get_random_ip_param();

	if (check_from_file) {
		std::ifstream f(from_file);
		while (std::getline(f, line))
			++filelines;
		f.close();
	}

	if (ncsopts->check_v_flag())
		ncsprint->note(
				"set source targets from <file="+
				std::string(((check_from_file)?("1("+
					std::string(from_file))+")":"0"))+", rand="+
				std::string(((check_randomips)?("1("+
					std::to_string(randomips)+")"):"0"))+", arg="+
				((opt)?("1"):"0")+">"
		);

	if (targets.empty()&&filelines<=0&&randomips<=0)
		ncsprint->error("not a single target was specified!");
	processing(targets);
}


/*
 * Checks if <txt> is an ipv4 address, and if it is correct. If it is, it returns
 * true, if not, it returns false.
 */
static bool is_valid_ipv4(const std::string &txt)
{
	std::vector<std::string>	octets;
	std::istringstream		stream(txt);
	std::string			token="";
	int				num=0;

	/* geting octets */
	while (std::getline(stream, token, '.'))
		octets.push_back(token);

	/* ipv4 address has 4 octets */
	if (octets.size()!=4)
		return false;

	/* octets loop */
	for (const auto&octet:octets) {

		/* all ipv4 address octets are numeric */
		if (octet.empty()||octet.size()>3||!std::all_of(
			octet.begin(), octet.end(), ::isdigit))
			return false;

		/* ipv4 address has numeric octets in range (0-255) */
		num=std::stoi(octet);
		if (num<0||num>255||(octet.size()>1&&octet[0]=='0'))
			return false;
	}

	/* is ipv4 */
	return true;
}


/*
 * Checks if <txt> is an ipv6 address, and if it is correct. If it is, it returns
 * true, if not, it returns false.
 */
static bool is_valid_ipv6(const std::string &txt)
{
	ip6_t ip6;

	/* easy check */
	if (ip6t_pton(txt.c_str(), &ip6)==-1)
		return false;

	/* is ipv6 */
	return true;
}


static bool is_valid_cidr4(const std::string &txt)
{
	std::string	addr, prfx;
	int		prfxlen=0;

	if (txt.find(".")==std::string::npos||txt.find("/")==std::string::npos)
		return 0;

	auto pos=txt.find("/");
	addr=txt.substr(0, pos);
	prfx=txt.substr(pos + 1);

	try { prfxlen=std::stoi(prfx); }
	catch (...) { return 0; }

	if (prfxlen<0||prfxlen>32)
		return 0;
	if (!is_valid_ipv4(addr))
		return 0;

	return 1;
}


static bool is_valid_range4(const std::string &txt)
{
	std::string	addr1, addr2;
	std::size_t	pos=0;

	if ((pos=txt.find("-"))==std::string::npos)
		return 0;

	addr1=txt.substr(0, pos);
	addr2=txt.substr(pos+1);

	if (!is_valid_ipv4(addr1))
		return 0;
	if (!is_valid_ipv4(addr2))
		return 0;

	return 1;
}


static bool is_valid_cidr6(const std::string &txt)
{
	std::string	addr, prfx;
	int		prfxlen=0;

	if (txt.find(":")==std::string::npos||txt.find("/")==std::string::npos)
		return 0;

	auto pos=txt.find("/");
	addr=txt.substr(0, pos);
	prfx=txt.substr(pos + 1);

	try { prfxlen=std::stoi(prfx); }
	catch (...) { return 0; }

	if (prfxlen<0||prfxlen>128)
		return 0;
	if (!is_valid_ipv6(addr))
		return 0;

	return 1;
}

static bool is_valid_range6(const std::string &txt)
{
	std::string addr1, addr2;
	std::size_t pos=0;

	if ((pos=txt.find("-"))==std::string::npos)
		return 0;

	addr1=txt.substr(0, pos);
	addr2=txt.substr(pos+1);

	if (!is_valid_ipv6(addr1))
		return 0;
	if (!is_valid_ipv6(addr2))
		return 0;

	return 1;
}

/*
 * Checks all targets, recognizes them, and saves them with
 * the clarified types to targets.
 */
void NESCARAWTARGETS::processing(const std::vector<std::string> &targets)
{
	std::string target="";
	for (const auto&t:targets) {
		target=trim(t);
		if (is_valid_ipv6(target)||is_valid_cidr6(target)
			||is_valid_range6(target))
			if (!ncsdev->check_ipv6())
				this->ncsprint->error("your device not support ipv6");
		if (is_valid_ipv4(target)||is_valid_cidr4(target)
			||is_valid_range4(target))
			if (!ncsdev->check_ipv4())
				this->ncsprint->error("your device not support ipv4");
		if (is_valid_ipv4(target))
			this->ipv4.push_back(target);
		else if (is_valid_ipv6(target))
			this->ipv6.push_back(target);
		else if (is_valid_cidr4(target)) {
			NESCARAWRANGEV4 r(target, 1);
			this->grouptargets.push_back(r);
		}
		else if (is_valid_range4(target)) {
			NESCARAWRANGEV4 r(target, 0);
			this->grouptargets.push_back(r);
		}
		else if (is_valid_cidr6(target)) {
			NESCARAWRANGEV6 r(target, 1);
			this->grouptargets6.push_back(r);
		}
		else if (is_valid_range6(target)) {
			NESCARAWRANGEV6 r(target, 0);
			this->grouptargets6.push_back(r);
		}
		else {
			char ip4buf[16];
			if ((ip4_util_strdst(target.c_str(), ip4buf, 16))!=-1) {
				this->ipv4.push_back(ip4buf);
				this->dns[ip4buf]=target;
			}
			else
				ncsprint->warning("failed resolve \""+target+"\" ("+std::strerror(errno)+")");
		}
	}
}

std::string NESCARAWTARGETS::getdns(std::string ip)
{
	std::string ret;
	if (ip.empty())
		return "";
	ret=this->dns[ip];
	this->dns.erase(ip);
	return this->dns[ip];
}


/*
 * Returns the number of all addresses, if it is a cidr then the
 * number of addresses in it, not counting the network itself and
 * the broadcast.
 */
u128 NESCARAWTARGETS::totlen(void)
{
	u128 res=0;
	res+=ipv4.size();
	res+=ipv6.size();
	for (auto c:grouptargets)
		res+=c.getlen();
	for (auto c:grouptargets6)
		res+=c.getlen();
	return res;
}


/*
 * Split ipv4 address on four octets.
 */
std::array<int,4> NESCARAWRANGEV4::ip4parse(const std::string& ip)
{
	std::array<int, 4>	octets={0, 0, 0, 0};
	std::stringstream	ss(ip);
	std::string		octet="";
	int			i=0;

	while (std::getline(ss, octet, '.')&&i<4)
		octets[i++]=std::stoi(octet);

	/*
	 * cidr auto do this
	 * remove broadcast and expanded
	 */
	if (!this->cidr) {
		if (octets[3]==0)
			octets[3]++;
		else
			octets[3]--;
	}

	return octets;
}


/*
 * Collect ipv4 address from octets
 */
std::string NESCARAWRANGEV4::ip4unparse(const std::array<int,4>& octets)
{
	return std::to_string(octets[0])+"."+
		std::to_string(octets[1])+"."+
		std::to_string(octets[2])+"."+
		std::to_string(octets[3]);
}


void NESCARAWRANGEV4::init(const std::string &range)
{
	std::size_t pos=0;
	pos=range.find('-');
	if (pos!=std::string::npos) {
		this->start=ip4parse(range.substr(0, pos));
		this->end=ip4parse(range.substr(pos+1));
		setlen();
	}
}

void NESCARAWRANGEV4::setlen(void)
{
	size_t count=1;
	count*=(this->end[0]-this->start[0]+1);
	if (this->start[0]==this->end[0])
		count*=(this->end[1]-this->start[1]+1);
	else {
		count*=(256-this->start[1]);
		count+=(this->end[1]+1);
		count+=(this->end[0]-this->start[0]-1)*256;
	}
	if (this->start[0]==this->end[0]&&this->start[1]==this->end[1])
		count*=(this->end[2]-this->start[2]+1);
	else {
		count*=(256-this->start[2]);
		count+=(this->end[2]+1);
		count+=(this->end[1]-this->start[1]-1)*256;
	}
	if (this->start[0]==this->end[0]&&this->start[1]==this->end[1]&&this->start[2]==this->end[2])
		count*=(this->end[3]-this->start[3]+1);
	else {
		count*=(256-this->start[3]);
		count+=(this->end[3]+1);
		count+=(this->end[2]-this->start[2]-1)*256;
	}
	len=count;
}

size_t NESCARAWRANGEV4::getlen(void)
{
	return this->len;
}

std::vector<std::string> NESCARAWRANGEV4::exportips(size_t start, size_t num)
{
	std::vector<std::string>	res, exclude;
	size_t				skipped=0, added=0;
	std::string			ret;
	int				i,j,k,l;

	/* this shit but work */
	for (i=this->start[0];i<=this->end[0];++i) {
		for (j=(i==this->start[0]?this->start[1]:0);
				j<=(i==this->end[0]?this->end[1]:255);++j) {
			for (k=(i==this->start[0]&&j==this->start[1]?
						this->start[2]:0);k<=(i==this->end[0]&&
							j==this->end[1]?this->end[2]:255);++k) {
				for (l=(i==this->start[0]&&j==this->start[1]&&
							k==this->start[2]?this->start[3]:0);l<=
						(i==this->end[0]&&j==this->end[1]&&k==
						 this->end[2]?this->end[3]:255);++l) {
					if (skipped<start-1) {
						++skipped;
						continue;
					}
					ret=ip4unparse({i, j, k, l});
					res.push_back(ret);
					++added;
					if (added>=num) {
						this->last=(added+skipped+1);
						return res;
					}
				}
			}
		}
	}

	return res;
}

void NESCARAWRANGEV4::init_cidr(const std::string &cidr)
{
	char	res[1024];
	cidr_t	*c;

	c=cidr_from_str(cidr.c_str());
	if (!c)
		return;
	cidr_to_str_range(c, res, sizeof(res));
	cidr_free(c);

	this->cidr=1;
	init(res);
}

NESCARAWRANGEV4::NESCARAWRANGEV4(const std::string &txt, bool cidr)
{
	if (cidr)
		init_cidr(txt);
	else
		init(txt);
}

size_t NESCARAWRANGEV4::getlast(void)
{
	return this->last;
}


/*
 * From this ipv6: 2001:db8:a::123
 * Return this ipv6: 2001:0db8:000a:0000:0000:0000:0000:0123
 */
std::string NESCARAWRANGEV6::ip6uncompact(const std::string &ipv6)
{
	std::vector<std::string>	blocks;
	std::stringstream		ss(ipv6);
	size_t				miss=0, i, j;
	std::string			segment;
	std::string			res;
	bool				dc=0;

	if (ipv6.find("::")==std::string::npos)
		return ipv6;

	while (std::getline(ss, segment, ':')) {
		if (segment.empty()&&!dc) {
			dc=1;
			blocks.push_back("");
		}
		else if (!segment.empty())
			blocks.push_back(segment);
	}
	miss=8-blocks.size();
	for (i=0;i<blocks.size();++i) {
		if (blocks[i].empty()) {
			for (j=0;j<=miss;++j)
				res+="0000:";
		}
		else res+=std::string(4-blocks[i].length(),
			'0')+blocks[i]+":";
	}
	if (!res.empty()&&res.back()==':')
		res.pop_back();

	return res;
}


/*
 * Split ipv6 address on neight octets.
 */
std::array<int, 8> NESCARAWRANGEV6::ip6parse(const std::string &ip)
{
	std::array<int, 8>	octets={0, 0, 0, 0, 0, 0, 0 ,0};
	std::stringstream	ss(ip);
	std::string		octet="";
	int			i=0;

	while (std::getline(ss, octet, ':')&&i<8)
		octets[i++]=std::stoi(octet, nullptr, 16);

	/*
	 * cidr auto do this
	 * remove broadcast and expanded
	 */
	if (!this->cidr) {
		if (octets[7]==0)
			octets[7]++;
		else
			octets[7]--;
	}

	return octets;
}

#include <iomanip>


/*
 * Collect ipv6 address from octets
 */
std::string NESCARAWRANGEV6::ip6unparse(const std::array<int,8> &octets)
{
	std::stringstream	ss;
	size_t			i;

	ss<<std::hex;
	for (i=0;i<octets.size();++i) {
		if (i>0) ss<<":";
		ss<<std::setw(4)<<std::setfill('0')<<octets[i];
	}

	return ss.str();
}


/*
 * Getting ipv6 range len
 */
void NESCARAWRANGEV6::setlen(void)
{
	u128	startnum=0, endnum=0, res=0;
	size_t	i=0;

	for (;i<8;++i) {
		startnum=(startnum<<16)|static_cast<uint64_t>(start[i]);
		endnum=(endnum<<16)|static_cast<uint64_t>(end[i]);
	}
	res=endnum-startnum+1;
	this->len=res;
}


void NESCARAWRANGEV6::init(const std::string &range)
{
	std::string ret1, ret2;
	std::size_t pos=0;
	pos=range.find('-');
	if (pos!=std::string::npos) {
		ret1=ip6uncompact(range.substr(0, pos));
		ret2=ip6uncompact(range.substr(pos+1));
		this->start=ip6parse(ret1);
		this->end=ip6parse(ret2);
		setlen();
	}
}

void NESCARAWRANGEV6::init_cidr(const std::string &cidr)
{
	char	res[1024];
	cidr_t	*c;

	c=cidr_from_str(cidr.c_str());
	if (!c)
		return;
	cidr_to_str_range(c, res, sizeof(res));
	std::cout << res << std::endl;
	cidr_free(c);

	this->cidr=1;
	init(res);
}

NESCARAWRANGEV6::NESCARAWRANGEV6(const std::string &txt, bool cidr)
{
	if (cidr)
		init_cidr(txt);
	else
		init(txt);
}

std::vector<std::string> NESCARAWRANGEV6::exportips(u128 start, u128 num)
{
	std::vector<std::string>	res;
	int				i, j, k, l, m, n, o, p;
	u128				skipped=0, added=0;
	std::string			ret="";

	/* it's holy shit */
	for (i=this->start[0];i<=this->end[0];++i){
		for(j=(i==this->start[0]?this->start[1]:0);j<=(i==this->end[0]?this->end[1]:0xffff);++j){
			for(k=(i==this->start[0]&&j==this->start[1]?this->start[2]:0);k<=(i==this->end[0]&&j==this->end[1]?this->end[2]:0xffff);++k){
				for(l=(i==this->start[0]&&j==this->start[1]&&k==this->start[2]?this->start[3]:0);l<=(i==this->end[0]&&j==this->end[1]&&k==this->end[2]?this->end[3]:0xffff);++l){
					for(m=(i==this->start[0]&&j==this->start[1]&&k==this->start[2]&&l==this->start[3]?this->start[4]:0);m<=(i==this->end[0]&&j==this->end[1]&&k==this->end[2]&&
							l==this->end[3]?this->end[4]:0xffff);++m){
						for(n=(i==this->start[0]&&j==this->start[1]&&k==this->start[2]&&l==this->start[3]&&m==this->start[4]?this->start[5]:0);n<=(i==this->end[0]&&j==
								this->end[1]&&k==this->end[2]&&l==this->end[3]&&m==this->end[4]?this->end[5]:0xffff);++n){
							for(o=(i==this->start[0]&&j==this->start[1]&&k==this->start[2]&&l==this->start[3]&&m==this->start[4]&&n==this->start[5]?this->start[6]:0);o<=
								(i==this->end[0]&&j==this->end[1]&&k==this->end[2]&&l==this->end[3]&&m==this->end[4]&&n==this->end[5]?this->end[6]:0xffff);++o){
								for(p=(i==this->start[0]&&j==this->start[1]&&k==this->start[2]&&l==this->start[3]&&m==this->start[4]&&n==this->start[5]&&o==this->start[6]?
										this->start[7]:0);p<=(i==this->end[0]&&j==this->end[1]&&k==this->end[2]&&l==this->end[3]&&m==this->end[4]&&n==this->end[5]&&o==this->
										 end[6]?this->end[7]:0xffff);++p){
									if (skipped<start-1) {
										++skipped;
										continue;
									}
									ret=ip6unparse({i, j, k, l, m, n, o, p});
									res.push_back(ret);
									++added;
									if (added>=num) {
										this->last=added+skipped+1;
										return res;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return res;
}

u128 NESCARAWRANGEV6::getlen(void)
{
	return this->len;
}

u128 NESCARAWRANGEV6::getlast(void)
{
	return this->last;
}

void NESCARAWTARGETS::load_from_file(size_t num)
{
	std::vector<std::string> tmp;
	if (check_from_file&&lastfileline<=filelines) {
		if (num>filelines)
			num=filelines;
		tmp=fileparse(from_file, lastfileline, num);
		if (!tmp.empty()) {
			lastfileline+=num;
			processing(tmp);
		}
	}
}

void NESCARAWTARGETS::load_random_ips(size_t num)
{
	std::vector<std::string>	tmp;
	std::string			ret;
	size_t				i=1;

	if (check_randomips&&randomips>0) {
		if (num>(size_t)randomips)
			num=randomips;
		for (;i<=num;i++) {
			ret=random_ip4();
			tmp.push_back(ret);
		}
		if (!tmp.empty())
			processing(tmp);
		randomips-=num;
	}
}

std::vector<std::string> NESCARAWTARGETS::unload(u128 num)
{
	std::vector<std::string>	res;
	u128				maxnum=0, j=0, x=0;

	maxnum=totlen();
	if (num<=0)
		return {};
	if (num>maxnum)
		j=maxnum;
	else
		j=num;

	if (!grouptargets.empty()) {
writecidr:
		if (j&&lastgroup<=(grouptargets.size()-1)) {
#define p grouptargets[lastgroup]
			x=(p.getlen()-p.getlast())+1;

			if (x==j) {
				copyvec(p.exportips(p.getlast(),j), res);
				lastgroup++;
				j=0;
				goto writecidr;
			}

			if (x>j) {
				copyvec(p.exportips(p.getlast(),j), res);
				j=0;
				goto writecidr;
			}

			if (x<j) {
				copyvec(p.exportips(p.getlast(),x), res);
				j-=x;
				lastgroup++;
				goto writecidr;
			}
		}
#undef p
	}
	if (!grouptargets6.empty()) {
writecidr6:
		if (j&&lastgroup6<=(grouptargets6.size()-1)) {
#define p grouptargets6[lastgroup6]
			x=(p.getlen()-p.getlast())+1;

			if (x==j) {
				copyvec(p.exportips(p.getlast(),j), res);
				lastgroup6++;
				j=0;
				goto writecidr6;
			}

			if (x>j) {
				copyvec(p.exportips(p.getlast(),j), res);
				j=0;
				goto writecidr6;
			}

			if (x<j) {
				copyvec(p.exportips(p.getlast(),x), res);
				j-=x;
				lastgroup6++;
				goto writecidr6;
			}
		}
#undef p
	}
	if (!ipv4.empty()&&j) {
writeip4:
		if (j&&lastip4<=(ipv4.size()-1)) {
			res.push_back(ipv4[lastip4++]);
			j--;
			goto writeip4;
		}
	}
	if (!ipv6.empty()&&j) {
writeip6:
		if (j&&lastip6<=(ipv6.size()-1)) {
			res.push_back(ipv6[lastip6++]);
			j--;
			goto writeip6;
		}
	}
	return res;
}

void NESCADEVICE::init(NESCAPRINT *ncsprint, NESCAOPTS *ncsopts)
{
	std::vector<std::string> devices;
	std::string index;

	/* clear */
	memset(this->srcip4.octet,	 0, 4);
	memset(this->srcip6.octet,	 0, 16);
	memset(this->gateway4.octet, 0, 4);
	memset(this->gateway6.octet, 0, 16);
	memset(this->srcmac.octet,	 0, 6);
	memset(this->dstmac.octet,	 0, 6);

	/* device setting */
	this->ncsprint=ncsprint;
	if (!ncsopts->check_dev_flag()) {
		devices=find_devices();
		for (const auto&d:devices)
			if (is_okdevice(d, 0))
				this->device=d;
	}
	else
		if (is_okdevice(ncsopts->get_dev_param(), 1))
			this->device=ncsopts->get_dev_param();
	init_device(this->device, ncsopts);
	if (ncsopts->check_v_flag())
		ncsprint->nescadevice(this);
}

typedef struct ___arp_arg {
	ip4_t tpa;
} __arp_arg;

static bool __received_arp_callback(u8 *frame, size_t frmlen, void *arg)
{
	__arp_arg *n=(__arp_arg*)arg;
	arp_op_request_ethip *arpreq;
	mach_t *datalink;

	if (frmlen<14)
		return 0;

	datalink=(mach_t*)frame;

	/* The payload type will definitely be ARP */
	if (ntohs(datalink->type)!=ETH_TYPE_ARP)
		return 0;

	/*
	 * The ip4 address of the recipient inside
	 * the ARP request must match the local ip4
	 * address, otherwise, the packet was not
	 * addressed to us.
	 */
	arpreq=(arp_op_request_ethip*)((frame)+(sizeof(mach_t)+sizeof(arph_t)));
	if (!ip4t_compare(arpreq->tpa, n->tpa))
		return 0;

	return 1;
}


/*
 * Gets dest mac address by 3 methods, first is
 * reading cache /proc/net/arp on gateway4, second
 * is arp request on gateway4, third is output
 * of arp command on gateway4.
 */
bool NESCADEVICE::dstmac4_at_all_costs(void)
{
	arp_op_request_ethip	*arpreq;
	u8			*arp, *buf;
	size_t			arplen=0;
	mac_t			srcmaceth;
	mac_t			srcmacarp;
	eth_t			*fd;
	__arp_arg		arg;
	ip4_t			tpa;
	lr_t			*lr;
	bool			get=0;
	FILE			*fp;
	char			ip[32], hw_type[32];
	char			flags[32], mac[32];
	char			mask[32], dev[32], line[256];
	ip4_t			tmp;
	std::string		cmd;

	tmp=get_gateway4();
	tpa=get_srcip4();


	/*
	 * Reading /proc/net/arp
	 */
	fp=fopen("/proc/net/arp", "r");
	if (!fp)
		goto nxt;
	fgets(line, sizeof(line), fp);
	while (fgets(line, sizeof(line), fp)) {
		sscanf(line, "%31s %31s %31s %31s %31s %31s", ip, hw_type, flags, mac, mask, dev);
		if (strcmp(dev, device.c_str()))
			continue;
		if (strcmp(ip, ip4t_ntop_c(&tmp)))
			continue;
		get=1;
		break;
	}
	fclose(fp);
	if (get) {
		mact_pton(mac, &this->dstmac);
		return get;
	}

nxt:


	/*
	 * arp req
	 */
	fd=eth_open(device.c_str());
	if (!fd)
		goto nxt1;
	lr=lr_open(device.c_str(), to_ns(50));
	if (!lr) {
		eth_close(fd);
		goto nxt1;
	}
	mact_fill(&srcmaceth, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff);
	mact_fill(&srcmacarp, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	arp=arp_ethip4_build_pkt(get_srcmac(), srcmaceth, ARP_OP_REQUEST,
		get_srcmac(), tpa, srcmacarp, get_gateway4(),
		&arplen);
	if (!arp) {
		eth_close(fd);
		lr_close(lr);
		goto nxt1;
	}
	eth_send(fd, arp, arplen);
	free(arp);
	ip4t_copy(&arg.tpa, &tpa);
	lr_callback(lr, __received_arp_callback);
	buf=(u8*)calloc(1, 1024);
	if (!buf) {
		eth_close(fd);
		lr_close(lr);
		goto nxt1;
	}
	if (lr_live(lr, &buf, 1024, &arg)>0) {
		arpreq=(arp_op_request_ethip*)((buf)+(sizeof(mach_t)
			+sizeof(arph_t)));
		mact_copy(&this->dstmac, &arpreq->sha);
		get=1;
	}
	free(buf);
	eth_close(fd);
	lr_close(lr);
	if (get)
		return get;

nxt1:


	/*
	 * arp -n
	 */
	memset(line, 0, sizeof(line));
	line[0]='\0';
	cmd="arp -n | grep '" +std::string(ip4t_ntop_c(&tmp))
		+ "[ \\t]' | awk '{print $3}'";
	fp=popen(cmd.c_str(), "r");
	fgets(line, sizeof(line), fp);
	pclose(fp);
	if (line[0]!='\0')
		if (strlen(line)>5)
			get=1;
	if (get)
		mact_pton(line, &this->dstmac);

	return get;
}



/*
 * The function to get the source ip 4 address of a particular
 * interface, uses three methods to do this, system call via
 * ioctl, brute force via getifaddrs, and netlink message.
 */
bool NESCADEVICE::srcip4_at_all_costs(void)
{
	struct ifaddrs		*ifaddr, *ifa;
	struct ifreq		ifr;
	bool			res=0;
	int			fd, len, rta_len;
	struct sockaddr_nl	sa;
	struct iovec		iov;
	struct msghdr		msg;
	struct nlmsghdr		*nlh;
	char			buf[8192];
	struct			nlmsg_list {
		struct nlmsghdr		*nlmsg;
		struct nlmsg_list	*next;
	};


	/*
	 * Receive via system call, on the desired interface
	 * from the socket
	 */
	strncpy(ifr.ifr_name, device.c_str(), IFNAMSIZ-1);
	fd=socket(AF_INET, SOCK_DGRAM, 0);
	if (fd<=0)
		goto nxt;
	if (ioctl(fd, SIOCGIFADDR, &ifr)==0) {
		if (ifr.ifr_addr.sa_family==AF_INET) {
			struct sockaddr_in *ip_addr=(struct sockaddr_in *)&ifr.ifr_addr;
			memcpy(srcip4.octet, &ip_addr->sin_addr.s_addr, 4);
			res=1;
		}
	}
	close(fd);
	if (res)
		return res;

nxt:


	/*
	 * Receipt via getifaddrs
	 */
	if (getifaddrs(&ifaddr)==-1)
		goto nxt1;
	for (ifa=ifaddr;ifa;ifa=ifa->ifa_next) {
		if (ifa->ifa_name&&strcmp(ifa->ifa_name,device.c_str())==0) {
			if (ifa->ifa_addr->sa_family==AF_INET) {
				memcpy(this->srcip4.octet,
					&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, 4);
				res=1;
			}
		}
	}
	freeifaddrs(ifaddr);
	if (res)
		return res;

nxt1:


	/*
	 * Receive using netlink message and bruteforce
	 */
	fd=socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
	if (fd<=0)
		return res;
	memset(&sa, 0, sizeof(sa));
	sa.nl_family=AF_NETLINK;
	nlh=(struct nlmsghdr *)buf;
	nlh->nlmsg_len=NLMSG_LENGTH(sizeof(struct rtgenmsg));
	nlh->nlmsg_type=RTM_GETADDR;
	nlh->nlmsg_flags=NLM_F_REQUEST|NLM_F_DUMP;
	nlh->nlmsg_seq=1;
	nlh->nlmsg_pid=getpid();
	memset(&iov, 0, sizeof(iov));
	iov.iov_base=nlh;
	iov.iov_len=nlh->nlmsg_len;
	memset(&msg, 0, sizeof(msg));
	msg.msg_name=&sa;
	msg.msg_namelen=sizeof(sa);
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;
	if (sendmsg(fd, &msg, 0)<0)
		goto exit;
	for (;;) {
		len=recv(fd, buf, sizeof(buf), 0);
		if (len<0)
			goto exit;
		struct nlmsghdr *nlh=(struct nlmsghdr *)buf;
		while (NLMSG_OK(nlh, len)) {
			if (nlh->nlmsg_type==NLMSG_DONE)
				break;
			if (nlh->nlmsg_type==NLMSG_ERROR)
				goto exit;
			struct ifaddrmsg *ifa=(struct ifaddrmsg *)NLMSG_DATA(nlh);
			struct rtattr *rta=(struct rtattr *)IFA_RTA(ifa);
			rta_len=IFA_PAYLOAD(nlh);
			for (;RTA_OK(rta, rta_len);rta=RTA_NEXT(rta, rta_len)) {
				if (rta->rta_type==IFA_LOCAL) {
					if ((int)ifa->ifa_index!=deviceindex)
						continue;
					memcpy(this->srcip4.octet, RTA_DATA(rta), 4);
					res=1;
					goto exit;
				}
			}
			nlh=NLMSG_NEXT(nlh, len);
		}
		if (nlh->nlmsg_type==NLMSG_DONE)
			break;
	}

exit:
	close(fd);
	return res;
}


/*
 * Gets the source mac address using three methods, first
 * by calling ioctl, second by reading /sys/class/net,
 * and third by gettingifaddrs.
 */
bool NESCADEVICE::srcmac_at_all_costs(void)
{
	struct ifreq	ifr;
	bool		res=0;
	int		fd, family;
	std::string	addr, addrlen;
	struct ifaddrs	*ifaddr, *ifa;


	/*
	 * Receive use system call on desired interface
	 */
	strncpy(ifr.ifr_name, device.c_str(), IFNAMSIZ-1);
	fd=socket(AF_INET, SOCK_DGRAM, 0);
	if (fd<=0)
		goto nxt;
	if (ioctl(fd, SIOCGIFHWADDR, &ifr)==0) {
		memcpy(this->srcmac.octet,
			ifr.ifr_ifru.ifru_hwaddr.sa_data, 6);
		res=1;
	}
	close(fd);
	if (res)
		return res;

nxt:


	/*
	 * Receive from /sys/class/net/<interface_name>/address
	 */
	addrlen=getfileln("/sys/class/net/"+this->device+"/addr_len");
	if (!addrlen.empty()&&(std::stoi(addrlen))==6) {
		addr=getfileln("/sys/class/net/"+this->device+"/address");
		if (!addr.empty()) {
			mact_pton(addr.c_str(), &this->srcmac);
			res=1;
		}
	}
	if (res)
		return res;


	/*
	 * Receipt via getifaddrs
	 */
	if (getifaddrs(&ifaddr)==-1)
		return res;
	for (ifa=ifaddr;ifa;ifa=ifa->ifa_next) {
		if (!ifa->ifa_addr)
			continue;
		family=ifa->ifa_addr->sa_family;
		if (family==AF_PACKET&&ifa->ifa_data&&!strcmp(ifa->ifa_name, device.c_str())) {
			struct sockaddr_ll *s=(struct sockaddr_ll *)ifa->ifa_addr;
			mact_fill(&this->srcmac, s->sll_addr[0], s->sll_addr[1], s->sll_addr[2],
				s->sll_addr[3], s->sll_addr[4], s->sll_addr[5]);
			res=1;
		}
	}
	freeifaddrs(ifaddr);

	return res;
}


/*
 * Cut string like kajsdf%123
 * to kajsdf
 */
static std::string __cutp(const std::string& input)
{
	size_t pos=input.find('%');
	if (pos!=std::string::npos)
		return input.substr(0, pos);
	return input;
}


/*
 * The function to get the source ip 6 address of a particular
 * interface, uses two methods to do this, reading the
 * /proc/net/if_inet6 file, and bruteforce through
 * getifaddrs.
 */
bool NESCADEVICE::srcip6_at_all_costs(void)
{
	u32		index, prefix_len, scope, flags, i;
	char		addr[32+1];
	std::string	addrt, addr_s;
	char		iface[40];
	struct ifaddrs	*ifaddr, *ifa;
	char		host[NI_MAXHOST];
	bool		res=0;
	FILE		*f;


	/*
	 * Receive from /proc/net/if_inet6
	 */
	f=fopen("/proc/net/if_inet6", "r");
	if (!f)
		goto nxt;
	while (fscanf(f, "%32s %x %x %x %x %19s", addr, &index,
			 &prefix_len, &scope, &flags, iface)==6) {
		if (strcmp(iface, device.c_str()))
			continue;
		addrt=addr;
		for (i=0;i<addrt.size();i+=4) {
			addr_s+=addrt.substr(i, 4);
			if (i+4<addrt.size())
				addr_s+=":";
		}
		ip6t_pton(addr_s.c_str(), &this->srcip6);
		res=1;
		break;
	}
	fclose(f);
	if (res)
		return res;

nxt:


	/*
	 * Receipt via getifaddrs
	 */
	if (getifaddrs(&ifaddr)==-1)
		return res;
	for (ifa=ifaddr;ifa;ifa=ifa->ifa_next) {
		if (!ifa->ifa_addr)
			continue;
		if (strcmp(ifa->ifa_name, device.c_str())==0&&
				ifa->ifa_addr->sa_family==AF_INET6) {
			if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in6),
					 host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)==0) {
				std::string tmp=host;
				tmp=__cutp(tmp);
				ip6t_pton(tmp.c_str(), &this->srcip6);
				res=1;
				goto exit;
			}
		}
	}

exit:
	freeifaddrs(ifaddr);
	return res;
}


/*
 * Gets gateway ipv4 address to 0.0.0.0.0 (internet) using two
 * methods. First by reading /proc/net/route, second by
 * netlink message.
 */
bool NESCADEVICE::gateway4_at_all_costs(void)
{
	char			iface_buffer[IFNAMSIZ];
	unsigned long		dest, gate;
	char			line[1024];
	bool			res=0;
	FILE			*f;
	int			fd;
	u32			i;
	struct nlmsghdr		*nmsg;
	struct rtmsg		*rmsg;
	struct rtattr		*rta;
	struct sockaddr_nl	snl;
	struct iovec		iov;
	struct msghdr		msg;
	u8			buf[512];
	static u32		seq;


	/*
	 * Receive using read /proc/net/route
	 */
	memset(line, 0, sizeof(line));
	f=fopen("/proc/net/route", "r");
	if (!f)
		goto nxt;
	fgets(line, sizeof(line), f);
	while (fgets(line, sizeof(line), f)) {
		if (sscanf(line, "%s %lx %lx", iface_buffer, &dest, &gate)!=3)
			continue;
		if (dest==0) {
			if (strcmp(device.c_str(), iface_buffer)!=0)
				continue;
			u32_ip4t(gate, &this->gateway4);
			res=1;
			break;
		}
	}
	fclose(f);
	if (res)
		return res;

nxt:


	/*
	 * Receive using netlink message
	 */
	fd=socket(AF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);
	if (fd<=0)
		return 0;
	 memset(buf, 0, sizeof(buf));
	nmsg=(struct nlmsghdr*)buf;
	nmsg->nlmsg_len=NLMSG_LENGTH(sizeof(*nmsg))+RTA_LENGTH(4);
	nmsg->nlmsg_flags=NLM_F_REQUEST;
	nmsg->nlmsg_type=RTM_GETROUTE;
	nmsg->nlmsg_seq=++seq;
	rmsg=(struct rtmsg*)(nmsg+1);
	rmsg->rtm_family=AF_INET;
	rmsg->rtm_dst_len=32; /* 4 XXX*/
	rta=RTM_RTA(rmsg);
	rta->rta_type=RTA_DST;
	rta->rta_len=RTA_LENGTH(4);
	/* gross hack for default route */
	i=htonl(0x60060606);
	memcpy(RTA_DATA(rta), &i, 4);
	memset(&snl, 0, sizeof(snl));
	snl.nl_family=AF_NETLINK;
	iov.iov_base=nmsg;
	iov.iov_len=nmsg->nlmsg_len;
	memset(&msg, 0, sizeof(msg));
	msg.msg_name=&snl;
	msg.msg_namelen=sizeof(snl);
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;
	if (sendmsg(fd, &msg, 0)<0)
		goto exit;
	iov.iov_base=buf;
	iov.iov_len=sizeof(buf);
	if ((i=recvmsg(fd, &msg, 0))<=0)
		goto exit;
	if (nmsg->nlmsg_len<(int)sizeof(*nmsg)||nmsg->nlmsg_len>i||nmsg->nlmsg_seq!=seq)
		goto exit;
	if (nmsg->nlmsg_type==NLMSG_ERROR)
		goto exit;
	i-=NLMSG_LENGTH(sizeof(*nmsg));
	while (RTA_OK(rta, i)) {
		if (rta->rta_type==RTA_OIF)
			if (*(int*)RTA_DATA(rta)!=deviceindex)
				continue;
		if (rta->rta_type==RTA_GATEWAY) {
			memcpy(this->gateway4.octet, RTA_DATA(rta), 4);
			res=1;
			goto exit;
		}
		rta=RTA_NEXT(rta, i);
	}

exit:
	close(fd);
	return res;

}


bool NESCADEVICE::gateway6_at_all_costs(void)
{
	char	line[1024], dest6[33], gate6[33], mask[9], flags[5];
	char	iface_buffer[IFNAMSIZ];
	FILE	*f;
	bool	res=0;

	memset(line, 0, sizeof(line));
	f=fopen("/proc/net/ipv6_route", "r");
	if (!f)
		return res;
	while (fgets(line, sizeof(line), f)) {
		sscanf(line, "%32s %8s %32s %4s %*s %*s %*s %*s %*s %s", dest6, mask, gate6, flags, iface_buffer);
		if (strcmp(dest6, "00000000000000000000000000000000")==0) {
			if (strcmp(iface_buffer, device.c_str())!=0)
				continue;
			struct in6_addr gateway_addr;
			sscanf(gate6, "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
				&gateway_addr.s6_addr[0], &gateway_addr.s6_addr[1], &gateway_addr.s6_addr[2], &gateway_addr.s6_addr[3],
				&gateway_addr.s6_addr[4], &gateway_addr.s6_addr[5], &gateway_addr.s6_addr[6], &gateway_addr.s6_addr[7],
				&gateway_addr.s6_addr[8], &gateway_addr.s6_addr[9], &gateway_addr.s6_addr[10], &gateway_addr.s6_addr[11],
				&gateway_addr.s6_addr[12], &gateway_addr.s6_addr[13], &gateway_addr.s6_addr[14], &gateway_addr.s6_addr[15]);
			memcpy(this->gateway6.octet, gateway_addr.s6_addr, 16);
			res=1;
			break;
		}
	}

	fclose(f);
	return res;
}


bool NESCADEVICE::dstmac6_at_all_costs(void)
{
	return 0;
}


void NESCADEVICE::init_device(const std::string &device, NESCAOPTS *ncsopts)
{
	bool ipv4=0, ipv6=0, gwipv4=0, gwipv6=0;

	/* getting interface index */
	this->deviceindex=if_nametoindex(device.c_str());
	if (deviceindex==0) {
		std::string index="";
		index=getfileln("/sys/class/net/"+this->device+"/ifindex");
		if (!index.empty())
			this->deviceindex=std::stoi(index);
		else
			this->ncsprint->error("nesca4 could not get device index");
	}

	/* other */
	if (ncsopts->check_src_flag())
		set_srcmac(ncsopts->get_src_param());
	else
		if (!srcmac_at_all_costs())
			this->ncsprint->error("nesca4 could not get source mac address");
	if (ncsopts->check_ip4_flag()) {
		set_srcip4(ncsopts->get_ip4_param());
		ipv4=1;
	}
	else
		ipv4=srcip4_at_all_costs();
	if (ncsopts->check_ip6_flag()) {
		set_srcip6(ncsopts->get_ip6_param());
		ipv6=1;
	}
	else
		ipv6=srcip6_at_all_costs();
	if (!ipv4&&!ipv6)
		this->ncsprint->error("nesca4 could not get ipv4 or ipv6 address");

	if (!ncsopts->check_dst_flag()) {
		if (ipv4) {
			gwipv4=gateway4_at_all_costs();
			if (gwipv4)
				this->ip4=1;
		}
		if (ipv6) {
			gwipv6=gateway6_at_all_costs();
			if (ip6t_isglobal(&this->srcip6)&&gwipv6)
				this->ip6=1;
		}
		if (!gwipv4&&!gwipv6)
			this->ncsprint->error("nesca4 could not get ipv4 or ipv6 gateway address");
		if (gwipv4&&ipv4)
			if (!dstmac4_at_all_costs())
				this->ncsprint->error("nesca4 could not get dest mac address");
		/* TODO getting dstmac with ipv6 */
	}

	/*
	 * user myself set dst mac
	 */
	else {
		set_dstmac(ncsopts->get_dst_param());
		if (ipv4)
			this->ip4=1;
		if (ipv6)
			this->ip6=1;
	}

	/* set_send_at() */
	this->send_at=77090; /* for example*/
}

long long NESCADEVICE::get_send_at(void)
{
	return this->send_at;
}

void NESCADEVICE::set_send_at(void)
{
	u8 test[1454]= {
		0x04,0xbf,0x6d,0x0d,0x3a,0x50,0x40,0xb0,0x76,0x47,
		0x8f,0x9a,0x08,0x00,0x45,0x00,0x05,0xa0,0xf6,0x98,
		0x00,0x00,0x37,0x06,0xec,0xac,0xc0,0xa8,0x01,0x22,
		0x8e,0xfa,0x4a,0x4e,0xe1,0x02,0x00,0x01,0x72,0x5d,
		0xb6,0x6b,0x00,0x00,0x00,0x00,0x50,0x02,0x04,0x00,
		0x79,0x56,0x00,0x00,0x74,0x61,0x45,0x48,0x51,0x62,
		0x38,0x6a,0x32,0x74,0x30,0x4b,0x6a,0x4c,0x4c,0x6c,
		0x45,0x4e,0x6b,0x4e,0x47,0x41,0x45,0x77,0x48,0x76,
		0x4b,0x56,0x79,0x61,0x64,0x4f,0x54,0x32,0x6b,0x45,
		0x73,0x66,0x54,0x72,0x32,0x7a,0x72,0x34,0x37,0x51,
		0x61,0x51,0x4b,0x63,0x6b,0x77,0x63,0x32,0x57,0x4a,
		0x50,0x6c,0x39,0x30,0x68,0x4a,0x38,0x78,0x38,0x64,
		0x45,0x50,0x4a,0x6d,0x79,0x36,0x30,0x4f,0x42,0x65,
		0x66,0x4b,0x66,0x4c,0x53,0x58,0x71,0x64,0x6e,0x38,
		0x39,0x48,0x48,0x6c,0x63,0x52,0x7a,0x6d,0x4c,0x63,
		0x50,0x75,0x4f,0x4e,0x6a,0x39,0x45,0x55,0x54,0x57,
		0x50,0x30,0x75,0x6b,0x71,0x75,0x39,0x35,0x61,0x41,
		0x30,0x77,0x30,0x53,0x4c,0x42,0x4d,0x31,0x69,0x66,
		0x47,0x7a,0x49,0x37,0x51,0x6c,0x68,0x31,0x59,0x62,
		0x78,0x4a,0x47,0x4d,0x6e,0x4a,0x31,0x39,0x53,0x7a,
		0x62,0x32,0x35,0x4e,0x64,0x4a,0x31,0x6b,0x65,0x59,
		0x73,0x4e,0x79,0x63,0x58,0x39,0x31,0x56,0x4d,0x49,
		0x53,0x58,0x64,0x58,0x72,0x77,0x64,0x49,0x37,0x34,
		0x74,0x33,0x6c,0x32,0x52,0x59,0x32,0x7a,0x7a,0x47,
		0x42,0x57,0x75,0x64,0x59,0x49,0x41,0x73,0x53,0x69,
		0x49,0x72,0x78,0x74,0x4b,0x71,0x65,0x76,0x30,0x43,
		0x68,0x69,0x48,0x74,0x74,0x75,0x59,0x31,0x65,0x62,
		0x5a,0x42,0x36,0x70,0x54,0x72,0x39,0x63,0x47,0x51,
		0x4b,0x79,0x72,0x39,0x4c,0x4c,0x53,0x67,0x45,0x37,
		0x32,0x61,0x6d,0x37,0x4b,0x33,0x78,0x74,0x71,0x4c,
		0x6a,0x78,0x76,0x52,0x34,0x6f,0x4d,0x32,0x57,0x44,
		0x4b,0x69,0x61,0x6e,0x41,0x6a,0x4f,0x4c,0x61,0x4c,
		0x44,0x58,0x65,0x6b,0x6e,0x51,0x48,0x51,0x76,0x4a,
		0x72,0x57,0x30,0x38,0x34,0x36,0x4d,0x47,0x35,0x4f,
		0x4a,0x69,0x69,0x4f,0x32,0x6f,0x33,0x4f,0x75,0x62,
		0x55,0x6b,0x49,0x79,0x62,0x4e,0x6f,0x39,0x63,0x70,
		0x79,0x42,0x41,0x51,0x62,0x66,0x71,0x53,0x66,0x55,
		0x48,0x4e,0x79,0x52,0x5a,0x67,0x4e,0x46,0x78,0x48,
		0x47,0x70,0x63,0x4c,0x63,0x42,0x46,0x36,0x32,0x37,
		0x33,0x46,0x69,0x58,0x62,0x76,0x6c,0x74,0x6b,0x6a,
		0x4e,0x30,0x66,0x78,0x42,0x74,0x5a,0x62,0x32,0x78,
		0x7a,0x4e,0x59,0x39,0x33,0x39,0x4f,0x6a,0x78,0x42,
		0x4f,0x4e,0x46,0x5a,0x33,0x7a,0x37,0x4e,0x65,0x5a,
		0x7a,0x34,0x5a,0x78,0x6c,0x50,0x50,0x30,0x77,0x7a,
		0x51,0x46,0x4a,0x79,0x47,0x42,0x65,0x6e,0x47,0x52,
		0x59,0x58,0x56,0x32,0x78,0x64,0x69,0x44,0x63,0x6f,
		0x6e,0x4d,0x39,0x4d,0x33,0x36,0x58,0x45,0x75,0x76,
		0x6d,0x32,0x62,0x50,0x74,0x64,0x4f,0x53,0x6e,0x68,
		0x61,0x6c,0x33,0x59,0x56,0x5a,0x64,0x37,0x35,0x47,
		0x64,0x77,0x44,0x70,0x46,0x4f,0x55,0x4a,0x62,0x64,
		0x4f,0x70,0x59,0x52,0x49,0x59,0x6b,0x58,0x38,0x43,
		0x39,0x67,0x48,0x6b,0x54,0x52,0x6c,0x47,0x36,0x59,
		0x63,0x68,0x4a,0x56,0x45,0x64,0x4b,0x55,0x4a,0x4c,
		0x52,0x57,0x50,0x30,0x55,0x33,0x61,0x37,0x75,0x34,
		0x67,0x44,0x70,0x32,0x48,0x6a,0x76,0x73,0x78,0x73,
		0x67,0x62,0x56,0x47,0x41,0x69,0x47,0x73,0x69,0x47,
		0x4c,0x72,0x7a,0x71,0x74,0x4a,0x6a,0x75,0x64,0x50,
		0x44,0x6e,0x76,0x72,0x72,0x6a,0x33,0x59,0x62,0x69,
		0x50,0x30,0x54,0x38,0x7a,0x59,0x67,0x4f,0x30,0x78,
		0x66,0x55,0x42,0x4e,0x37,0x4a,0x4c,0x31,0x57,0x34,
		0x78,0x6b,0x52,0x44,0x4b,0x32,0x57,0x79,0x49,0x48,
		0x4b,0x4b,0x34,0x34,0x6a,0x43,0x4a,0x31,0x51,0x68,
		0x61,0x65,0x54,0x74,0x52,0x34,0x55,0x6f,0x65,0x4c,
		0x6c,0x59,0x66,0x6c,0x52,0x30,0x62,0x41,0x79,0x32,
		0x6c,0x31,0x41,0x74,0x55,0x6e,0x79,0x45,0x79,0x50,
		0x77,0x7a,0x6c,0x43,0x4b,0x6a,0x6d,0x55,0x34,0x36,
		0x4b,0x6d,0x6a,0x52,0x4b,0x47,0x69,0x55,0x53,0x32,
		0x53,0x67,0x36,0x4e,0x55,0x4c,0x48,0x77,0x34,0x7a,
		0x59,0x47,0x72,0x51,0x4f,0x69,0x6a,0x70,0x53,0x64,
		0x51,0x50,0x62,0x43,0x58,0x79,0x56,0x6d,0x4b,0x63,
		0x6f,0x34,0x78,0x55,0x47,0x45,0x47,0x69,0x5a,0x72,
		0x52,0x31,0x34,0x43,0x35,0x75,0x31,0x33,0x6b,0x56,
		0x38,0x6c,0x66,0x6a,0x54,0x78,0x6e,0x45,0x69,0x5a,
		0x32,0x69,0x5a,0x74,0x69,0x42,0x6d,0x6e,0x4b,0x70,
		0x38,0x58,0x6b,0x56,0x39,0x30,0x43,0x4a,0x44,0x35,
		0x69,0x55,0x57,0x4a,0x57,0x78,0x6e,0x70,0x7a,0x4c,
		0x4a,0x50,0x69,0x44,0x72,0x58,0x41,0x71,0x52,0x46,
		0x6c,0x77,0x63,0x66,0x69,0x4a,0x35,0x42,0x71,0x64,
		0x37,0x39,0x6e,0x66,0x62,0x35,0x79,0x66,0x36,0x67,
		0x69,0x42,0x4e,0x65,0x6e,0x4a,0x4d,0x6f,0x35,0x34,
		0x54,0x54,0x46,0x37,0x77,0x5a,0x7a,0x73,0x51,0x34,
		0x56,0x49,0x36,0x74,0x43,0x42,0x49,0x4c,0x68,0x31,
		0x30,0x59,0x38,0x31,0x48,0x59,0x51,0x4e,0x48,0x77,
		0x76,0x62,0x66,0x77,0x37,0x6c,0x70,0x75,0x51,0x44,
		0x35,0x61,0x5a,0x62,0x74,0x32,0x65,0x46,0x78,0x5a,
		0x70,0x61,0x4a,0x76,0x36,0x61,0x52,0x4f,0x69,0x71,
		0x75,0x5a,0x42,0x43,0x7a,0x70,0x4c,0x6e,0x63,0x31,
		0x47,0x67,0x49,0x4d,0x34,0x67,0x54,0x54,0x57,0x73,
		0x6b,0x33,0x42,0x6d,0x30,0x5a,0x36,0x39,0x52,0x32,
		0x73,0x4d,0x77,0x33,0x42,0x53,0x4e,0x62,0x74,0x4f,
		0x63,0x51,0x6d,0x6c,0x44,0x68,0x59,0x45,0x52,0x34,
		0x51,0x45,0x67,0x4c,0x68,0x42,0x46,0x33,0x77,0x71,
		0x4e,0x6f,0x79,0x49,0x35,0x70,0x65,0x42,0x41,0x68,
		0x4f,0x4e,0x69,0x70,0x6b,0x49,0x73,0x54,0x56,0x6a,
		0x44,0x46,0x6e,0x45,0x35,0x4a,0x35,0x4d,0x55,0x55,
		0x56,0x6e,0x6f,0x33,0x48,0x4d,0x75,0x59,0x57,0x54,
		0x76,0x46,0x53,0x78,0x32,0x45,0x68,0x7a,0x44,0x6c,
		0x4d,0x64,0x7a,0x33,0x55,0x56,0x67,0x62,0x4b,0x30,
		0x68,0x76,0x76,0x4a,0x73,0x52,0x4e,0x59,0x6d,0x34,
		0x35,0x55,0x7a,0x37,0x50,0x49,0x68,0x34,0x68,0x45,
		0x70,0x52,0x4f,0x4a,0x6b,0x6e,0x64,0x38,0x50,0x59,
		0x7a,0x64,0x69,0x76,0x36,0x47,0x4c,0x4d,0x6a,0x54,
		0x6e,0x6a,0x30,0x54,0x51,0x70,0x52,0x51,0x6f,0x57,
		0x43,0x43,0x66,0x61,0x46,0x59,0x61,0x56,0x68,0x4c,
		0x59,0x4b,0x56,0x59,0x57,0x37,0x64,0x61,0x38,0x64,
		0x64,0x57,0x69,0x67,0x50,0x45,0x6b,0x78,0x56,0x4a,
		0x70,0x71,0x79,0x73,0x68,0x59,0x48,0x4c,0x4c,0x52,
		0x38,0x56,0x7a,0x69,0x55,0x4d,0x34,0x59,0x44,0x71,
		0x6f,0x62,0x62,0x6b,0x5a,0x71,0x4a,0x41,0x54,0x6c,
		0x72,0x67,0x6b,0x58,0x6b,0x31,0x52,0x6d,0x66,0x49,
		0x55,0x31,0x69,0x51,0x6a,0x68,0x66,0x6c,0x71,0x4f,
		0x45,0x75,0x33,0x6c,0x67,0x41,0x6c,0x73,0x42,0x49,
		0x6d,0x4d,0x4a,0x44,0x48,0x66,0x48,0x75,0x4b,0x74,
		0x67,0x67,0x59,0x6c,0x66,0x74,0x76,0x68,0x78,0x39,
		0x6f,0x42,0x65,0x48,0x49,0x45,0x37,0x39,0x64,0x72,
		0x42,0x31,0x72,0x6a,0x51,0x46,0x4c,0x73,0x65,0x46,
		0x7a,0x42,0x42,0x57,0x4e,0x79,0x39,0x77,0x44,0x6a,
		0x79,0x37,0x6c,0x54,0x37,0x41,0x43,0x39,0x48,0x6e,
		0x56,0x68,0x59,0x69,0x30,0x41,0x74,0x52,0x41,0x72,
		0x49,0x51,0x51,0x73,0x66,0x6e,0x78,0x33,0x31,0x4e,
		0x39,0x59,0x4b,0x77,0x4a,0x47,0x6a,0x77,0x67,0x67,
		0x4b,0x74,0x33,0x73,0x61,0x4e,0x53,0x6f,0x61,0x73,
		0x4c,0x35,0x74,0x6e,0x59,0x74,0x4e,0x62,0x56,0x4f,
		0x59,0x79,0x77,0x53,0x4a,0x32,0x36,0x51,0x48,0x33,
		0x76,0x43,0x6d,0x7a,0x4c,0x33,0x33,0x56,0x68,0x49,
		0x6a,0x58,0x57,0x71,0x35,0x75,0x77,0x59,0x50,0x78,
		0x67,0x49,0x74,0x32,0x59,0x52,0x57,0x41,0x6b,0x46,
		0x58,0x69,0x77,0x4e,0x34,0x73,0x41,0x34,0x77,0x4c,
		0x58,0x39,0x35,0x46,0x4f,0x73,0x42,0x62,0x57,0x54,
		0x74,0x6c,0x6e,0x6a,0x78,0x59,0x4c,0x4f,0x57,0x31,
		0x41,0x62,0x63,0x61,0x4d,0x61,0x4e,0x42,0x71,0x6c,
		0x45,0x45,0x57,0x63,0x38,0x55,0x50,0x4b,0x4d,0x48,
		0x31,0x30,0x54,0x36,0x65,0x59,0x64,0x44,0x5a,0x68,
		0x58,0x6c,0x70,0x6f,0x6e,0x52,0x36,0x6e,0x4a,0x53,
		0x5a,0x6f,0x69,0x74,0x48,0x38,0x67,0x4d,0x71,0x46,
		0x54,0x64,0x6b,0x46,0x67,0x56,0x36,0x69,0x58,0x55,
		0x74,0x59,0x58,0x62,0x6e,0x4f,0x4e,0x6d,0x6f,0x6c,
		0x32,0x73,0x46,0x54,0x45,0x43,0x30,0x47,0x32,0x69,
		0x52,0x44,0x4e,0x77,0x33,0x54,0x58,0x45,0x4d,0x52,
		0x65,0x67,0x63,0x43,0x4e,0x71,0x4c,0x46,0x61,0x45,
		0x49,0x65,0x78,0x71,0x32,0x62,0x44,0x4d,0x7a,0x57,
		0x61,0x38,0x63,0x79,0x78,0x69,0x57,0x51,0x5a,0x6b,
		0x53,0x72,0x61,0x50,0x63,0x72,0x65,0x73,0x6e,0x6a,
		0x52,0x43,0x53,0x30,0x41,0x6f,0x72,0x4b,0x67,0x55,
		0x39,0x5a,0x79,0x74,0x4d,0x69,0x33,0x58,0x32,0x45,
		0x68,0x49,0x69,0x4a
	};

	long long start_ns, end_ns;
	struct timeval s, e;
	mac_t src, dst;
	eth_t *eth;

	eth=eth_open(device.c_str());

	src=get_srcmac();
	dst=get_dstmac();

	/* just to router skip */
	test[0]=mact_getid(&src, 0);
	test[1]=mact_getid(&src, 1);
	test[2]=mact_getid(&src, 2);
	test[3]=mact_getid(&src, 3);
	test[4]=mact_getid(&src, 4);
	test[5]=mact_getid(&src, 5);
	test[6]=mact_getid(&dst, 0);
	test[7]=mact_getid(&dst, 1);
	test[8]=mact_getid(&dst, 2);
	test[9]=mact_getid(&dst, 3);
	test[10]=mact_getid(&dst, 4);
	test[11]=mact_getid(&dst, 5);

	gettimeofday(&s, NULL);
	eth_send(eth, test, sizeof(test));
	gettimeofday(&e, NULL);
	eth_close(eth);

	start_ns=static_cast<long long>(s.tv_sec)*1000000000LL+
		static_cast<long long>(s.tv_usec)*1000LL;
	end_ns=static_cast<long long>(e.tv_sec)*1000000000LL+
		static_cast<long long>(e.tv_usec)*1000LL;

	if ((end_ns-start_ns)>0)
		this->send_at=end_ns-start_ns;
	else
		this->send_at=77090; /* for example*/
}

bool NESCADEVICE::check_ipv4(void)
{
	return this->ip4;
}

std::string NESCADEVICE::getfileln(const std::string &path)
{
	std::ifstream	file(path);
	std::string	line;

	if (file.is_open()) {
		if (std::getline(file, line))
			return line;
		else
			return "";
	}
	else
		return "";
}

bool NESCADEVICE::is_okdevice(const std::string &device, bool err)
{
	std::string mainpath, flags, mtu;
	u32 realflags, j, realmtu;

	mainpath="/sys/class/net/"+device;
	realflags=j=realmtu=0;

	flags=getfileln(mainpath+"/flags");
	if (flags.empty()) {
		if (err)
			this->ncsprint->error("not found flags for \""+device+"\"!");
		return 0;
	}
	mtu=getfileln(mainpath+"/mtu");
	if (mtu.empty()) {
		if (err)
			this->ncsprint->error("not found mtu for \""+device+"\"!");
		return 0;
	}

	if (flags[0]=='0'&&(flags[1]=='x'||flags[1]=='X'))
		j=2;
	while(flags[j]!='\0') {
		realflags=(realflags<<4)|chex_atoh(flags[j]);
		j++;
	}

	if (!(realflags&IFF_UP)) {
		if (err)
			this->ncsprint->error("device \""+device+"\" is down!");
		return 0;
	}
	if ((realflags&IFF_LOOPBACK)) {
		if (err)
			this->ncsprint->error("device \""+device+"\" is loopback!");
		return 0;
	}
	if ((realflags&IFF_POINTOPOINT)) {
		if (err)
			this->ncsprint->error("device \""+device+"\" is point to point (PTP)!");
		return 0;
	}
	if ((realflags&IFF_SLAVE)) {
		if (err)
			this->ncsprint->error("device \""+device+"\" is slave!");
		return 0;
	}
	if ((realflags&IFF_NOARP)) {
		if (err)
			this->ncsprint->error("device \""+device+"\" is no arp!");
		return 0;
	}

	realmtu=std::stoi(mtu);
	if (realmtu<576) {
		if (err)
			this->ncsprint->error("device \""+device+"\" has too low mtu!");
		return 0;
	}

	return 1;
}

std::string NESCADEVICE::get_device(void) { return this->device; }
mac_t NESCADEVICE::get_srcmac(void) { return this->srcmac; }
ip4_t NESCADEVICE::get_srcip4(void) { return this->srcip4; }
ip6_t NESCADEVICE::get_srcip6(void) { return this->srcip6; }
bool NESCADEVICE::check_ipv6(void) { return this->ip6; }
ip4_t NESCADEVICE::get_gateway4(void) { return this->gateway4; }
ip6_t NESCADEVICE::get_gateway6(void) { return this->gateway6; }
mac_t NESCADEVICE::get_dstmac(void) { return this->dstmac; }
void NESCADEVICE::set_dstmac(const std::string &mac)
{
	mac_t macc;
	if (mact_pton(mac.c_str(), &macc)<0)
		ncsprint->error("failed set dest mac for ipv6 \""+mac+"\"!\n");
	this->dstmac=macc;
}
void NESCADEVICE::set_gateway4(const std::string &ip4)
{
	ip4_t ip;
	if (ip4t_pton(ip4.c_str(), &ip)<0)
		ncsprint->error("failed set gateway ip4 \""+ip4+"\"!\n");
	this->gateway4=ip;
}

void NESCADEVICE::set_gateway6(const std::string &ip6)
{
	ip6_t ip;
	if (ip6t_pton(ip6.c_str(), &ip)<0)
		ncsprint->error("failed set gateway ip6 \""+ip6+"\"!\n");
	this->gateway6=ip;
}

void NESCADEVICE::set_srcip4(const std::string &ip4)
{
	ip4_t ip;
	if (ip4t_pton(ip4.c_str(), &ip)<0)
		ncsprint->error("failed set ip4 \""+ip4+"\"!\n");
	this->srcip4=ip;
}
void NESCADEVICE::set_srcip6(const std::string &ip6)
{
	ip6_t ip;
	if (ip6t_pton(ip6.c_str(), &ip)<0)
		ncsprint->error("failed set ip6 \""+ip6+"\"!\n");
	this->srcip6=ip;
}

void NESCADEVICE::set_srcmac(const std::string &mac)
{
	mac_t macc;
	if (mact_pton(mac.c_str(), &macc)<0)
		ncsprint->error("failed set source mac \""+mac+"\"!\n");
	this->srcmac=macc;
}

std::vector<std::string> NESCADEVICE::find_devices(void)
{
	std::vector<std::string> res;
	std::string path="/sys/class/net";
	if (std::filesystem::exists(path)&&std::filesystem::is_directory(path))
		for (const auto&entry:std::filesystem::directory_iterator(path))
			res.push_back(entry.path().filename().string());
	else
		this->ncsprint->error("nesca4 couldn't find net interfaces!");
	return res;
}

std::string util_bytesconv(size_t bytes)
{
	const char *sizes[]={
		"B", "KiB", "MiB", "GiB",
		"TiB", "PiB", "EiB"
	};
	double c=0;
	int i=0;

	c=static_cast<double>(bytes);
	while (c>=1024&&i<6) {
		c/=1024;
		i++;
	}

	std::ostringstream result;
	result<<std::fixed<<std::setprecision(2)<<c<<" "<<sizes[i];
	return result.str();
}

std::string util_timediff(const struct timeval& start,
		const struct timeval& end)
{
	const char *prefixes[]={
		"ns", "μs", "ms", "sec",
		"min", "h"
	};
	long long	s, mc, tot;
	double		val;
	int		prfx;

	s=end.tv_sec-start.tv_sec;
	mc=end.tv_usec-start.tv_usec;

	if (mc<0) {
		s--;
		mc+=1000000;
	}

	tot=s*1000000+mc;
	val=tot;
	prfx=0;

	if (val>=3600000000) {
		prfx=5;
		val/=3600000000;
	}
	else if (val>=60000000) {
		prfx=4;
		val/=60000000;
	}
	else if (val>=1000000) {
		prfx=3;
		val/=1000000;
	}
	else if (val>=1000) {
		prfx=2;
		val/=1000;
	}
	else if (val>=1) {
		prfx = 1;
	}
	else {
		prfx=0;
	}

	std::ostringstream result;
	result<<std::fixed<<std::setprecision(2)<<val<<" "<<prefixes[prfx];
	return result.str();
}

std::string util_pps(const struct timeval& start,
		const struct timeval& end, size_t total)
{
	long	pps;
	double	d;

	d=(end.tv_sec-start.tv_sec)+
		(end.tv_usec-start.tv_usec)/1e6;
	if (d<0)
		return "0 pps";
	if (d<1.0)
		pps=total;
	else
		pps=static_cast<long>(total)/d;

	std::ostringstream result;
	result<<pps<<" pps";
	return result.str();
}

bool isokport(NESCAPORT *p)
{
	switch (p->method) {
		case M_UDP_SCAN:
		case M_TCP_WINDOW_SCAN:
		case M_SCTP_INIT_SCAN:
		case M_TCP_SYN_SCAN:
			if (p->state==PORT_OPEN)
				return 1;
			break;
		case M_TCP_ACK_SCAN:
			if (p->state==PORT_NO_FILTER)
				return 1;
			break;
		case M_TCP_FIN_SCAN:
		case M_TCP_XMAS_SCAN:
		case M_TCP_NULL_SCAN:
		case M_TCP_PSH_SCAN:
		case M_SCTP_COOKIE_SCAN:
		case M_TCP_MAIMON_SCAN:
			if (p->state==PORT_CLOSED)
				return 1;
			break;
	}
	return 0;
}
