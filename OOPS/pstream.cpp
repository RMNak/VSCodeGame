#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

std::string ssystem (const char *command) {
    char tempBuffer [L_tmpnam];
    std::tmpnam ( tempBuffer );
    std::string scommand = command;
    std::string cmd = scommand + " >> " + tempBuffer;
    std::system(cmd.c_str());
    std::ifstream file(tempBuffer, std::ios::in | std::ios::binary );
    std::string result;
    if (file) {
        while (!file.eof()) result.push_back((char)file.get())
            ;
        file.close();
    }
    remove(tempBuffer);
    return result;
}

// For Cygwin

int main(int argc, char *argv[])
{
    std::string bash = "systeminfo | findstr /B /C:\"OS Name\" /B /C:\"OS Version\"";
    std::string in;
    std::string s = ssystem(bash.c_str());
    std::istringstream iss(s);
    std::string word = iss.str();
   std::string sysInfo = ""; 
   while (!iss.eof()) {
        std::getline(iss, word, '\n');
        if (word.find("OS Name:") != std::string::npos) {
            sysInfo = word.substr(word.find(":")+1, word.find("\n"));
            std::cout << sysInfo.erase(0, sysInfo.find_first_not_of(" \t\n\r\f\v") )<< std::endl;
        }
        else if(word.find("OS Version:") != std::string::npos) {
            sysInfo = word.substr(word.find(":")+1, word.find("\n"));
            std::cout << sysInfo.erase(0, sysInfo.find_first_not_of(" \t\n\r\f\v") )<< std::endl;
        }
    }
    // std::string OSName = iss.str().substr(0, iss.str().find("\n"));
    // std::string OSVersion = iss.str().substr(iss.str().find("\n"), iss.str().length());
    // std::cout <<OSName << " ===> " << OSVersion << std::endl;
    return 0;
}