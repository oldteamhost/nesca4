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
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "../ncsock/include/ncread.h"

#define CAMERA_AXIS                    "AXIS CAMERA"
#define WEB_CAMERA_HIKVISION           "HIKVISION CAMERA"
#define WEB_CAMERA_RVI                 "RVI CAMERA"
#define HTTP_BASIC_AUTH                "Basic-HTTP-auth"
#define IP_CAMERA_CONTOL               "IP camera-contol"
#define CAMERA_BB_SC384                "BB-SC384 CAMERA"
#define CAMERA_VB_M40                  "VB-M40 CAMERA"
#define PANASONIC_WTFIDONTEVEN_CAMERA  "Panasonic-wtfidonteven CAMERA"
#define CAMERA_SONY                    "Sony CAMERA"
#define CAMERA_UA                      "UA CAMERA"
#define CAMERA_LG_SMART                "LG-smart CAMERA"
#define WEB_CAMERA                     "WEB CAMERA"
#define CAMERA_GEO                     "GEO CAMERA"
#define CAMERA_PANASONIC               "Panasonic CAMERA"
#define CAMERA_PANASONIC_WJ_HD180      "Panasonic-WJ-HD180 CAMERA"
#define CAMERA_FOSCAM                  "Foscam CAMERA"
#define CAMERA_EAGLE_EYE               "Eagle-eye CAMERA"
#define CAMERA_VB_C300                 "Vb-c300 CAMERA"
#define CAMERA_AVISYS                  "AVISYS CAMERA"
#define CAMERA_NW                      "NW CAMERA"
#define DIGITAL_VIDEO_SERVER           "Digital-video-server"
#define CAMERA_WEBCAMXP5               "Webcamxp5 CAMERA"
#define IP_CAMERA_BEWARD               "Beward IP CAMERA"
#define WEB_VIDEO_CLIENT               "Web video-client"
#define CAMERA_QCAM                    "QCAM CAMERA"
#define CAMERA_ACKTI                   "ACKTI CAMERA"
#define CAMERA_AIROS                   "AIROS CAMERA"
#define NAX                            "NAX"
#define CAMERA_MASPRO                  "MASPRO CAMERA"
#define CAMERA_PANASONIC_BB_HG         "Panasonic-BB-HG CAMERA"
#define CAMERA_AXIS_2400               "AXIS-2400|M3004|Q1755 CAMERA"
#define CAMERA_AXIS_205                "AXIS-205 CAMERA"
#define NETWORK_VIDEO_SYSTEM           "Network-video-system"
#define CAMERA_EASY                    "EASY CAMERA"
#define CAMERA_NETWORK                 "Network CAMERA"
#define CAMERA_QLIK                    "Qlik-view CAMERA"
#define CAMERA_IEORFOREFOX             "IEORFOREFOX CAMERA"
#define NETWORK_VIDEO_CLIENT           "Network-video-client"
#define CAMERA_REE                     "REE CAMERA"
#define IP_CAMERA_MONITORING           "IP cam-monitoring"
#define CAMERA_VILIAR                  "VILIAR CAMERA"
#define CPANEL                         "cPanel"
#define ROUTER_OS                      "RouterOS panel"
#define APACHE2                        "Apache2 Default"
#define GOOGLE_404                     "Google 404-code"
#define AUTH                           "Auth No-name"
#define AUTH_LUCI                      "Auth Luci"
#define AUTH_SIMIAN                    "Auth Simian"
#define CLOUD_FLARE                    "CloudFlare"
#define METEDAS                        "Auth METEDAS"
#define LIFE_IS_GOOD                   "Auth LIFE-IS-GOOD"
#define TP_LINK                        "Auth Tp-link"
#define KINGDEE                        "Auth Kingdee"
#define HTTP_DIGEST_AUTH               "DIGEST-HTTP-AUTH"
#define NGNIX                          "Ngnix"
#define INVALID_URL                    "Invalid URL"
#define RANDOM                         "Where it leads?"

#define HTTP_BASIC_AUTH_BRUTE  999

/*Нужен для точной установки сервиса порта.
 * Дело в том что, когда после сканирования показывается сервис на порту,
 * это лишь общепринятые данные. И какой нибудь FTP спокойно может быть и на 4333 порту.
 *
 * Именно для этого и нужен этот, класс, что-бы точно убеждатся что там стоит именно тот свервис.*/
class service_probes{
	int
	http_probe(const std::string& ip, const int port);
	int
	ftp_probe(const std::string& ip, const int port);
	int
	smtp_probe(const std::string& ip, const int port);
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
