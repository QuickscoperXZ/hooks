#include <Windows.h>
#include <iostream>

HMODULE hLibHandle = GetModuleHandleA("kernel32.dll");
FARPROC pFunctionPointer = GetProcAddress(hLibHandle,"OpenProcess");
byte bOriginalBytes[6];
int iSelectedPid = NULL;
SIZE_T size;

HANDLE __stdcall Hook(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId){
    std::cout << "function hooked";
    
    if (dwDesiredAccess & PROCESS_ALL_ACCESS){
        std::cout << "\"OpenProcess\" WITH PROCESS_ALL_ACCESS CAUGHT";
        return nullptr;
    }

    WriteProcessMemory(GetCurrentProcess(),(LPVOID)pFunctionPointer,bOriginalBytes,6,&size);

    return OpenProcess(dwDesiredAccess,bInheritHandle,dwProcessId);
}

int main (int argc, char *argv[]){
    if (pFunctionPointer == NULL){
        std::cout << "[-] Unable to get function address.";
        return 1;
    }
    else{
        std::cout << "[+] Got function pointer.\n";
    }

    if (!ReadProcessMemory(GetCurrentProcess(),pFunctionPointer,bOriginalBytes,6,&size)){
        std::cout << "[-] Unable to read process memory.";
        return 1;
    }
    else{
        std::cout << "[+] First bytes backed up.\n";
    }

    DWORD oldProtect;
    if (!VirtualProtectEx(GetCurrentProcess(),pFunctionPointer,6,PAGE_EXECUTE_READWRITE,&oldProtect)){
        std::cout << "[-] Unable to change memory protection";
        return 1;
    }
    else{
        std::cout << "[+] Protection changed.\n";
    }

    std::cout << GetLastError();

    void* pHook = &Hook;
    byte bPatch[6];
    memcpy_s(bPatch,1,"\x68",1);
    memcpy_s(bPatch+1,4,pHook,4);
    memcpy_s(bPatch+5,1,"\xC3",1);

    memcpy(pFunctionPointer, bPatch, 6);

    VirtualProtect(pFunctionPointer,6,oldProtect,&oldProtect);
    //WriteProcessMemory(GetCurrentProcess,(LPVOID)pFunctionPointer,bPatch,6,&size);

    HANDLE test = OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId());
    //std::cout << &test;
}