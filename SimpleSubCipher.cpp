#include <iostream>
#include <string>
#include "SimpleSubCipher.h"
std::string EncodeSimple(std::string alphabet, std::string text, std::string key){
    int ind;
    std::string encoded_text;
    if(key.size() == alphabet.size()) {
        for (int i = 0; i < text.size(); i ++) {
            ind = alphabet.find(text[i]);
            encoded_text += key[ind];
        }
        return encoded_text;
    }
    else return "Error. Key entered incorrectly.";
}
std::string DecodeSimple(std::string alphabet, std::string text, std::string key) {
    int ind;
    std::string Decoded_text;
    if (key.size() == alphabet.size()){
        for (int i = 0; i< text.size(); i ++ ) {
            ind  = key.find(text[i]);
            Decoded_text += alphabet[ind];
        }
        return Decoded_text;
    }
    else return "Error. Key entered incorrectly.";
}