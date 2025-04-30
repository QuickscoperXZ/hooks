#include <Windows.h>
#include <iostream>
#include <array>

HMODULE hLibHandle = GetModuleHandleA("User32.dll");
FARPROC pFunctionPointer = GetProcAddress(hLibHandle, "MessageBoxA");
HANDLE hCurrentProcess = GetCurrentProcess();
byte bOriginalBytes[6];
SIZE_T unhookedBytes = 0;

int __stdcall Hook(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType){
    std::cout << "Function call detected, params: \nText:" << lpText <<"\nCaption: " << lpCaption << "\n";

    WriteProcessMemory(hCurrentProcess,pFunctionPointer,bOriginalBytes,6,&unhookedBytes);

    return MessageBoxA(hWnd, "It was changed", "It was changed too",uType);
}

int main(int argc, char *argv[]){

    std::cout << "[+] Got MessageBox ptr: " << pFunctionPointer << "\n";
    
    SIZE_T szReadedBytes = 0;

    ReadProcessMemory(hCurrentProcess,pFunctionPointer,&bOriginalBytes,6,&szReadedBytes);
    
    std::cout << "[+] Got original bytes: " << bOriginalBytes << "\n";

    void* hookedMBAddress = &Hook;
    byte patch[6];
    memcpy_s(patch,1,"\x68",1);
    memcpy_s(patch+1,4,&hookedMBAddress,4);
    memcpy_s(patch+5,1,"\xC3",1);

    std::cout << "[+] Patch created: " << patch;

    SIZE_T szBytesWrited = 0;
    WriteProcessMemory(hCurrentProcess,(LPVOID)pFunctionPointer,patch,6,&szBytesWrited);

    MessageBoxA(NULL,"Test","Test",MB_OK);
}
