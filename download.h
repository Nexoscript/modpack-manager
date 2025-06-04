#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <string>

class Download {
    std::string url;
    std::string path;
public:
    Download(const std::string &url, const std::string &path);
    bool download() const;
};

#endif
