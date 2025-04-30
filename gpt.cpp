#include <Windows.h>
#include <iostream>

typedef HANDLE(WINAPI* tOpenProcess)(DWORD, BOOL, DWORD);

tOpenProcess originalOpenProcess = nullptr;
BYTE originalBytes[6] = { 0 }; // Save 6 bytes for push/ret
bool isHooked = false;

HANDLE WINAPI HookedOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{
    std::cout << "[HOOK] OpenProcess called! PID: " << dwProcessId 
              << ", Access: 0x" << std::hex << dwDesiredAccess << std::dec << std::endl;

    // Block PROCESS_ALL_ACCESS
    if (dwDesiredAccess & PROCESS_ALL_ACCESS)
    {
        std::cout << "[BLOCKED] PROCESS_ALL_ACCESS denied!" << std::endl;
        return nullptr;
    }

    // Call original function
    return originalOpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
}

bool InstallHook()
{
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    if (!hKernel32)
    {
        std::cerr << "[-] Failed to get kernel32.dll handle" << std::endl;
        return false;
    }

    originalOpenProcess = (tOpenProcess)GetProcAddress(hKernel32, "OpenProcess");
    if (!originalOpenProcess)
    {
        std::cerr << "[-] Failed to find OpenProcess" << std::endl;
        return false;
    }

    // Save original bytes (6 bytes for push/ret)
    memcpy(originalBytes, originalOpenProcess, 6);

    // Prepare the push/ret patch:
    // 68 XX XX XX XX   PUSH HookedOpenProcess
    // C3               RET
    BYTE patch[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };
    *(DWORD*)(patch + 1) = (DWORD)HookedOpenProcess; // Write absolute address

    // Change memory protection to allow writing
    DWORD oldProtect;
    if (!VirtualProtect(originalOpenProcess, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        std::cerr << "[-] Failed to change memory protection" << std::endl;
        return false;
    }

    // Apply the hook
    memcpy(originalOpenProcess, patch, 6);

    // Restore protection
    VirtualProtect(originalOpenProcess, 6, oldProtect, &oldProtect);

    isHooked = true;
    std::cout << "[+] Hook installed successfully (push/ret method)" << std::endl;
    return true;
}

bool RemoveHook()
{
    if (!isHooked || !originalOpenProcess)
        return false;

    DWORD oldProtect;
    if (!VirtualProtect(originalOpenProcess, 6, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        std::cerr << "[-] Failed to change memory protection (unhook)" << std::endl;
        return false;
    }

    // Restore original bytes
    memcpy(originalOpenProcess, originalBytes, 6);

    VirtualProtect(originalOpenProcess, 6, oldProtect, &oldProtect);
    isHooked = false;
    std::cout << "[+] Hook removed successfully" << std::endl;
    return true;
}

int main()
{
    if (!InstallHook())
    {
        std::cerr << "[-] Failed to install hook!" << std::endl;
        return 1;
    }

    // Test 1: Block PROCESS_ALL_ACCESS
    HANDLE hTest = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    if (!hTest)
        std::cout << "[TEST] Blocked PROCESS_ALL_ACCESS (working correctly)" << std::endl;
    else
        CloseHandle(hTest);

    // Test 2: Allow PROCESS_QUERY_INFORMATION
    hTest = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, GetCurrentProcessId());
    if (hTest)
    {
        std::cout << "[TEST] Allowed PROCESS_QUERY_INFORMATION (working correctly)" << std::endl;
        CloseHandle(hTest);
    }

    RemoveHook();
    return 0;
}