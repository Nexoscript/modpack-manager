#include <iostream>
#include "download.h"
#include "file_editor.h"
#include "console.h"
#include <vector>

using namespace std;

int main() {
    vector<string> enviroments = {"client", "server"};
    cout << "Welcome to the Minecraft Modpack Downloader!" << endl;
    cout << "------------------------------------------" << endl;
    cout << "This program will download a Minecraft modpack from a given URL." << endl;
    cout << "------------------------------------------" << endl;
    const filesystem::path path = request_input("Enter path to download to: ");
    const string zipName = request_input("Enter zip name: ") + ".zip";
    const string url = request_input("Enter URL to download from: ");
    string enviroment;
    while (find(enviroments.begin(), enviroments.end(), enviroment) == enviroments.end()) {
        enviroment = request_input("Enter environment to download for: ");
        if (find(enviroments.begin(), enviroments.end(), enviroment) == enviroments.end()) {
            cerr << "Invalid environment, please enter either 'client' or 'server'" << endl;
            cout << "------------------------------------------" << endl;
            cout << "Press enter to reenter environment...";
            cin.get();
            cin.ignore();
            cout << "------------------------------------------" << endl;
        }
    }
    if (find(enviroments.begin(), enviroments.end(), enviroment) == enviroments.end()) {
        cerr << "Invalid environment, please enter either 'client' or 'server'" << endl;
        return 1;
    }
    cout << endl;
    filesystem::path zipPath = path / zipName;
    if (const Download downloader(url, zipPath); !downloader.download()) {
        cerr << "Error downloading " << url << endl;
        return 1;
    }
    cout << url << " loaded successfully!" << endl;
    const FileEditor editor(path);
    editor.removeDirectory("config");
    editor.removeDirectory("defaultconfigs");
    editor.removeDirectory("kubejs");
    editor.removeDirectory("logs");
    editor.removeDirectory("mods");
    if (enviroment == "client") {
        editor.removeDirectory("resourcepacks");
        editor.removeDirectory("shaderpacks");
    }

    return 0;
}
