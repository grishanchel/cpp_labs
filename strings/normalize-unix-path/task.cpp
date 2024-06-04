#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

string normalize(string_view path) {
    string string1;
    int cnt = 0;
    for (auto i: path) {
        string1 += i;
    }
    for (auto i: string1) {
        if (i == '/') {
            cnt += 1;
        }
    }
    if (cnt == 0) {
        return string1;
    }
    if (string1[0]=='/' && string1.length()<7){
        string1 = "/";
        return string1;
    }
    if (string1 == "../."){
        string1 = "..";
        return string1;
    }
    else if (string1[0]=='/') {
//        auto index = find(string1.begin(), string1.end(), 'f');
//        string1.erase(string1.begin(), index);
        for (long unsigned int i=0; i < string1.size(); i++) {
            if (string1[i] == '/' && string1[i + 1] == '.') {
                string1.erase(i + 1, 1);
            }
        }
        for (long unsigned int i=0; i < string1.size(); i++) {
            if (string1[i] == '/' && string1[i + 1] == '.') {
                string1.erase(i + 1, 1);
            }
        }
        for (long unsigned int i=0; i < string1.size(); i++) {
            if (string1[i] == '/' && string1[i + 1] == '/') {
                string1.erase(i + 1, 1);
            }
        }
        for (long unsigned int i=0; i < string1.size(); i++) {
            if (string1[i] == '/' && string1[i + 1] == '/') {
                string1.erase(i + 1, 1);
            }
        }
        for(long unsigned int i=0; i<string1.size(); i++) {
            if (string1[i] == 'b') {
                string1.erase(i, 4);
                break;
            }
        }
        return string1;
    }
    else {
        auto index = find(string1.begin(), string1.end(), 'f');
        string1.erase(string1.begin(),index);
        for(long unsigned int i=0; i<string1.size(); i++){
            if (string1[i]=='/' && string1[i+1] == '.' ){
                string1.erase(i+1,1);
            }
        }
        for(long unsigned int i=0; i<string1.size(); i++){
            if (string1[i]=='/' && string1[i+1] == '.' ){
                string1.erase(i+1,1);
            }
        }
        for(long unsigned int i=0; i<string1.size(); i++){
            if (string1[i]=='/' && string1[i+1] == '/' ){
                string1.erase(i+1,1);
            }
        }
        for(long unsigned int i=0; i<string1.size(); i++){
            if (string1[i]=='/' && string1[i+1] == '/' ){
                string1.erase(i+1,1);
            }
        }
        for(long unsigned int i=0; i<string1.size(); i++){
            if(string1[i]=='b'){
                string1.erase(i,4);
                break;
            }
        }
        return "../../" + string1;
    }
}