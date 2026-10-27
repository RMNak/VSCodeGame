#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::wstring> GetLogicalDiskNames() {
    DWORD bufferSize = GetLogicalDriveStrings(0, (LPSTR)NULL);
    if (bufferSize == 0) {
        std::cerr << "Failed to get buffer size for logical drive strings." << std::endl;
        return {};
    }

    std::vector<wchar_t> buffer(bufferSize);
    if (GetLogicalDriveStrings(bufferSize, (LPSTR)buffer.data()) == 0) {
        std::cerr << "Failed to get logical drive strings." << std::endl;
        return {};
    }

    std::vector<std::wstring> driveNames;
    wchar_t* drive = buffer.data();
    while (*drive) {
        driveNames.push_back(drive);
        drive += wcslen(drive) + 1;
    }

    return driveNames;
}

int main() {
    std::vector<std::wstring> driveNames = GetLogicalDiskNames();
    if (driveNames.empty()) {
        std::cerr << "No logical drives found." << std::endl;
        return 1;
    }

    std::wcout << L"Logical Drives:" << std::endl;
    for (const auto& drive : driveNames) {
        std::wcout << drive << std::endl;
    }

    return 0;
}