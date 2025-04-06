#include "download.h"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

// Callback zum Schreiben der Daten in die Datei
size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    auto* out = static_cast<std::ofstream*>(stream);
    const size_t totalSize = size * nmemb;
    out->write(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

bool download(const std::string& url, const std::string& path) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[curl] Initialisierung fehlgeschlagen\n";
        return false;
    }

    std::ofstream outFile(path, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "[download] Konnte Datei nicht öffnen: " << path << "\n";
        curl_easy_cleanup(curl);
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Redirects folgen

    const CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    outFile.close();

    if (res != CURLE_OK) {
        std::cerr << "[curl] Fehler beim Download: " << curl_easy_strerror(res) << "\n";
        return false;
    }

    std::cout << "[download] Erfolgreich gespeichert als: " << path << "\n";
    return true;
}
