//
// Created by Tom Handrick on 14.06.25.
//

#ifndef FILE_EDITOR_H
#define FILE_EDITOR_H

#include <filesystem>

using namespace std;

class FileEditor {
    filesystem::path path;

public:
    explicit FileEditor(filesystem::path path);

    void removeDirectory(const filesystem::path& name) const;

    void removeFile(const filesystem::path& name) const;

    void unzip(const filesystem::path& zip) const;
};


#endif //FILE_EDITOR_H
