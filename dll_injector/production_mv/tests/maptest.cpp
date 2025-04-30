#include <iostream>
#include <map>

using namespace std;

int main(int argc, char* argv[]){
    // map<int,string> test = {
        // {1,"abc"},
        // {2,"def"}
    // };
    map<bool,string> test1={
        {true,"LOADED"},
        {false, "NOT LOADED"}
    };
    
    bool a = true;
    cout << test1[a];
}   