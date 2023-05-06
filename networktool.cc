#include "include/networktool.h"
#include "include/callbacks.h"
#include "include/other.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/deadline_timer.hpp>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
#include <curl/curl.h>
#include <stdexcept>
#include <sstream>
#include <regex>
#include <future>
#include <cstring>
#include <cstddef>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <errno.h>
#endif

std::string get_dns_ip(const char* ip){
    struct addrinfo hints, *result = nullptr;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status;
#ifdef _WIN32
    WSADATA wsaData;
    if ((status = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        return "";
    }
#endif

    if ((status = getaddrinfo(ip, nullptr, &hints, &result)) != 0) {
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    char hostname[NI_MAXHOST] = "";
    if ((status = getnameinfo(result->ai_addr, result->ai_addrlen, hostname, NI_MAXHOST, nullptr, 0, 0)) != 0) {
        freeaddrinfo(result);
#ifdef _WIN32
        WSACleanup();
#endif
        return "";
    }

    freeaddrinfo(result);

#ifdef _WIN32
    WSACleanup();
#endif

    return hostname;
}


long get_response_code(const char *node){
    CURL *curl = curl_easy_init();
    if (!curl) {
        return -1;
    }
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_URL, node);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, clear_callback);
    CURLcode res = curl_easy_perform(curl);

    long response_code = 0;

    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    }

    else {
        return -1;
    }

    curl_easy_cleanup(curl);
    return response_code;
}

double measure_ping_time(const char* node, int port){
    double total_time = 0.0;
    CURL *curl = curl_easy_init();
    if(curl) {
        char node_with_port[256];
        snprintf(node_with_port, 256, "%s:%d", node, port);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_URL, node_with_port);

        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, 500L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
        curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 3000L);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curl_callback);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
        curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 300L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
            if(res != CURLE_OK) {
                curl_easy_cleanup(curl);
                return -2;
            }
        }
        else {
            curl_easy_cleanup(curl);
            return -1;
        }
    }
    curl_easy_cleanup(curl);
    return total_time;
}

std::string get_html_title(std::string node){
    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        return "N/A";
    }

    if (!curl) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_http);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    char* content_type;
    res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);

    if (res != CURLE_OK || content_type == nullptr) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string title_tag_open = "<title>";
    std::string title_tag_close = "</title>";

    size_t title_start = response_string.find(title_tag_open);
    if (title_start == std::string::npos) {
        curl_easy_cleanup(curl);
        return "N/A";
    }
    title_start += title_tag_open.length();

    size_t title_end = response_string.find(title_tag_close, title_start);
    if (title_end == std::string::npos) {
        curl_easy_cleanup(curl);
        return "N/A";
    }

    std::string title = response_string.substr(title_start, title_end - title_start);
    std::string return_value = "\"" + title + "\"";
    curl_easy_cleanup(curl);
    return return_value;
}

std::string parse_content_from_meta(std::string& html) {
    std::string htmll = html;
    boost::algorithm::to_lower(htmll);
    std::string meta_str = "<meta";
    std::string http_equiv_str = "http-equiv=\"refresh\"";
    std::string content_str = "content=\"";
    std::string end_str = "\"";
    std::string url;

    auto meta_it = std::search(htmll.begin(), htmll.end(), meta_str.begin(), meta_str.end(), boost::is_iequal());
    if (meta_it != htmll.end()) {
        auto http_equiv_it = std::search(meta_it, htmll.end(), http_equiv_str.begin(), http_equiv_str.end(), boost::is_iequal());
        if (http_equiv_it != htmll.end()) {
            auto content_it = std::search(http_equiv_it, htmll.end(), content_str.begin(), content_str.end(), boost::is_iequal());
            if (content_it != htmll.end()) {
                auto end_it = std::search(content_it + content_str.size(), htmll.end(), end_str.begin(), end_str.end());
                if (end_it != htmll.end()) {
                    url = std::string(content_it + content_str.size(), end_it);
                    boost::algorithm::trim_all(url);
                    std::vector<std::string> url_prefixes = {"0; url=", "0;url=", "1; url=", "1;url=", "2; url", "2;url=", "0.0; url=", "0.0;url=", "12; url=", "12;url="};
                    for (auto& prefix : url_prefixes) {
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

std::string get_headers(const std::string node){
    std::string header;

    CURL* curl = curl_easy_init();
    if (!curl) {
        return "";
    }

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, node.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &header);

    auto handle = std::async(std::launch::async, curl_easy_perform, curl);
    handle.wait();

    if (handle.valid() && handle.get() != CURLE_OK) {
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_cleanup(curl);

    return header;
}

std::string parse_content_location(std::string header) {
    std::string content_location_str = "Content-Location:";
    std::string end_str = "\r\n";
    std::string result;

    auto content_location_it = std::search(header.begin(), header.end(), content_location_str.begin(), content_location_str.end(), boost::is_iequal());
    if (content_location_it != header.end()) {
        auto end_it = std::search(content_location_it, header.end(), end_str.begin(), end_str.end());
        if (end_it != header.end()) {
            result = std::string(content_location_it + content_location_str.size(), end_it);
            boost::algorithm::trim_all(result);
        }
    }

    return result;
}

std::string parse_location(std::string header) {
    std::string location_str = "Location:";
    std::string end_str = "\r\n";
    std::string result;

    auto location_it = std::search(header.begin(), header.end(), location_str.begin(), location_str.end(), boost::is_iequal());
    if (location_it != header.end()) {
        auto end_it = std::search(location_it, header.end(), end_str.begin(), end_str.end());
        if (end_it != header.end()) {
            result = std::string(location_it + location_str.size(), end_it);
            boost::algorithm::trim_all(result);
        }
    }

    return result;
}

std::string send_http_request(std::string url){
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_request);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_cleanup(curl);
    return response_string;
}

std::string parse_url_from_js(std::string html) {
    std::string search_str = "window.location.href";
    std::string end_str = "\"";
    std::string result;

    auto search_it = std::search(html.begin(), html.end(), search_str.begin(), search_str.end(), boost::is_iequal());
    if (search_it != html.end()) {
        auto end_it = std::search(search_it, html.end(), end_str.begin(), end_str.end());
        if (end_it != html.end()) {
            result = std::string(search_it + search_str.size(), end_it);
            boost::algorithm::trim_all(result);
        }
    }

    return result;
}

std::string get_ftp_response_code(std::string server, std::string port, std::string username, std::string password) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::socket socket(io_context);

    try {
        boost::asio::connect(socket, resolver.resolve(server, port));

        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "USER " << username << "\r\n";
        request_stream << "PASS " << password << "\r\n";
        request_stream << "QUIT\r\n";

        boost::asio::write(socket, request);

        boost::asio::streambuf response;
        boost::asio::deadline_timer timer(io_context, boost::posix_time::seconds(15));
        boost::asio::async_read_until(socket, response, "\r\n", [&response](const boost::system::error_code& error, std::size_t bytes_transferred) {
        });

        io_context.run_one();
        if (timer.expires_at() <= boost::asio::deadline_timer::traits_type::now()) {
            socket.close();
            return "N/A";
        }

        std::istream response_stream(&response);
        std::string status_line;
        std::getline(response_stream, status_line);

        std::string response_description = status_line.substr(status_line.find(' ') + 1);
        response_description.erase(std::remove(response_description.begin(), response_description.end(), '\r'), response_description.end());
        response_description.erase(std::remove(response_description.begin(), response_description.end(), '\n'), response_description.end());

        return response_description;
    }
    catch (const boost::wrapexcept<boost::system::system_error>& ex) {
        return "N/A";
    }
}
