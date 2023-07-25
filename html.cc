/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/html.h"

int 
html_output::html_main_init(const std::string& filepath){
	const int write = write_line(filepath, style_nesca3);
	if (write != 0) {return -1;}
	return 0;
}

int 
html_output::html_pre_init(const std::string& filepath){
	const std::string data_html = R"(
	<br><br>
	<hr>
      <center>
  		<h5>
    	<font color="#a1a1a1">[)" + std::string(get_time()) + " & " + get_current_date() + R"(]</font>
  		</h5>
      </center>
	<hr>
	<br><br>
	)";

	const int write = write_line(filepath, data_html);
	if (write != 0) {return -1;}
	return 0;
}

int 
html_output::html_add_result(const std::string& filepath, const std::string& time, const std::string& href, const std::string& text,
		const std::string& opt, const std::string& res, const std::string& opt1, const std::string& res1,
		const std::string& opt2, const std::string& res2, const std::string& opt3, const std::string& res3){

	char dots[4] = 
	{':', ':', ':', ':'};

	if (res.empty())  {dots[0] = ' ';}
	if (res1.empty()) {dots[1] = ' ';}
	if (res2.empty()) {dots[2] = ' ';}
	if (res2.empty()) {dots[3] = ' ';}

	const std::string data_html = R"(
	<div id="ipd" style="color:#707070;text-decoration: none;">
	[)" + time + R"(] 
	<span id="hostSpan"><a href=")" + href + R"(" target="_blank">
	<font color=MediumSeaGreen>)" + text + R"(</font></a>;</span>
	<span id="recvSpan">)" + opt3 + dots[0] + R"( <font color=SteelBlue>)" + res3 + R"(</font> </span>
	<span id="recvSpan">)" + opt + dots[1] + R"( <font color=SteelBlue>)" + res + R"(</font> </span>
	<span id="recvSpan">)" + opt1 + dots[2] + R"( <font color=GoldenRod>)" + res1 + R"(</font></span>)" 
	+ opt2 + dots[3] + R"( <font color=GoldenRod>)" + res2 + R"(</font>
	</div>)";

	const int write = write_line(filepath, data_html);
	if (write != 0) {return -1;}
	return 0;
}
