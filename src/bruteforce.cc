#include "../include/bruteforce.h"

nesca_prints nsp;
brute_ftp_data bfd;

std::string 
base64_encode(const std::string& input){
    constexpr char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string encoded_string;
    size_t input_length = input.length();
    size_t i = 0;

    while (i < input_length) {
        unsigned char char_array_3[3] = {0};
        unsigned char char_array_4[4] = {0};

        for (size_t j = 0; j < 3; j++) {
            if (i < input_length) {
                char_array_3[j] = input[i++];
            }
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (size_t j = 0; j < 4; j++) {
            encoded_string += base64_chars[char_array_4[j]];
        }
    }

    size_t padding = 3 - (input_length % 3);
    for (size_t j = 0; j < padding; j++) {
        encoded_string += '=';
    }

    return encoded_string;
}

std::string 
brute_smtp(const std::string& ip, int port, const std::string& login, const std::string& pass, int brute_log, int verbose){
    if (brute_log) {
        nsp.nlog_custom("SMTP", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
    }

    int sock = create_sock("tcp");
    if (sock == -1) {
        return "";
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &(server_address.sin_addr)) <= 0) {
        return "";
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0) {
        return "";
    }

    char buffer[1024];
    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose) {
        std::cout << buffer;
    }

    std::string helo_command = "HELO localhost\r\n";
    if (send(sock, helo_command.c_str(), helo_command.length(), 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose) {
        std::cout << buffer;
    }

    std::string auth_command = "AUTH LOGIN\r\n";
    if (send(sock, auth_command.c_str(), auth_command.length(), 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose) {
        std::cout << buffer;
    }

    std::string encoded_login = base64_encode(login);
    if (send(sock, encoded_login.c_str(), encoded_login.length(), 0) < 0) {
        close(sock);
        return "";
    }

    if (send(sock, "\r\n", 2, 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose) {
        std::cout << buffer;
    }

    std::string encoded_password = base64_encode(pass);
    if (send(sock, encoded_password.c_str(), encoded_password.length(), 0) < 0) {
        close(sock);
        return "";
    }

    if (send(sock, "\r\n", 2, 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose) {
        std::cout << buffer;
    }

    if (std::string(buffer).find("235") != std::string::npos) {
        close(sock);
        std::string result = login + ":" + pass + "@";
        bfd.set_success_pass(pass);
        bfd.set_success_login(login);
        return result;
    } 
    else {
        close(sock);
        return "";
    }
    return "";
}

std::string 
threads_brute_smtp(const std::string ip, int port, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms){
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, port, login, password, brute_log, verbose, &results]() {
                std::string temp = brute_smtp(ip, port, login, password, brute_log, verbose);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
}

std::string 
brute_ftp(const std::string ip, int port, const std::string login, const std::string pass, int brute_log, int verbose){
    if (brute_log){
            nsp.nlog_custom("FTP", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
    }

    int sock = create_sock("tcp");
    if (sock == -1){
	   return "";
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &(server_address.sin_addr)) <= 0) {
        return "";
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0) {
        return "";
    }

    char buffer[1024];
    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose){
	   std::cout << buffer;
    }

    std::string user_command = "USER " + login + "\r\n";
    if (send(sock, user_command.c_str(), user_command.length(), 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024 - 1, 0) < 0) {
        close(sock);
        return "";
    }
    if (verbose){
	   std::cout << buffer;
    }

    std::string password_command = "PASS " + pass + "\r\n";
    if (send(sock, password_command.c_str(), password_command.length(), 0) < 0) {
        close(sock);
        return "";
    }

    memset(buffer, 0, 1024);
    if (recv(sock, buffer, 1024- 1, 0) < 0) {
        close(sock);
        return "";
    }

    if (verbose){
	   std::cout << buffer;
    }

    if (std::string(buffer).find("230") != std::string::npos) {
        close(sock);
	   std::string result = login + ":" + pass + "@";
	   bfd.set_success_pass(pass);
	   bfd.set_success_login(login);
        return result;
    } 
    else {
        close(sock);
        return "";
    }
    return "";
}

std::string 
threads_brute_ftp(const std::string ip, int port, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms) {
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, port, login, password, brute_log, verbose, &results]() {
                std::string temp = brute_ftp(ip, port, login, password, brute_log, verbose);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
}

std::string 
brute_ssh(const std::string& ip, int port, const std::string login, const std::string pass, int brute_log, int verbose, int known_hosts){
    if (brute_log) {
        nsp.nlog_custom("SSH", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
    }

    ssh_session sshSession = ssh_new();
    if (sshSession == nullptr) {
        return "";
    }

    ssh_options_set(sshSession, SSH_OPTIONS_HOST, ip.c_str());
    ssh_options_set(sshSession, SSH_OPTIONS_PORT, &port);
    ssh_options_set(sshSession, SSH_OPTIONS_USER, login.c_str());

    int connectionStatus = ssh_connect(sshSession);
    if (connectionStatus != SSH_OK) {
	   if (verbose){
		  std::cerr << "Не удалось установить соединение SSH: " << ssh_get_error(sshSession) << std::endl;
	   }
        ssh_free(sshSession);
        return "";
    }

    int authenticationStatus = ssh_userauth_password(sshSession, nullptr, pass.c_str());
    if (authenticationStatus != SSH_AUTH_SUCCESS) {
	   if (verbose){
		  std::cerr << "Не удалось авторизоваться: " << ssh_get_error(sshSession) << std::endl;
	   }
        ssh_disconnect(sshSession);
        ssh_free(sshSession);
        return "";
    }

    if (verbose){
	   std::cout << "Авторизация прошла успешно!" << std::endl;
    }

    ssh_disconnect(sshSession);
    ssh_free(sshSession);

    std::string result = login + ":" + pass + "@";
    return result;
}

std::string 
threads_brute_ssh(const std::string ip, int port, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int known_hosts, int brute_timeout_ms) {
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, port, login, password, brute_log, verbose, known_hosts, &results]() {
                std::string temp = brute_ssh(ip, port, login, password, brute_log, verbose, known_hosts);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
}

std::string 
brute_rtsp(const std::string ip, const std::string login, const std::string pass, int brute_log, int verbose){
    std::string result;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        if (verbose)
        {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
        curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 1L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "LibVLC/2.1.5 (LIVE555 Streaming Media v2014.05.27"); 
        curl_easy_setopt(curl, CURLOPT_RTSP_TRANSPORT, "TCP");
        curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_DESCRIBE);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        std::string url = "rtsp://" + ip;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        if (brute_log){
            nsp.nlog_custom("RTSP", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
        }
        curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, pass.c_str());

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK && http_code == 200){
            result = login + ":" + pass + "@";
            curl_easy_cleanup(curl);
            return result;
        }
        else {
            curl_easy_cleanup(curl);
            return "";
        }
    }
    curl_global_cleanup();
    return "";
}
std::string 
threads_brute_rtsp(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms) {
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, login, password, brute_log, verbose, &results]() {
                std::string temp = brute_rtsp(ip, login, password, brute_log, verbose);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
}

std::string 
brute_http(const std::string ip, const std::string login, const std::string pass, int brute_log, int verbose) {
    CURL *curl;
    CURLcode res;
    long http_code;
    std::string content_type;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ip.c_str());

        if (verbose) {
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        }

        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36");
        curl_easy_setopt(curl, CURLOPT_USERNAME, login.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, pass.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        if (brute_log) {
            nsp.nlog_custom("HTTP", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
        }

        curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            return "";
        }

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code < 200 || http_code >= 300) {
            return "";
        }

        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);
        if (content_type.find("error") != std::string::npos) {
            return "";
        }

        std::string result = login + ":" + pass + "@";
        return result;
    }

    curl_easy_cleanup(curl);
    return "";
}

