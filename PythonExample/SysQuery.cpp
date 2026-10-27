#include <windows.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#include <iostream>

#pragma comment(lib, "wbemuuid.lib")

std::string WStringToUtf8(const std::wstring& input)
{
    if (input.empty()) return std::string();

    int sizeNeeded = WideCharToMultiByte(
        CP_UTF8,
        0,
        input.c_str(),
        static_cast<int>(input.size()),
        NULL,
        0,
        NULL,
        NULL);

    if (sizeNeeded <= 0) return std::string();

    std::string output(sizeNeeded, '\0');
    WideCharToMultiByte(
        CP_UTF8,
        0,
        input.c_str(),
        static_cast<int>(input.size()),
        &output[0],
        sizeNeeded,
        NULL,
        NULL);

    return output;
}

std::wstring GetWindowsOSInfoWMI()
{
    HRESULT hres;

    // Initialize COM
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) return L"";

    // Set COM security
    hres = CoInitializeSecurity(
        NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, EOAC_NONE, NULL);
    if (FAILED(hres)) {
        CoUninitialize();
        return L"";
    }

    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);
    if (FAILED(hres)) {
        CoUninitialize();
        return L"";
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0,
        NULL, 0, 0, &pSvc);
    if (FAILED(hres)) {
        pLoc->Release();
        CoUninitialize();
        return L"";
    }

    // Set security levels
    hres = CoSetProxyBlanket(
        pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, EOAC_NONE);

    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT Caption, Version, BuildNumber FROM Win32_OperatingSystem"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL, &pEnumerator);

    if (FAILED(hres)) {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return L"";
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;
    std::wstring result;

    if (pEnumerator) {
        hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (uReturn) {
            VARIANT vtProp;

            pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
            result += vtProp.bstrVal;
            VariantClear(&vtProp);

            result += L":";

            pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
            result += vtProp.bstrVal;
            VariantClear(&vtProp);

            result += L" Build ";

            pclsObj->Get(L"BuildNumber", 0, &vtProp, 0, 0);
            result += vtProp.bstrVal;
            VariantClear(&vtProp);

            pclsObj->Release();
        }
        pEnumerator->Release();
    }

    pSvc->Release();
    pLoc->Release();
    CoUninitialize();

    return result;
}

void main()
{
    std::wstring osInfo = GetWindowsOSInfoWMI();
    std::string osInfoUtf8 = WStringToUtf8(osInfo);
    std::cout << "Operating System Information:\n" << osInfoUtf8 << std::endl;
}
