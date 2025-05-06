#include <Windows.h>
#include <iostream>
#include <map>
#include <tuple>
#include <functional>
#include <utility>
#include <any>
#include <vector>

using namespace std;

// typedef void (*fPTR)(void);
// typedef map<int,fPTR> fptrmap;
class callFunctions{
    tuple<DWORD,BOOL,DWORD> fOpenProcessArgs = make_tuple(PROCESS_ALL_ACCESS,0,GetCurrentProcessId());
    map<int,any> fmap = {
        {1,function<HANDLE(DWORD,BOOL,DWORD)>(OpenProcess)},
        {2,function<int(HWND,LPCSTR,LPCSTR,UINT)>(MessageBoxA)}
    };
    map<int,any> amap = {
        {1,tuple<DWORD,BOOL,DWORD>(PROCESS_ALL_ACCESS,0,GetCurrentProcessId())},
        {2,tuple<HWND,LPCSTR,LPCSTR,UINT>(NULL,"1","2",MB_OK)}
    };
    public:
    callFunctions(){
        //MessageBoxA(NULL,"1","2",MB_OK);
    };

    template <typename rType, typename... Args>
    void run(int id){
        auto runner = any_cast<function<rType(Args...)>>(fmap[id]);
        auto runnerArgs = any_cast<tuple<Args...>>(amap[id]);
        apply(runner,runnerArgs);
    }
};


int main(int argc, char* argv[]){
    callFunctions cf = callFunctions();
    //cf.run<HANDLE,DWORD,BOOL,DWORD>(1);
    cf.run<int,HWND,LPCSTR,LPCSTR,UINT>(2);
}
