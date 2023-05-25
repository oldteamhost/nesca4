#include "include/title.h"

std::string
get_http_title(std::string &html_content){
    std::string title_tag_open = "<title>";
    std::string title_tag_close = "</title>";

    size_t title_start = html_content.find(title_tag_open);
    if (title_start == std::string::npos) {
        return HTTPTITLE_ERROR;
    }

    title_start += title_tag_open.length();

    size_t title_end = html_content.find(title_tag_close, title_start);
    if (title_end == std::string::npos) {
        return HTTPTITLE_ERROR;
    }

    std::string title = html_content.substr(title_start, title_end - title_start);
    return title;
}
