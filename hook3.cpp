#include <Windows.h>
#include <iostream>

byte ogbytes[6];

HANDLE __stdcall HOP(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessID){
    std::cout << "good";
    return OpenProcess(dwDesiredAccess,bInheritHandle,dwProcessID);
}


int main (int argc, char *argv[]){

    HMODULE k32 = GetModuleHandleA("kernel32.dll");
    FARPROC fptr = GetProcAddress(k32,"OpenProcess");

    memcpy(ogbytes,fptr,6);

    BYTE patch[6] = { 0x68, 0x00, 0x00, 0x00, 0x00, 0xC3 };
    *(DWORD*)(patch + 1) = (DWORD)HOP;

    DWORD op;
    VirtualProtect(fptr,6,PAGE_EXECUTE_READWRITE,&op);

    memcpy(fptr,patch,6);

    VirtualProtect(fptr,6,op,&op);

    OpenProcess(PROCESS_ALL_ACCESS,0, GetCurrentProcessId());
}
