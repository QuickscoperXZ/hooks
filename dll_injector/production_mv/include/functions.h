#include <Windows.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <functional>
#include <any>

using namespace std;

//typedef void (*fPtr)(void);

bool CheckDLLPresence(){
    HANDLE hDLLStatusHandle = GetModuleHandleA("testdll.dll");
    if (hDLLStatusHandle != NULL){
        return true;
    }
    else return false;    
}

// template <typename returnValue, typename function, typename... Args>
// returnValue runFunction(function fFunction, tuple<Args...> args){
    
//     return apply(function,args);
// }

template <typename returnValue, typename Func, typename... Args>
returnValue runFunction(Func func, tuple<Args...> args){
    
    return apply(func,args);
}

//int a =OpenProcess()

tuple a = make_tuple(PROCESS_ALL_ACCESS,0,GetCurrentProcess());

map<int,function<any(any)>> mFunctionMap = {
    {
        1, runFunction<HANDLE>(OpenProcess,a)
    }
    
};

void ResolveFunction(int pageId, int functionId){
    map<int,int> mPageProcess = {
        {}
    }
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