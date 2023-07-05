/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

/*Этот интерфейс создан для установки характеристики для HTTP портов.
 * Устанавливает характеристику по перенаправлению, или по HTTP заголовкам.*/

#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define CAMERA_AXIS                    "Cam AXIS"
#define WEB_CAMERA_HIKVISION           "Cam HIKVISION"
#define WEB_CAMERA_RVI                 "Cam RVI"
#define HTTP_BASIC_AUTH                "Basic-HTTP-auth"
#define IP_CAMERA_CONTOL               "IP camera-contol"
#define CAMERA_BB_SC384                "Cam BB-SC384"
#define CAMERA_VB_M40                  "Cam VB-M40"
#define PANASONIC_WTFIDONTEVEN_CAMERA  "Cam panasonic-wtfidonteven"
#define CAMERA_SONY                    "Cam sony"
#define CAMERA_UA                      "Cam UA"
#define CAMERA_LG_SMART                "Cam LG-smart"
#define WEB_CAMERA                     "Cam WEB"
#define CAMERA_GEO                     "Cam GEO"
#define CAMERA_PANASONIC               "Cam panasonic"
#define CAMERA_PANASONIC_WJ_HD180      "Cam panasonic-WJ-HD180"
#define CAMERA_FOSCAM                  "Cam foscam"
#define CAMERA_EAGLE_EYE               "Cam eagle-eye"
#define CAMERA_VB_C300                 "Cam vb-c300"
#define CAMERA_AVISYS                  "Cam AVISYS"
#define CAMERA_NW                      "Cam NW"
#define DIGITAL_VIDEO_SERVER           "Digital-video-server"
#define CAMERA_WEBCAMXP5               "Cam webcamxp5"
#define IP_CAMERA_BEWARD               "IP cam beward"
#define WEB_VIDEO_CLIENT               "Web video-client"
#define CAMERA_QCAM                    "Cam QCAM"
#define CAMERA_ACKTI                   "Cam ACKTI"
#define CAMERA_AIROS                   "Cam AIROS"
#define NAX                            "NAX"
#define CAMERA_MASPRO                  "Cam MASPRO"
#define CAMERA_PANASONIC_BB_HG         "Cam panasonic-BB-HG"
#define CAMERA_AXIS_2400               "Cam AXIS-2400|M3004"
#define CAMERA_AXIS_205                "Cam AXIS-205"
#define NETWORK_VIDEO_SYSTEM           "Network-video-system"
#define CAMERA_EASY                    "Cam EASY"
#define CAMERA_NETWORK                 "Cam network"
#define CAMERA_QLIK                    "Cam Qlik-view"
#define CAMERA_IEORFOREFOX             "Cam IEORFOREFOX"
#define NETWORK_VIDEO_CLIENT           "Network-video-client"
#define CAMERA_REE                     "Cam REE"
#define IP_CAMERA_MONITORING           "IP cam-monitoring"
#define CAMERA_VILIAR                  "Cam VILIAR"
#define CPANEL                         "cPanel"
#define ROUTER_OS                      "RouterOS panel"
#define APACHE2                        "Apache2 Default"
#define GOOGLE_404                     "Google 404-code"
#define AUTH                           "Auth no-name"
#define AUTH_LUCI                      "Auth luci"
#define AUTH_SIMIAN                    "Auth simian"
#define CLOUD_FLARE                    "CloudFlare"
#define METEDAS                        "Auth METEDAS"
#define LIFE_IS_GOOD                   "Auth LIFE-IS-GOOD"
#define TP_LINK                        "Auth tp-link"
#define KINGDEE                        "Auth Kingdee"


#define HTTP_BASIC_AUTH_BRUTE  999

/*Нужен для точной установки сервиса порта.
 * Дело в том что, когда после сканирования показывается сервис на порту,
 * это лишь общепринятые данные. И какой нибудь FTP спокойно может быть и на 4333 порту.
 *
 * Именно для этого и нужен этот, класс, что-бы точно убеждатся что там стоит именно тот свервис.*/
class service_probes{
	int http_probe();
	int ftp_probe();
	int smtp_probe();
	int ssh_probe();
};

/*Получение характеристики.*/
class checking_finds{
    public:

	/*Заголовок HTTP*/
	std::vector<std::string> basic_auth_header = {"401 authorization", "401 unauthorized", "www-authenticate",
											"401 unauthorized access denied", "401 unauthorised", "www-authenticate",
											"digest realm", "basic realm", "401 Unauthorized"};

	/*Перенаплавления.*/
    std::vector<std::string> axis_2400_path = {"/view/viewer_index.shtml", "/view/viewer_index.shtml?", "/check_user.cgi",
									"/view/index2.shtml", "/index.shtml","/view/indexFrame.shtml","/indexFrame.html"};

	std::vector<std::string> network_camera_path ={"/ViewerFrame?Mode=", "/CgiStart?page=", "/admin/index.shtml?"};

    std::vector<std::string> axis_other_path = {"/view/viewer_index.shtml", "/view/viewer_index.shtml", "/check_user.cgi",
											"/axis-cgi/mjpg/video.cgi", "/jpg/image.jpg?size=3", "/mjpg/video.mjpg",
                                            "/view/viewer_index.shtml", "/view/viewer_index.shtml", "/check_user.cgi",
											"/cgi-bin/guest/Video.cgi?", "/ISAPI/Security/userCheck", "/SnapshotJPEG",
											"/axis-cgi/com/ptz.cgi?", "/mjpg/video.mjpg"};

	bool /*Поиск слова в строчке.*/
	contains_word(const std::string& word, const std::string& sentence);

	std::string /*Установка характеристики по перенаправлению.*/
	set_target_at_path(const std::string& path);

	std::string /*Установка характеристики по HTTP заголовку.*/
	set_target_at_http_header(const std::string& buffer);

	std::string /*Установка характеристики по HTTP названию*/
	set_target_at_title(const std::string& buffer);

	int /*Узнать метод брутфорса для определённого типа.*/
	than_bruteforce(const std::string type);
};

#endif
