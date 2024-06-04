#include "task.h"
#include <vector>

using namespace std;

bool is_palindrome(const std::string& s) {
    string s1 = s;
    for(int i = 0; i<(int)s1.size(); i++){
        char x = s1[i];
        if ((int)x < 65 || (int)x > 122 || ((int)x > 92 && (int)x < 97)){
            s1.erase(i,1);
            i--;
        }
        if ((int)x>64 && (int)x < 91)
        {
            x+=32;
            s1[i]=x;
        }
    }
    int p = 1;
    for (int i = 0; i<(int)s1.size(); i++){
        if(s1[i]!=s1[(int)s1.size()-1-i]){
            p=0;
            break;
        }
    }
    if (p==1){
        return true;
    }
    return false;
}































































