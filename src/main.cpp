#include <iostream>
#include "download.h"

int main() {
    const Download downloader(
        "https://eztxm.de/assets/images/logo.png",
        "/Users/eztxmmc/Downloads/logo.png"
    );
    if (downloader.download()) {
        std::cout << "Logo loaded successfully!" << std::endl;
        return 0;
    }
    std::cerr << "Error loading logo" << std::endl;
    return 1;
}
