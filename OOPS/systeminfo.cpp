#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <cstdio>
#include <windows.h>

using namespace std;

wstring RegGetString(HKEY hKey, const string& subkey, const wstring& valueName) {
    // Provide the implementation for RegGetString here
      DWORD val;
      DWORD dataSize = sizeof(val);
      if (ERROR_SUCCESS == RegGetValueA(hKey, "SOFTWARE\\Microsoft\\Office\\ClickToRun\\Inventory\\Office\\16.0", "OfficePackageVersion", RRF_RT_DWORD, nullptr /*type not required*/, &val, &dataSize)) {
      printf("Value is %i\n", val);
      // no CloseKey needed because it is a predefined registry key
      }
      else {
      printf("Error reading.\n");
      }

      return L"";
}

wstring GetRegistry(const string& keyPath, const string& valueName) {
    wstring s = RegGetString(HKEY_CURRENT_USER, keyPath, L"MyStringValue");
    return s;
}

int main() {
    try {
        string keyPath = "SOFTWARE\\Microsoft\\Office\\ClickToRun\\Inventory\\Office\\16.0";
        string valueName = "OfficePackageVersion";
        wstring productName = GetRegistry(keyPath, valueName);
        wcout << "Product Name: " << productName << endl;
    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}