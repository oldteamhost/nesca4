#include "../include/redirect.h"

std::string 
parse_http_equiv(std::string& html) {
    std::string htmll = html;
    std::transform(htmll.begin(), htmll.end(), htmll.begin(), ::tolower);
    std::string meta_str = "<meta";
    std::string http_equiv_str = "http-equiv=\"refresh\"";
    std::string content_str = "content=\"";
    std::string end_str = "\"";
    std::string url;

    auto meta_it = std::search(htmll.begin(), htmll.end(), meta_str.begin(), meta_str.end(),
        [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
    if (meta_it != htmll.end()) {
        auto http_equiv_it = std::search(meta_it, htmll.end(), http_equiv_str.begin(), http_equiv_str.end(),
            [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
        if (http_equiv_it != htmll.end()) {
            auto content_it = std::search(http_equiv_it, htmll.end(), content_str.begin(), content_str.end(),
                [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
            if (content_it != htmll.end()) {
                auto end_it = std::search(content_it + content_str.size(), htmll.end(), end_str.begin(), end_str.end(),
                    [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
                if (end_it != htmll.end()) {
                    url = std::string(content_it + content_str.size(), end_it);
                    url.erase(std::remove(url.begin(), url.end(), ' '), url.end());
                    std::vector<std::string> url_prefixes = {"0;url=", "1;url=", "2;url=", "0.0;url=", "12;url="};
                    for (const std::string& prefix : url_prefixes) {
                        if (url.compare(0, prefix.length(), prefix) == 0) {
                            url.erase(0, prefix.length());
                        }
                    }
                }
            }
        }
    }

    return url;
}

std::string 
parse_url_from_js(std::string& html) {
    std::string search_str = "window.location.href";
    std::string end_str = "\"";
    std::string result;

    auto search_it = std::search(html.begin(), html.end(), search_str.begin(), search_str.end(),
        [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
    if (search_it != html.end()) {
        auto end_it = std::search(search_it, html.end(), end_str.begin(), end_str.end(),
            [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
        if (end_it != html.end()) {
            result = std::string(search_it + search_str.size(), end_it);
            result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
        }
    }

    return result;
}

std::string 
parse_location(std::string& header) {
    std::string location_str = "Location:";
    std::string end_str = "\r\n";
    std::string result;

    auto location_it = std::search(header.begin(), header.end(), location_str.begin(), location_str.end(),
        [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
    if (location_it != header.end()) {
        auto end_it = std::search(location_it, header.end(), end_str.begin(), end_str.end(),
            [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
        if (end_it != header.end()) {
            result = std::string(location_it + location_str.size(), end_it);
            result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
        }
    }

    return result;
}

std::string 
process_redirect(const std::string& path, const std::string& ip, int port){
    std::string paste_;
    std::string redirect;
    size_t finding0 = path.find("http://");
    size_t finding1 = path.find("https://");
    size_t finding2 = path.find(":" + std::to_string(port));

    if (finding1 != std::string::npos || finding0 != std::string::npos) {
         if (finding2 == std::string::npos) {
             redirect = path;
         }
    }
    else {
        if (path[0] != '/') {
            paste_ = "http://" + ip + ":" + std::to_string(port) + "/" + path;
        }
        else {
            paste_ = "http://" + ip + ":" + std::to_string(port) + path;
        }

        redirect.insert(0, paste_);
        redirect = paste_;
    }

    return redirect;
}
std::string 
parse_content_location(std::string& header) {
    std::string content_location_str = "Content-Location:";
    std::string end_str = "\r\n";
    std::string result;

    auto content_location_it = std::search(header.begin(), header.end(), content_location_str.begin(), content_location_str.end(),
        [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
    if (content_location_it != header.end()) {
        auto end_it = std::search(content_location_it, header.end(), end_str.begin(), end_str.end(),
            [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
        if (end_it != header.end()) {
            result = std::string(content_location_it + content_location_str.size(), end_it);
            result.erase(std::remove(result.begin(), result.end(), ' '), result.end());
        }
    }

    return result;
}
std::string
parse_redirect(std::string& html, std::string &header, const std::string& ip, bool fix, int port){
    std::string redirect;
    std::string path_location = parse_location(header);

    if (path_location.length() > 1){
        if (fix){
            redirect = path_location;
        }
        else {
            redirect = process_redirect(path_location, ip, port);
        }
    }
    else {
        std::string path_http = parse_http_equiv(html);

        if (path_http.length() > 1){
            if (fix){
                redirect = path_http;
            }
            else {
                redirect = process_redirect(path_http, ip, port);
            }
        } 
        else {
            std::string path_js = parse_url_from_js(html);
            if (path_js.length() > 3){
                if (fix){
                    redirect = path_js;
                }
                else {
                    redirect = process_redirect(path_js, ip, port);
                }
            }
            else {
                std::string path_content_location = parse_content_location(header);
                if (path_content_location.length() > 1){
                    if (fix){
                        redirect = path_content_location;
                    }
                    else {
                        redirect = process_redirect(path_content_location, ip, port);
                    }
                }
            }
        }
    }

    return redirect;
}
