bool isalpha(unsigned char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
        return true;
    }
    else {
        return false;
    }
}
//

unsigned char tolower(unsigned char c) {
    if (c >= 65 && c<=90){
        c=char(int(c)+32);
    }
    return c;
}
