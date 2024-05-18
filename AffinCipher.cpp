#include <iostream>
#include <string>
#include "AffinCipher.h"
std::string EncodeAffin(std::string alphabet, std::string text) {
    std::string rezult;
    std::cout << "Enter the first key\n";
    int a,b;
    std::cin >> a;
    std::cout << "Enter the second key\n";
    std::cin >> b;
    int mod = alphabet.size();
    for (int i = 0; i < text.size(); i++) rezult += alphabet[((a * alphabet.find(text[i])) + b) % mod];
    return rezult;
}
std::string DecodeAffin(std::string alphabet, std::string text) {
    std::string rezult;
    int a,b;
    std::cout << "Enter the first key\n";
    std::cin >> a;
    std::cout << "Enter the second key\n";
    std::cin >> b;
    int mod = alphabet.size();
    int r;
    while (true) {
        if (r % a == 0 && r % mod == 1) break;
        r += 1;
    }
    int a1 = ( (r / a) % mod );
    int nod = 1;
    int mx = 0;
    if (a >= mod) mx = a;
    else mx = mod;
    for (int i = 1; i <= mx; i ++) {
        if (a % i == 0 && mod % i == 0) nod = i;
    }
    if (nod == 1) {
        for (int i = 0; i < text.size(); i++) {
            rezult += alphabet[((alphabet.find(text[i]) - b + mod) * a1) % mod];

        }
    }
    return rezult;
}