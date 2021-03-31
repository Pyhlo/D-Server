#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
//#include <bits/stdc++.h> //apparently this is needed for vectors
//#define WINVER 0x0500
#include <windows.h>
//#include <unistd.h> //this should work even if the linter says there's an error
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp> //ADD CPLUS_INCLUDE_PATH AND LIBRARY_PATH TO SYSTEM VARIABLES

using std::string;
std::string SERVERNAME = "z"; //change this to d

bool doesExist(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void clearFile(const std::string path) {
    std::ofstream file;
    file.open(path, std::ofstream::out | std::ofstream::trunc);
    file.close();
}
void start_countdown(int seconds) {
    for (int i = seconds; i > 0; i--) {
        if (i == 1) {
            std::cout << "Starting in " << i << " second!" << std::endl;
            Sleep(1000);
            continue; 
        }
        std::cout << "Starting in " << i << " seconds!" << std::endl;
        Sleep(1000);
    }
}
void pressKey(WORD vkey) {
    INPUT input;
    //WORD vkey = VK_F12; // see link below
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vkey;
    input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
/*void pressSlash() {
    INPUT input;
    WORD vkey = 0xA0;
    WORD vkey2 = 0x37;
    //WORD vkey = VK_F12; // see link below
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vkey;
    input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
    SendInput(1, &input, sizeof(INPUT));
    INPUT input2;
    input2.type = INPUT_KEYBOARD;
    input2.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
    input2.ki.time = 0;
    input2.ki.dwExtraInfo = 0;
    input2.ki.wVk = vkey2;
    input2.ki.dwFlags = 0;
    SendInput(1, &input2, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    input2.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input2, sizeof(INPUT));
    //do shit here
}*/

void writeWord(std::string word) {
    //std::cout << std::hex << number << std::endl;
    //pressKey(b);
    std::cout << word << std::endl;
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    std::cout << word << std::endl;
    for (int letter : word) {
        if (letter == 0x2F) {
            letter = 0x6F;
        }
        pressKey(letter);
        std::cout << "Pressed key: " << std::hex << letter << std::endl;
        //pressKey(VK_F12);
        std::cout << letter << std::endl;
    }
}

std::vector<std::string> string_split(const std::string& str) {
    std::vector<std::string> r;
    std::istringstream ss(str);
    for (std::string s; ss >> s;) {
        if (s.find("?") != std::string::npos || s.find("[") != std::string::npos || s.find("]") != std::string::npos || s.find(":") != std::string::npos) { //this is to cut out all the weird stuff and only get the names
            //std::cout << "questionmark was found!" << std::endl;
            continue;
        }
        r.push_back(s);
    }
    return r;
}

std::vector<std::string> get_names(std::string path, int get_value) {
    std::cout << "GETTING NAMES FROM " << path << std::endl;
    std::ifstream instream(path);
    std::string value;
    std::string text;
    //instream >> value;
    //char value = '\n';
    std::vector<std::string> vect;
    int i = 0;
    while (getline(instream, value)) { //DET HER FUCKING VIRKER
        vect.push_back(value);
        text = text + value + '\n';
        //std::cout << "I " << i << " " << value << std::endl;
        i++;
    }
    //std::cout << vect[2] << std::endl;
    std::string n_p_plus_names = vect[2];
    std::vector<std::string> plus_names_v = string_split(n_p_plus_names);
    std::cout << "\n\nPLUS NAMES:" << std::endl;
    for (std::string name : plus_names_v) {
        std::cout << name << std::endl;
    }
    std::string n_p_minus_names = vect[4];
    std::vector<std::string> minus_names_v = string_split(n_p_minus_names);
    std::cout << "\n\nMINUS NAMES:\n" << std::endl;
    for (std::string name : minus_names_v) {
        std::cout << name << std::endl;
    }
    //std::cout << plus_names_v[4]; //plus_names_v[4] is when the names start comming
    if (get_value == 1) {
        return plus_names_v;
    } else if (get_value == 2) {
        return minus_names_v;
    } else { //the get_value says which value u want, 1 is plus rates, 2 is minus rates
        return plus_names_v;
    }
}
int main() {
    std::string logs_folder = getenv("APPDATA");
    logs_folder = logs_folder + "\\.minecraft\\logs";
    if (doesExist(logs_folder+"\\latest.log")) {
        std::cout << "WARNING: THIS WILL CLEAR YOUR latest.log IN THE FOLDER " << logs_folder+"\\latest.log" << std::endl; 
        std::cout << "Please have your minecraft selected and your chat open!" << std::endl;
        start_countdown(3);
        clearFile(logs_folder+"\\latest.log");
        writeWord("/rate s s " + SERVERNAME);
        pressKey(0x0D); //will press ENTER / RETURN KEY
        Sleep(500);
        std::vector<std::string> plus_rates = get_names(logs_folder+"\\latest.log", 1);
        std::vector<std::string> minus_rates = get_names(logs_folder+"\\latest.log", 2);
        //get_names(logs_folder+"\\latest.log");
        //sleep(3);
        //pressSlash(); //it turns out you actually just can juse / in the writeWord(str);
        
        
    } else {
        std::cout << "The file " << logs_folder + "\\latest.log" << " doesn't exist, stopping..." << std::endl;
        Sleep(5000);
        return -1;
    }
    return 0;
}