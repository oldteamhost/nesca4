/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/scanner.h"

bool 
checking_finds::contains_word(const std::string& word, const std::string& sentence)
{
	std::string lowerWord = word;
    std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), [](unsigned char c){ return std::tolower(c); });

    std::string lowerSentence = sentence;
    std::transform(lowerSentence.begin(), lowerSentence.end(), lowerSentence.begin(), [](unsigned char c){ return std::tolower(c); });

    std::string::size_type pos = lowerSentence.find(lowerWord);
    while (pos != std::string::npos)
	{
        if (std::isalpha(lowerSentence[pos - 1]) || std::isalpha(lowerSentence[pos + lowerWord.length()])) 
		{
          pos = lowerSentence.find(lowerWord, pos + 1);
        } else{return true;}
    }

    return false;
}

std::string
checking_finds::set_target_at_path(const std::string& path)
{
	/*AXIS камеры.*/
	if (contains_word("/operator/basic.shtml", path)){return CAMERA_AXIS_205;}
	for (auto& p : axis_2400_path){if(contains_word(p, path)){return CAMERA_AXIS_2400;}}
	for (auto& p : axis_other_path){if(contains_word(p, path)){return CAMERA_AXIS;}}

	/*NETWORK камеры.*/
	for (auto& p : network_camera_path){if(contains_word(p, path)){return CAMERA_NETWORK;}}
	if (contains_word("/viewer/live/index.html", path)){return CAMERA_VB_M40;}
	if (contains_word("/live/index2.html", path)){return CAMERA_BB_SC384;}

	/*Другие камеры.*/
	if (contains_word("/tool.js", path)){return CAMERA_EASY;}
	if (contains_word("/command/inquiry.cgi?", path)){return CAMERA_SONY;}
	if (contains_word("/config/easy_index.cgi", path)){return CAMERA_PANASONIC;}
	if (contains_word("/view/getuid.cgi", path)){return CAMERA_PANASONIC_WJ_HD180;}
	if (contains_word("/main/cs_motion.asp", path)){return IP_CAMERA_CONTOL;}
	if (contains_word("/cgi-bin/data/viostor-220/viostor/viostor.cgi", path)){return NAX;}
	if (contains_word("gui.css", path)){return DIGITAL_VIDEO_SERVER;}
	if (contains_word("/config/index.cgi", path)){return CAMERA_PANASONIC_BB_HG;} /*???*/
	if (contains_word("/login.asp", path)){return HTTP_DIGEST_AUTH;}
	if (contains_word("/videostream.cgi", path)){return CAMERA_QCAM;}
	if (contains_word("/gui/gui_outer_frame.shtml", path)){return CAMERA_NW;}
	if (contains_word("/admin/index.html", path)){return AUTH;}
	if (contains_word("liveview.html", path)){return CAMERA_AVISYS;}
	if (contains_word("js/upfile.js", path)){return CAMERA_FOSCAM;}
	if (contains_word("ssi.cgi/login.htm", path)){return CAMERA_GEO;}
	if (contains_word("src=\\\"webs.cgi?", path)){return CAMERA_UA;}
	if (contains_word("/app/multi/single.asp", path)){return NETWORK_VIDEO_SYSTEM;}
	if (contains_word("/app/live/sim/single.asp", path)){return NETWORK_VIDEO_SYSTEM;}
	if (contains_word("/doc/page/login.asp?_", path)){return WEB_CAMERA_HIKVISION;}
	if (contains_word("/login", path)){return AUTH;}

	/*Другое*/
	if (contains_word("/cgi-sys/defaultwebpage.cgi", path)){return CPANEL;}
	if (contains_word("/login.html", path)){return AUTH;}
	if (contains_word("/cgi-bin/luci", path)){return AUTH_LUCI;}
	if (contains_word("cgi-bin/luci", path)){return AUTH_LUCI;}
	if (contains_word("/admin_login", path)){return AUTH_SIMIAN;}
	if (contains_word("/ecoremote/index.html", path)){return METEDAS;}
	if (contains_word("?password-protected=login", path)){return LIFE_IS_GOOD;}
	if (contains_word("/webpages/index.html", path)){return TP_LINK;}
	if (contains_word("/k3cloud/html5", path)){return KINGDEE;}

	return "fuck";
}

std::string
checking_finds::set_target_at_http_header(const std::string& buffer)
{
	/*Разное.*/
	for (auto& p : basic_auth_header){if(contains_word(p, buffer)){return HTTP_BASIC_AUTH;}}

	/*Другие камеры.*/
	if (contains_word("airos_logo", buffer)){return CAMERA_AIROS;}
	if (contains_word("acti Corporation", buffer)){return CAMERA_ACKTI;}
	if (contains_word("qlikview", buffer)){return CAMERA_QLIK;}
	if (contains_word("webcamxp", buffer)){return CAMERA_WEBCAMXP5;}
	if (contains_word("a valid username/password", buffer)){return CAMERA_WEBCAMXP5;}
	if (contains_word("ieorforefox", buffer)){return CAMERA_IEORFOREFOX;}
	if (contains_word("dvr_remember", buffer)){return NETWORK_VIDEO_CLIENT;}
	if (contains_word("login_chk_usr_pwd", buffer)){return NETWORK_VIDEO_CLIENT;}
	if (contains_word("reecam ip camera", buffer)){return CAMERA_REE;}
	if (contains_word("real-time ip camera monitoring system", buffer)){return IP_CAMERA_MONITORING;}
	if (contains_word("server push mode", buffer)){return IP_CAMERA_MONITORING;}
	if (contains_word("invalid url", buffer)){return INVALID_URL;}
	if (contains_word("vilar ipcamera", buffer)){return CAMERA_VILIAR;}
	if (contains_word("welcome to nginx!", buffer)){return NGNIX;}
	if (contains_word("routeros", buffer)){return ROUTER_OS;}
	if (contains_word("apache2", buffer)){return APACHE2;}
	if (contains_word("cloudflare", buffer)){return CLOUD_FLARE;}
	if (contains_word("www.rvi-cctv.ru", buffer)){return WEB_CAMERA_RVI;}

	return "fuck";
}
std::string
checking_finds::set_target_at_title(const std::string& title)
{
	if (contains_word("error 404 (not found)!!1", title)){return GOOGLE_404;}
	if (contains_word("ngnix", title)){return NGNIX;}
	if (contains_word("302 found", title)){return RANDOM;}
	if (contains_word("axis", title)){return CAMERA_AXIS_Q6055_E;}
	if (contains_word("301 moved permanently", title)){return RANDOM;}

	return "fuck";
}

int
checking_finds::than_bruteforce(const std::string type)
{
	if (type == CAMERA_AXIS || type == CAMERA_AXIS_205 ||
		type == CAMERA_AXIS_2400 || type == HTTP_BASIC_AUTH ||
		type == CAMERA_BB_SC384 || type == CAMERA_VB_M40 ||
		type == CAMERA_PANASONIC || type == CAMERA_UA ||
		type == CAMERA_SONY || type == CAMERA_LG_SMART ||
		type == CAMERA_EAGLE_EYE || type == CAMERA_QLIK
		|| type == CAMERA_AXIS_Q6055_E){
		return HTTP_BASIC_AUTH_BRUTE;
	} 
	return -1;
}
