#include <Windows.h>
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

template <typename ret, typename Func, typename... Args>
ret runByName(Func function, tuple<Args...> args){
    return apply(function,args);
}
int ShowMessageBox(const tuple<HWND, LPCSTR, LPCSTR, UINT>& args) {
    return apply(MessageBoxA, args);
}

int main(int argc, char* argv[]){
    auto a = make_tuple(nullptr,"test","test",MB_OK);
    
    auto args = make_tuple(
        nullptr,                     // HWND (nullptr = no owner window)
        "Hello from WinAPI!",        // LPCSTR (message)
        "Title",                     // LPCSTR (title)
        MB_OK | MB_ICONINFORMATION   // UINT (flags)
    );
    
    //OpenProcess()   

    auto b = make_tuple(PROCESS_ALL_ACCESS,0,GetCurrentProcessId());

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    HANDLE test = runByName<HANDLE>(OpenProcess,b);
    if (test != nullptr){
        SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
        printf("\x1B[32mHandle aquired\x1B[!p");
    }
    else{
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
        printf("Can't get a handle");
    }
}