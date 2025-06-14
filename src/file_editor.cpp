//
// Created by Tom Handrick on 14.06.25.
//

#include "file_editor.h"

#include <utility>

using namespace std;

FileEditor::FileEditor(filesystem::path path) {
    FileEditor::path = move(path);
}

void FileEditor::removeDirectory(const filesystem::path &name) const {
    filesystem::remove_all(path / name);
}

void FileEditor::removeFile(const filesystem::path &name) const {
    filesystem::remove(path / name);
}

void FileEditor::unzip(const filesystem::path &zip) const {

}

