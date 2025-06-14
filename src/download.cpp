#include "download.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(dir) _mkdir(dir)
#else
    #include <errno.h>
    #define MKDIR(dir) mkdir(dir, 0755)
#endif

// Helper: Create directory if it does not exist
bool ensure_directory(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos == std::string::npos) return true; // No directory part

    std::string dir = filepath.substr(0, pos);
    struct stat info;
    if (stat(dir.c_str(), &info) != 0) {
        // Directory does not exist, try to create it
        if (MKDIR(dir.c_str()) != 0) {
            std::cerr << "[download] Failed to create directory: " << dir << std::endl;
            return false;
        }
    } else if (!(info.st_mode & S_IFDIR)) {
        std::cerr << "[download] Path exists but is not a directory: " << dir << std::endl;
        return false;
    }
    return true;
}

// Callback for libcurl to write data to file
size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    std::ofstream* out = static_cast<std::ofstream*>(stream);
    const size_t totalSize = size * nmemb;
    out->write(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

Download::Download(const std::string &url, const std::string &path)
    : url(url), path(path) {}

bool Download::download() const {
    if (!ensure_directory(path)) {
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[curl] Initialization failed" << std::endl;
        return false;
    }

    std::ofstream outFile(path, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "[download] Could not open file: " << path << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    outFile.close();

    if (res != CURLE_OK) {
        std::cerr << "[curl] Download error: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    std::cout << "[download] Successfully saved as: " << path << std::endl;
    return true;
}
