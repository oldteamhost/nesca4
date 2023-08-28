/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/hikvision.h"

bool hikvision_screenshot(const std::string& ip, const long user_id, const NET_DVR_DEVICEINFO_V40 device, const std::string& path)
{
  for (int channel = 0; channel < device.struDeviceV30.byChanNum; channel++) {
    std::string filename = path + ip + "_" + std::to_string(channel) + ".jpg";
    char screenshotFilenameBuffer[256];
    strcpy(screenshotFilenameBuffer, filename.c_str());

    NET_DVR_JPEGPARA params = {0};
    params.wPicQuality = 2;
    params.wPicSize = 0;

    if (NET_DVR_CaptureJPEGPicture(user_id, channel, &params, screenshotFilenameBuffer)) {
      return true;
    }
  }

  return false;
}
