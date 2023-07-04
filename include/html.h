/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#ifndef HTML_H
#define HTML_H
#include <iostream>

class html_output{
private:
	std::string style_nesca3 = R"(
	<style>
  	#recvSpan {
    	display: inline-block;
    	width: 150px;
  	}
  	#hostSpan {
    	display: inline-block;
    	width: 200px;
  	}
  	body {
    	background-color: #141414;
    	font-family: monospace;
    	font-size: 95%;
  	}
  	#ipd {
    	background: black;
    	width: 100%;
    	white-space: nowrap;
    	overflow-x: none;
    	display: inline-block;
  	}
  	#ipd:hover {
    	color: #909090;
    	background: #202020;
  	}
  	#tit {
    	text-align: center;
    	border: 1px solid #5d5d5d;
  	}
  	a {
    	color: gray;
    	text-decoration: underline;
  	}
  	a:focus {
    	outline-style: dashed;
    	outline-width: 1px;
    	outline-color: red;
  	}
	</style>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>output</title>

	<div id="tit">
	<a href="http://oldteamhost.ru">.oldteam</a>
	</div>
	)";
public:
	int 
	html_main_init(const std::string& filepath);

	int 
	html_pre_init(const std::string& filepath);

	int 
	html_add_result(const std::string& filepath, std::string time, std::string href, std::string text,
			std::string opt, std::string res, std::string opt1, std::string res1,
			std::string opt2, std::string res2);
};

#endif
