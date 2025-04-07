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

#ifndef NESCAPRINT_H
#define NESCAPRINT_H

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <atomic>
#include <chrono>

#include "../libncsnet/ncsnet/sys/types.h"
#include "../libncsnet/ncsnet/utils.h"
#include "../nesca-config.h"

#define DEFAULT_STYLE_PATH \
	"resources/style.css"

class	NESCATARGET;
class	NESCADATA;
struct	NESCAPORT;
class	NESCADEVICE;

class NESCAPRINT {
public:
	void		run(void);
	void		usage(int argc, char **argv);
	void		error(const std::string &err);
	void		warning(const std::string &warn);
	void		note(const std::string &note);
	void		finish(NESCADATA *ncsdata);

	void		nescatarget(NESCATARGET *target, bool onlyok, bool cut);
	void		nescadevice(NESCADEVICE *device);
	void		nescastats(size_t grouplen, __uint128_t total, __uint128_t i);
	void		PRINTTARGETS(NESCADATA *ncsdata);
};

class NESCAHTML {
	size_t		bodyclose_pos=0, headerclose_pos=0, total=0;
	std::string	path;
	bool		open=0;

	std::string	nh_fmtdate(const std::string &fmt);
	void		nh_addtobuf(const std::string &txt);
	void		nh_style(const std::string &filepath);
	void		nh_headeropen(void);
	void		nh_headerclose(void);
	void		nh_bodyopen(NESCADATA *ncsdata);
	void		nh_bodyclose(void);
	void		NH_OPEN(NESCADATA *ncsdata);
	void		NH_ADD(NESCATARGET *target, NESCADATA *ncsdata,
				bool onlyok, bool cut);
	void		NH_CLOSE(void);

public:
	void NHTARGETS(NESCADATA *ncsdata);
	void nh_setpath(const std::string &path);
};

void nescastatus(const std::string &status);
void nescawatting(std::atomic<bool> &running, __uint128_t i,
	NESCADEVICE *ncsdev);
std::string is_service(NESCAPORT *port);
std::string portblock(NESCAPORT *port, bool onlyok);
u8 strmethod(int m);

#endif
