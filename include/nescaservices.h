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

#ifndef NESCASERVICE_H
#define NESCASERVICE_H

#include <future>
#include <vector>
#include <string>
#include <unordered_map>

#include "../libncsnet/ncsnet/sys/types.h"
#include "nescadata.h"

/*
 * CHECK FUNCTIONS:
 *   bool <SERVICE>_chk_<NUM>(...);
 *
 * METHOD FUNCTIONS:
 *   bool <SERVICE>_m_<DATATYPE,...,>(...);
 */
class NESCAPROCESSINGCORPUS
{
	std::vector< std::function<bool(NESCATARGET *, int,
		long long, NESCADATA *)>> checks, methods;
	size_t nummethods=0, numchecks=0;
	bool checksstate=0;

	void _set_general_(std::function<bool(NESCATARGET *, int,
		long long, NESCADATA *)> func, bool check)
	{
		if (!check) {
			this->methods.push_back(func);
			nummethods++;
			return;
		}
		this->checks.push_back(func);
		numchecks++;
	}
	void __exec_check(NESCATARGET *target, int port,
		long long timeout, NESCADATA *ncsdata, size_t num);
	void __exec_method(NESCATARGET *target, int port,
		long long timeout, NESCADATA *ncsdata, size_t num);

public:
	void setmethod(std::function<bool(NESCATARGET *, int,
			long long, NESCADATA *)> method) {
		return _set_general_(method, 0);
	}
	void setcheck(std::function<bool(NESCATARGET *, int,
			long long, NESCADATA *)> method) {
		return _set_general_(method, 1);
	}
	void exec(NESCATARGET *target, int port,
		long long timeout, NESCADATA *ncsdata);
};

class NESCAPROCESSING
{
	std::map<NESCATARGET*, std::vector<int>>	targets;
	std::vector<NESCAPROCESSINGCORPUS>		methods;

	void INIT(NESCADATA *ncsdata, int service);
	void EXECMETHOD(NESCATARGET *target, std::vector<int> ports,
		NESCADATA *ncsdata);
	void NULLVARS(void);
	void EXEC(NESCADATA *ncsdata);

public:
	NESCAPROCESSING(NESCADATA *ncsdata);
};

bool http_chk_0(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata);
bool ftp_chk_0(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata);
bool http_m_htmlredirtitle(NESCATARGET *target, int port,
	long long timeout, NESCADATA *ncsdata);

#endif