std::string 
threads_brute_http(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int verbose, int brute_timeout_ms) {
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, login, password, brute_log, verbose, &results]() {
                std::string temp = brute_http(ip, login, password, brute_log, verbose);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
    return "";
}
        
std::string 
brute_ftp_data::get_success_login(void){
    return this->success_login;
}

std::string 
brute_ftp_data::get_success_pass(void){
    return this->success_pass;
}

void 
brute_ftp_data::set_success_login(std::string success_login){
    this->success_login = success_login;
}
void 
brute_ftp_data::set_success_pass(std::string success_pass){
    this->success_pass = success_pass;
}
std::string 
brute_hikvision(const std::string ip, const std::string login, const std::string pass, int brute_log){
  std::string result;

  // log redirection
  freopen("/dev/null", "w", stderr);
  //
  NET_DVR_Init();

  NET_DVR_USER_LOGIN_INFO loginInfo = {0};
  loginInfo.bUseAsynLogin = false;
  strcpy(loginInfo.sDeviceAddress, ip.c_str());
  loginInfo.wPort = 8000;
  strcpy(loginInfo.sUserName, login.c_str());
  strcpy(loginInfo.sPassword, pass.c_str());

  NET_DVR_DEVICEINFO_V40 deviceInfo = {0};

  if (brute_log){
      nsp.nlog_custom("HIKVISION", "                 try: " + login + "@" + pass + " [BRUTEFORCE]\n", 1);
  }

  LONG userId = NET_DVR_Login_V40(&loginInfo, &deviceInfo);

  if (userId < 0) {
    NET_DVR_Cleanup();
    return "";
  }

  result = login + ":" + pass + "@";

  NET_DVR_Logout(userId);
  NET_DVR_Cleanup();

  return result;
}

std::string 
threads_brute_hikvision(const std::string ip, const std::vector<std::string> logins, const std::vector<std::string> passwords, int brute_log, int brute_timeout_ms){
    std::vector<std::thread> threads;
    std::vector<std::string> results;

    for (const auto& login : logins) {
        for (const auto& password : passwords) {
            delay_ms(brute_timeout_ms);
            threads.emplace_back([ip, login, password, brute_log, &results]() {
                std::string temp = brute_hikvision(ip, login, password, brute_log);
                if (!temp.empty() && temp.length() > 3) {
                    results.push_back(temp);
                }
            });
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }

    if (!results.empty()) {
        return results[0];
    } else {
        return "";
    }
    return "";
}
