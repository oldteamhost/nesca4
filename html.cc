#include "include/html.h"
#include "include/other.h"
#include "include/files.h"

int 
html_output::html_main_init(const std::string& filepath){
	int write = write_line(filepath, style_nesca3);
	if (write != 0){return -1;}
	return 0;
}

int 
html_output::html_pre_init(const std::string& filepath){
	std::string data_html = R"(
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
	int write = write_line(filepath, data_html);
	if (write != 0){return -1;}
	return 0;
}

int 
html_output::html_add_result(const std::string& filepath, std::string time, std::string href, std::string text,
		std::string opt, std::string res, std::string opt1, std::string res1,
		std::string opt2, std::string res2){

	char dots[3] = {':', ':', ':'};
	if (res.empty()){dots[0] = ' ';}
	if (res1.empty()){dots[1] = ' ';}
	if (res2.empty()){dots[2] = ' ';}

	std::string data_html = R"(
	<div id="ipd" style="color:#707070;text-decoration: none;">
	[)" + time + R"(] 
	<span id="hostSpan"><a href=")" + href + R"(" target="_blank">
	<font color=MediumSeaGreen>)" + text + R"(</font></a>;</span>
	<span id="recvSpan">)" + opt + dots[0] + R"( <font color=SteelBlue>)" + res + R"(</font> </span>
	<span id="recvSpan">)" + opt1 + dots[1] + R"( <font color=GoldenRod>)" + res1 + R"(</font></span>)" 
	+ opt2 + dots[2] + R"( <font color=GoldenRod>)" + res2 + R"(</font>
	</div>)";

	int write = write_line(filepath, data_html);
	if (write != 0){return -1;}
	return 0;
}
