#include <Windows.h>

byte bOriginalBytes[6];
FARPROC fFunctionPointer;
DWORD dwOriginalProtection;

HANDLE __stdcall HookedOpenProcess(DWORD dwAccess, BOOL bInheritance, DWORD dwPid){
    MessageBoxA(NULL,"Hook intercepted OpenProcess call","Hook executed",MB_OK);
    memcpy(fFunctionPointer,bOriginalBytes,6);
    VirtualProtect(fFunctionPointer,6,dwOriginalProtection,nullptr);
    
    HANDLE hOpHandle = OpenProcess(dwAccess, bInheritance, dwPid);

    return hOpHandle; 
}


bool HookAttachTest(){
    HMODULE hKernel32Handle = GetModuleHandleA("kernel32.dll");
    if (hKernel32Handle == NULL){
        return false;
    }
    fFunctionPointer = GetProcAddress(hKernel32Handle, "OpenProcess");
    if (fFunctionPointer == nullptr){
        return false;
    }

    memcpy(bOriginalBytes,fFunctionPointer,6);

    byte bPatch[6] = {0x68, 0x00, 0x00, 0x00, 0x00, 0xC3};
    *(DWORD*)(bPatch + 1) = (DWORD)HookedOpenProcess;

    VirtualProtect(fFunctionPointer,6,PAGE_EXECUTE_READWRITE,&dwOriginalProtection);
    memcpy(fFunctionPointer,bPatch,6);
}

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
    if (fdwReason == DLL_PROCESS_ATTACH){
        HookAttachTest();
        MessageBoxA(NULL,"DLL Attached", "Success", MB_OK);
    }
    return true;
}