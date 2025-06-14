//
// Created by Tom Handrick on 14.06.25.
//

#include <iostream>
#include <string>

using namespace std;

string request_input(const string& message) {
    string input;
    cout << message;
    getline(cin, input);
    cout << endl;
    return input;
}
