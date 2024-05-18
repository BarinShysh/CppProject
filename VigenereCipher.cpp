#include <iostream>
#include <string>
#include "VigenereCipher.h"
int keycode(char s) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < alphabet.size(); i ++ ) {
        if ( s == alphabet[i]) return i;
    }
    return 0;
}
std::string EncodeVigenere(std::string alphabet,std::string text, std::string key) {
    std::string cipher;
    for ( int i = 0; i < text.size(); i ++) {
        cipher += alphabet[(keycode(text[i]) + keycode(key[i % key.size()])) % alphabet.size()];
    }
    return cipher;
}
std::string DecodeVigenere(std::string alphabet, std::string text, std::string key){
    std::string code;
    for ( int i  = 0; i < text.size(); i ++) {
        code += alphabet[(keycode(text[i]) - keycode(key[i % key.size()]) + alphabet.size()) % alphabet.size()];
    }
    return code;
}