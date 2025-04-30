#include <Windows.h>
#include <iostream>

int main(int argc, char* argv[]){ 
    std::cout << "\nStanding by, awaitin library...\nPress any key after loading to continue...";
    
    getchar();
    //HMODULE hLoadedLibHandle;

    //hLoadedLibHandle = LoadLibraryW(L"C:\\Users\\userok\\Desktop\\rsrch\\tests\\hooks\\dl_injector\\test_program\\testdll.dll");

    // if (hLoadedLibHandle == nullptr){
    //     MessageBoxA(NULL,"ERROR: DLL NOT LOADED","ERROR",MB_ICONERROR | MB_OK);
    //     return 1;
    // }
    // else{
        std::cout << "Press any key to run OpenProcess... \n";
        getchar();
        OpenProcess(PROCESS_ALL_ACCESS,false,GetCurrentProcessId());
        return 0;
    // }
}