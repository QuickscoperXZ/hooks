#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

using namespace std;

bool CheckDLLPresence(){
    HANDLE hDLLStatusHandle = GetModuleHandleA("testdll.dll");
    if (hDLLStatusHandle != NULL){
        return true;
    }
    else return false;    
}

void cls(){
    cout << "\033[2J\033[1;1H";
}

void PrintPage(int pageId){
    switch (pageId)
    {
        case 1:
            printf("1. CreateProcess\n2. OpenProcess\n3. ExitProcess\n");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("1. CreateProcess\n2. OpenProcess\n3. ExitProcess\n");
            break;
    }
}