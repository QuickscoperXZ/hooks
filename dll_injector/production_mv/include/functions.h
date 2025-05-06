#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <functional>
#include <any>
#include <array>

using namespace std;

typedef map<int,any> anymap;

bool CheckDLLPresence(){
    HANDLE hDLLStatusHandle = GetModuleHandleA("testdll.dll");
    if (hDLLStatusHandle != NULL){
        return true;
    }
    else return false;    
}

//maps
anymap fmap = {
    {2,function<HANDLE(DWORD,BOOL,DWORD)>(OpenProcess)}
};

anymap amap = {
    {2,tuple<DWORD,BOOL,DWORD>(PROCESS_ALL_ACCESS,0,GetCurrentProcessId())}
};

template <typename rType, typename... Args>
void run(int id){
    auto runner = any_cast<function<rType(Args...)>>(fmap[id]);
    auto runnerArgs = any_cast<tuple<Args...>>(amap[id]);
    if (id == 2){
        HANDLE cPH = apply(runner,runnerArgs);
        if (cPH != nullptr){
            cout << "\x1b[31mSuccess\x1b[!p";
        }
        else cout << "\x1b[32mFail\x1b[!p";
    }
};

int resolveId(int pageId, int id){
    return pageId+id;
};

void runById(int id){
    switch (id)
    {
    case 2:
        run<HANDLE,DWORD,BOOL,DWORD>(2);
        break;
    
    default:
        break;
    }
}





//clear
void cls(){
    cout << "\033[2J\033[1;1H";
}

//pages
array<int,5> GetPageIds(int page){
    switch (page)
    {
    case 1:
        return {1,2,3};
        break;
    
    default:
        return {1,2,3};
        break;
    }
};

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