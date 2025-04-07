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

#ifndef NESCAFIND_H
#define NESCAFIND_H

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "nescadata.h"

/* ubi petere? */
#define FIND_ALL		-1
#define FIND_HTTP_REDIRECT	0
#define FIND_HTTP_TITLE		1
#define FIND_HTTP_HTML		2
#define FIND_MAC		3
#define FIND_DNS		4
#define FIND_IP			5
#define FIND_FTP_HELLO		6

class	NESCAOPTS;
class	NESCATARGET;

/*
 * regex:
 *   R'\b173\.194\.(?:[0-9]{1,3})\.(?:[0-9]{1,3})\b', 'GOOOGLE', 0, 5;
 * no-regex:
 *   '173', 'GOOOGLE', 0, 5;
 */

struct NESCAFINDLINE {
	std::string	node,info;
	int		find;
	bool		bruteforce,regex;
};

struct NESCAFINDRESULT {
	std::string info;
	bool bruteforce,ok;
};

class NESCAFIND {
	std::string path;

	NESCAFINDLINE			lineget(const std::string &txt);
	std::vector<NESCAFINDLINE>	fileget(void); /* - */
	NESCAFINDRESULT			fileprobe(NESCATARGET *target, const std::string &node,
						 int find);
	void				init(NESCAOPTS *opts);
public:
	NESCAFIND(NESCADATA *ncsdata);
};

#endif
