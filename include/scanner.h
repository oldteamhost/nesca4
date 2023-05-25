#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <vector>

#define PORT_OPEN 0
#define PORT_ERROR -1
#define PORT_CLOSED 1
#define PORT_FILTERED 2

// dns scan
int 
dns_scan(std::string domain, std::string domain_1level);

class checking_finds{
    public:

    std::vector<std::string> axis_path = {"/view/viewer_index.shtml", "/view/viewer_index.shtml", 
                                         "/mjpg/video.mjpg", "/axis-cgi/com/ptz.cgi?",
                                         "/view/viewer_index.shtml?", "check_user.cgi", "/axis-cgi/com/ptz.cgi?query=position", "CgiStart?page=",
                                         "view/indexFrame.shtml"};

    std::vector<std::string> basic_auth_paths = {"/view/getuid.cgi", "/cgi-bin/guest/Video.cgi?", "/admin/index.shtml?", 
                                    "/cgi-bin/getuid?FILE=indexnw.html", "/gui/rem_display.shtml", "/ISAPI/Security/userCheck",
                                    "/config/index.cgi", "/QvAJAXZfc/Authenticate.aspx?_=1453661324640", "/videostream.cgi",
                                    "/Login.cgi?rnd=000148921789481", "/user/index.htm", "/main/cs_motion.asp", "/live/index2.html",
                                    "/-wvhttp-01-/open.cgi?", "/SnapshotJPEG", "/oneshotimage?", "/webs.cgi?", "/-wvhttp-01-/open.cgi?",
                                    "/digest.php", "/cgi-bin/data/viostor-220/viostor/viostor.cgi", "/check_user.cgi", "/view/getuid.cgi",
                                    "/cgi-bin/guest/Video.cgi?", "/admin/index.shtml?", ":webs", "/login.asp", "index.asp", "index.shtml"};

    std::string check_axis_camera(std::string ip);
    std::string check_basic_auth(std::string ip);
};

#endif
