#include <Windows.h>
#include <iostream>

using namespace std;

bool CheckDllPresence(char moduleName[]){
    HMODULE hModuleHandle = GetModuleHandleA(moduleName);
    if (hModuleHandle != NULL){
        return true;
    }
    return false;
}

void cls(){
    cout << "\033[2J\033[1;1H";
}

// bool sw = true;

int main(int argc, char *argv[]){
    //while (sw){
        printf("Current process PID: %i\n", GetCurrentProcessId());
        printf("Waiting for input...");
        getchar();
        cls();
        printf("DLL Status: ");
        if (CheckDllPresence(argv[1])){
            cout << "Loaded";
        }
        else{
            cout << "Not Loaded";
        }
        getchar();
    //}
}