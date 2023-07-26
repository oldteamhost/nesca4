/*
 * NESCA4
 * by oldteam & lomaster
 * license GPL-3.0
 * - Сделано от души 2023.
*/

#include "include/title.h"

size_t write_callback(char* ptr, size_t size, size_t nmemb, std::string* data) 
{
  data->append(ptr, size * nmemb);
  return size * nmemb;
}

std::string
get_http_title(std::string &html_content)
{
    std::string title_tag_open = "<title>";
    std::string title_tag_close = "</title>";

    size_t title_start = html_content.find(title_tag_open);
    if (title_start == std::string::npos){return HTTPTITLE_ERROR;}

    title_start += title_tag_open.length();

    size_t title_end = html_content.find(title_tag_close, title_start);
    if (title_end == std::string::npos){return HTTPTITLE_ERROR;}

    std::string title = html_content.substr(title_start, title_end - title_start);
    return title;
}

std::string
get_http_title_pro(const std::string& node)
{
    CURL* curl = curl_easy_init();
    std::string title = "";
    std::string response_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 1500L);
        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) 
		{
            char* content_type;
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);
            if (res == CURLE_OK && content_type && strstr(content_type, "text/html"))
			{
                size_t start_pos = response_string.find("<title>");
                if (start_pos != std::string::npos)
				{
                    start_pos += 7;
                    size_t end_pos = response_string.find("</title>", start_pos);
                    if (end_pos != std::string::npos)
					{
                        title = response_string.substr(start_pos, end_pos - start_pos);
                    }
                }
            }
        } 
    } 
    curl_easy_cleanup(curl);
    return title;
}
