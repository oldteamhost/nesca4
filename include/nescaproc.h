/*
 *          NESCA4
 *   Сделано от души 2023.
 * Copyright (c) [2023] [lomaster]
 * SPDX-License-Identifier: BSD-3-Clause
 *
*/

#ifndef NESCAPROC_H
#define NESCAPROC_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "nescalog.h"
#include "nescadata.h"
#include "nescautils.h"
#include "../config/nescaopts.h"

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
#define CAMERA_AXIS_Q6055_E            "AXIS-Q6055-E"
#define CAPTCHA                        "Captcha"
#define ERROR_403                      "403 error"
#define UNKNOWN_ERROR                  "Unknown error"
#define NOT_FOUND_404                  "404 not found"
#define EMPTY_REQUEST                  "Empty request"

#define HTTP_BASIC_AUTH_BRUTE  999

/*Получение характеристики.*/
  /*Заголовок HTTP*/
std::vector<std::string>
find_sentences_with_word(const std::string& word, const std::string& input_text);

bool contains_word(const std::string& word, const std::string& sentence);
std::string set_target_at_path(const std::string& path);
std::string set_target_at_http_header(const std::string& buffer);
std::string set_target_at_title(const std::string& buffer);
int than_bruteforce(const std::string type);
void print_port_state(int status, int port, std::string service, nesca_prints& np);

/*Для обработки портов класс на паттерне Strategy Pattern.*/
class ports_strategy {
public:
  virtual ~ports_strategy() {}
  virtual void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
  const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) = 0;

  std::string brute_temp, http_title, type_target, content_base64,
    screenshot_base64_cam, screenshot_base64, result_print;
};

class ftp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class hikvision_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class rvi_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class https_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class rtsp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class smtp_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class http_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

class else_strategy : public ports_strategy {
public:
  void handle(const std::string& ip, const std::string& result, const std::string& rtt_log,
    const std::string& protocol, int port, arguments_program& argp, nesca_prints& np, NESCADATA& nd, services_nesca& sn) override;};

#endif
