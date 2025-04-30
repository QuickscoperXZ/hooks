#include <Windows.h>
#include <iostream>

using namespace std;

HANDLE hProcessHandle;
FARPROC fFunctionPointer;
HMODULE hKernel32Handle;
wchar_t dllPath[] = L"C:\\Users\\userok\\Desktop\\rsrch\\tests\\hooks\\dll_injector\\test_program\\testdll.dll";


int main(int argc, char* argv[]){
    hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,0,atoi(argv[1]));
    if (hProcessHandle !=NULL){
        cout << "\x1b[1m\x1b[32m[+] Process opened.\x1b[!p\n";
    }
    else{
        cout << "\x1b[1m\x1b[31m[-] Unable to open process, last error: " << GetLastError() << ".\x1b[!p";    
    }
    hKernel32Handle = GetModuleHandleW(L"kernel32.dll");
    if (hKernel32Handle != NULL){
        "\x1b[1m\x1b[32m[+] K32 Handle obtained.\x1b[!p\n";
    }
    else {
        cout << "\x1b[1m\x1b[31m[-] Unable to obtain K32 handle, last error: " << GetLastError() << ".\x1b[!p\n";    
    }
    fFunctionPointer = GetProcAddress(hKernel32Handle,"LoadLibraryW");
    if (fFunctionPointer != nullptr){
        "\x1b[1m\x1b[32m[+] Function base address obtained.\x1b[!p\n";
    }
    else {
        cout << "\x1b[1m\x1b[31m[-] Unable to obtain function base address, last error: " << GetLastError() << ".\x1b[!p\n";    
    }
    LPTHREAD_START_ROUTINE lptsrRoutine = (LPTHREAD_START_ROUTINE)fFunctionPointer;



    LPVOID lpAllocated = VirtualAllocEx(hProcessHandle,NULL,sizeof dllPath,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
    if (lpAllocated != NULL){
        "\x1b[1m\x1b[32m[+] Memory allocated\x1b[!p\n";
    }
    else {
        cout << "\x1b[1m\x1b[31m[-] Unable to allocate memory, last error: " << GetLastError() << ".\x1b[!p";    
    }
    SIZE_T bytesWriten;
    if (WriteProcessMemory(hProcessHandle,lpAllocated,&dllPath,sizeof dllPath,&bytesWriten)){
        "\x1b[1m\x1b[32m[+] DLL writen in target process.\x1b[!p\n";
    }
    else {
        cout << "\x1b[1m\x1b[31m[-] Unable to write DLL, last error: " << GetLastError() << ".\x1b[!p";    
    }
    

    HANDLE hRemoteThreadHandle =  CreateRemoteThread(hProcessHandle,NULL,0,lptsrRoutine,lpAllocated,0,NULL);
    if (hRemoteThreadHandle != NULL){
        "\x1b[1m\x1b[32m[+] DLL Loaded.\x1b[!p\n";
    }
    else {
        cout << "\x1b[1m\x1b[31m[-] Unable to load DLL, last error: " << GetLastError() << ".\x1b[!p";    
    }
}