#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <bits/stdc++.h> //apparently this is needed for vectors
//#define WINVER 0x0500 
#include <windows.h>
#include <unistd.h> //this should work even if the linter says there's an error


using std::string;
std::string SERVERNAME = "z";

bool doesExist(const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1);
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
            sleep(1);
            continue; 
        }
        std::cout << "Starting in " << i << " seconds!" << std::endl;
        sleep(1);
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



std::string get_names(std::string path) {
    std::cout << "GETTING NAMES FROM " << path << std::endl;
    std::ifstream instream(path);
    std::string value;
    //instream >> value;
    //char value = '\n';
    int i = 0;
    while (getline(instream, value)) { //DET HER FUCKING VIRKER
        std::cout << "I " << i << " " << value << std::endl;
        i++;
    }
    return "he";
}
std::string o_get_names(std::string path) {
    std::cout << "GETTING NAMES FROM " << path << std::endl;
    //std::string text;
    //std::string t;
    //std::string line;
    std::ifstream instream(path);
    std::string line;
    std::string text;
    while (instream >> line)
    { //den skipper åbenbart den første linje fucking tilt
        text = text + line;
        //std::cout << line;
        if (instream.peek() == '\n') //detect "\n"
        {
            text = text + '\n';
            //std::cout << std::endl;
        }
    }
    instream.close();
    std::stringstream ss(text);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vect(begin, end);
    //std::copy(vect.begin(), vect.end(), std::ostream_iterator<std::string>(std::cout, "\t"));
    std::cout << vect[2] << std::endl; //make the vector include spaces
    //std::cout << text;
    //std::cout << line;
    
    //std::cout << "\n\n" << t.find("Serveren " + SERVERNAME + " har") << string::npos << std::endl;
    return line;
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
        get_names(logs_folder+"\\latest.log");
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