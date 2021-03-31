#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
//#define WINVER 0x0500
#include <windows.h>

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

void writeWord(std::string word) {
    std::cout << word << std::endl;
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    std::cout << word << std::endl;
    for (int letter : word) {
        pressKey(letter);
        std::cout << "Pressed key: " << std::hex << letter << std::endl;
        //pressKey(VK_F12);
        std::cout << letter << std::endl;
    }
}

int main() {
    Sleep(3500);
    writeWord("aaa");
    return EXIT_SUCCESS;
}