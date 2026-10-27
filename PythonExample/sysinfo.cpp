#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <random>
#include <cstdlib>


std::string SystemOSInfo()
{
    std::string cmdSysInfo = "systeminfo | findstr /B /C:\"OS Name\" /B /C:\"OS Version\"";
    auto tempFile = std::filesystem::temp_directory_path() / "tempfile.txt";
    std::string cmd = cmdSysInfo + " >> " + tempFile.string();
    std::system(cmd.c_str());

    std::ifstream file(tempFile, std::ios::in | std::ios::binary);
    std::ostringstream oss;
    oss << file.rdbuf();
    file.close();
    std::filesystem::remove(tempFile);

    return oss.str();
}

void main()
{
    std::string osInfo = SystemOSInfo();
    std::cout << "Operating System Information:\n" << osInfo << std::endl;
}