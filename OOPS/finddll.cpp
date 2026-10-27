#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

// Function to get the path of the current module (DLL or EXE)
std::string GetModulePath(HMODULE hModule) {
    char path[MAX_PATH];
    if (GetModuleFileNameA(hModule, path, MAX_PATH) == 0) {
        std::cerr << "Failed to get module path. Error code: " << GetLastError() << std::endl;
        return "";
    }
    return std::string(path);
}

int main() {
    // Get the path of the current executable
    std::string exePath = GetModulePath(NULL);
    std::cout << "Executable Path: " << exePath << std::endl;

    // If you want to get the path of a specific DLL, you need to get its handle first
    // For demonstration, let's assume we have a DLL named "example.dll" loaded
    HMODULE hDll = LoadLibraryA("hcl_mail_sync32.dll");
    if (hDll != NULL) {
        std::string dllPath = GetModulePath(hDll);
        std::cout << "DLL Path: " << dllPath << std::endl;
        FreeLibrary(hDll);
    } else {
        std::cerr << "Failed to load example.dll. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}