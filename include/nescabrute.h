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

#ifndef NESCABRUTE_H
#define NESCABRUTE_H

#include <chrono>
#include <cstdio>
#include <mutex>

#include "nescadata.h"
#include "nescaengine.h"

#include "../libncsnet/ncsnet/mt19937.h"
#include "../libncsnet/ncsnet/socket.h"
#include "../libncsnet/ncsnet/random.h"
#include "../libncsnet/ncsnet/ftp.h"
#include "../libncsnet/ncsnet/http.h"

#define START_TIMEOUT		1e+9
#define HTTP_BRUTEFORCE		S_HTTP
#define FTP_BRUTEFORCE		S_FTP
/*
#define SMTP_BRUTEFORCE      2
#define RVI_BRUTEFORCE       3
#define HIKVISION_BRUTEFORCE 5
*/

class NESCABRUTE {
	std::string reslogin, respass;
	long long restimeout, rtt;
	std::vector<int> fds;
	bool ok;

	bool init(size_t threads, const std::string &ip, u16 port,
		u8 service, long long timeout, std::vector<std::string> login,
		std::vector<std::string> pass);
	void newfd(const std::string &ip, u16 port, u8 service,
		long long timeout);

	void probe(int fd, u8 service, const std::string &ip,
		const std::string &path, const std::string &login,
		const std::string &pass, std::atomic<bool> *auth);
public:
	std::string GETRESULTINNESCASTYLE(void);

	NESCABRUTE(size_t threads, const std::string &ip, const std::string &path,
		u16 port, long long timeout, u8 service, long long delay,
		std::vector<std::string> login, std::vector<std::string> pass);
	~NESCABRUTE(void);

	std::string LOGIN(void);
	std::string PASS(void);
};

void NESCABRUTEFORCE(NESCADATA *ncsdata);


#endif
