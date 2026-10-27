#include <windows.h>
#include <mapi.h>
#include <iostream>
#include <string>

#pragma comment(lib, "mapi32.lib")

void UpdateFreeBusy(const std::wstring& email, const std::wstring& freeBusyData) {
    HRESULT hr;
    LPMAPISESSION lpSession = nullptr;

    // Initialize MAPI
    hr = MAPIInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize MAPI. Error: " << hr << std::endl;
        return;
    }

    // Log on to the MAPI session
    hr = MAPILogonEx(0, NULL, NULL, MAPI_EXTENDED | MAPI_USE_DEFAULT, &lpSession);
    if (FAILED(hr)) {
        std::cerr << "Failed to log on to MAPI session. Error: " << hr << std::endl;
        MAPIUninitialize();
        return;
    }

    // Get the address book
    LPADRBOOK lpAddrBook = nullptr;
    hr = lpSession->OpenAddressBook(0, NULL, 0, &lpAddrBook);
    if (FAILED(hr)) {
        std::cerr << "Failed to open address book. Error: " << hr << std::endl;
        lpSession->Release();
        MAPIUninitialize();
        return;
    }

    // Create an entry ID for the recipient
    ULONG cbEID = 0;
    LPENTRYID lpEID = nullptr;

    hr = lpAddrBook->CreateOneOff(
        (LPTSTR)email.c_str(), // Email address
        NULL,                  // No display name
        NULL,                  // No address type
        MAPI_UNICODE,          // Unicode flag
        &cbEID,                // Entry ID size
        &lpEID                 // Entry ID
    );

    if (FAILED(hr)) {
        std::cerr << "Failed to create entry ID. Error: " << hr << std::endl;
        lpAddrBook->Release();
        lpSession->Release();
        MAPIUninitialize();
        return;
    }

    // Open the Free/Busy message
    LPMESSAGE lpMessage = nullptr;
    hr = lpSession->OpenEntry(cbEID, lpEID, NULL, MAPI_MODIFY, NULL, (LPUNKNOWN*)&lpMessage);
    if (FAILED(hr)) {
        std::cerr << "Failed to open Free/Busy message. Error: " << hr << std::endl;
        lpAddrBook->Release();
        lpSession->Release();
        MAPIUninitialize();
        return;
    }

    // Update the Free/Busy data
    SPropValue propValue;
    propValue.ulPropTag = PR_FREE_BUSY_ENTRYIDS; // Property tag for Free/Busy data
    propValue.Value.lpszA = (LPSTR)freeBusyData.c_str();

    hr = lpMessage->SetProps(1, &propValue, NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to set Free/Busy data. Error: " << hr << std::endl;
    } else {
        std::cout << "Free/Busy data updated successfully." << std::endl;
    }

    // Save changes
    hr = lpMessage->SaveChanges(0);
    if (FAILED(hr)) {
        std::cerr << "Failed to save changes to Free/Busy message. Error: " << hr << std::endl;
    }

    // Cleanup
    lpMessage->Release();
    lpAddrBook->Release();
    lpSession->Release();
    MAPIUninitialize();
}

int main() {
    std::wstring email = L"user@example.com"; // Replace with the target email address
    std::wstring freeBusyData = L"Updated Free/Busy data"; // Replace with the actual Free/Busy data

    UpdateFreeBusy(email, freeBusyData);
    return 0;
}