#include <iostream>
#include <string>
#include "VigenereCipher.h"
#include "SimpleSubCipher.h"
#include "AffinCipher.h"

int main () {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string text, key;
    std::cout << "Enter your text\n";
    std::cin >> text;
    for (auto &c: text) c = toupper(c);
    int choice_cipher;
    std::cout << "Choose your cipher:\n (1) - Simple substitution cipher, (2) - Vigenere cipher, (3) - Affin cipher.\n";
    std::cin >> choice_cipher;
    if (choice_cipher == 1) {
        std::cout << "Enter your key \n";
        std::cin >> key;
        for (auto &c: key) c = toupper(c);
        std::cout << "Choose what are you want (1) - Encode, (2) - Decode\n";
        int choice;
        std::cin >> choice;
        if (choice == 1) std:: cout << EncodeSimple(alphabet, text, key);
        else if (choice == 2) std::cout << DecodeSimple(alphabet, text, key);
    }
    else if (choice_cipher == 2) {
        std::cout << "Enter your key \n";
        std::cin >> key;
        for (auto &c: key) c = toupper(c);
        std::cout << "Choose what are you want (1) - Encode, (2) - Decode\n";
        int choice;
        std::cin >> choice;
        if (choice == 1) std:: cout << EncodeVigenere(alphabet, text, key);
        else if (choice == 2) std::cout << DecodeVigenere(alphabet, text, key);
    }
    else if (choice_cipher == 3) {
        for (auto &c: key) c = toupper(c);
        std::cout << "Choose what are you want (1) - Encode, (2) - Decode\n";
        int choice;
        std::cin >> choice;
        if (choice == 1) std:: cout << EncodeAffin(alphabet, text);
        if (choice == 2) std::cout << DecodeAffin(alphabet, text);
    }
}