#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include "include/functions.h"

using namespace std;


// bool CheckDLLPresence(){
//     HANDLE hDLLStatusHandle = GetModuleHandleA("testdll.dll");
//     if (hDLLStatusHandle != NULL){
//         return true;
//     }
//     else return false;    
// }

// void cls(){
//     cout << "\033[2J\033[1;1H";
// }

// void PrintPage(int pageId){
//     switch (pageId)
//     {
//         case 1:
//             printf("1. CreateProcess\n2. OpenProcess\n3. ExitProcess\n");
//             break;
//         case 2:
//             break;
//         case 3:
//             break;
//         case 4:
//             break;
//         case 5:
//             break;
//         default:
//             printf("1. CreateProcess\n2. OpenProcess\n3. ExitProcess\n");
//             break;
//     }
// }




//declaration
bool bDisableSwitch = true;
int page = 1;
int runId = 0;
wchar_t pageName[18];
bool bDllStatus;

char cSelector;

//maps
map<int, string> pageToName {{1,"Process"}, {2, "Thread"}, {3, "Memory"}, {4,"File"}, {5,"Misc"}};
map<bool,string> statusToStr {{true,"\x1b[32m\x1b[1mLOADED\x1b[!p"}, {false, "\x1b[31m\x1b[1mUNLOADED\x1b[!p"}};

int main(int argc, char* argv[]){
    cout << "\nStanding by, awaiting library...\nPress any key after loading to continue...";
    getchar();
    cls();
    while (bDisableSwitch){
        cls();
        cout << "Welcome to function tester.\nCurrent page: " << page << ": " << pageToName[page] << "\n";   
        PrintPage(page);
        bDllStatus = CheckDLLPresence();
        cout << "Current DLL Status: " << statusToStr[bDllStatus] << "\n\n";
        cout << "\x1b[1mInput number to run, input \"P\" to select page, input \"R\" to reload DLL status, \"E\" to exit, \"I\" for info: \x1b[!p";
        cin >> cSelector;
        switch (cSelector)
        {
        case 'P':
            cls();
            cout << "Enter page number: ";
            cin >> page;
            continue;
            break;
        case 'R':
            continue;
            break;
        case 'E':
            bDisableSwitch = false;
            continue;
            break;
        case 'I':
            cls();
            cout << "Current process ID: " << GetCurrentProcessId() << "\nPress any key to continue...";
            getchar();
            continue;
            break;
        default:
            break;
        }
    }
}