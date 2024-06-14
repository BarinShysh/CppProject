#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "VigenereCipher.h"
#include "SimpleSubCipher.h"
#include "AffinCipher.h"
std::string encodeCaesar(const std::string& alphabet, const std::string& message, int shift) {
    std::string encodedMessage;
    for (char c : message) {
        if (alphabet.find(c) != std::string::npos) {
            int index = (alphabet.find(c) + shift) % alphabet.size();
            encodedMessage += alphabet[index];
        }
        else {
            encodedMessage += c;
        }
    }
    return encodedMessage;
}
std::string decodeCaesar(const std::string& alphabet, const std::string& message, int shift) {
    std::string decodedMessage;
    for (char c : message) {
        if (alphabet.find(c) != std::string::npos) {
            int index = (alphabet.find(c) - shift + alphabet.size()) % alphabet.size();
            decodedMessage += alphabet[index];
        }
        else {
            decodedMessage += c; // Если символ не найден в алфавите, просто добавляем его без изменений
        }
    }
    return decodedMessage;
}
class EnigmaMachine {
public:
    EnigmaMachine(const std::vector<std::string>& rotors, const std::string& reflector)
        : rotors_(rotors), reflector_(reflector), rotor_positions_(rotors.size(), 0) {}

    void setRotorPositions(const std::vector<int>& positions) {
        if (positions.size() != rotors_.size()) {
            throw std::invalid_argument("Number of positions must match number of rotors");
        }
        rotor_positions_ = positions;
    }
    char encodeChar(char ch) {
        if (ch < 'A' || ch > 'Z') {
            throw std::invalid_argument("Input character must be an uppercase letter A-Z");
        }
        stepRotors();
        return transformCharacter(ch);
    }
    std::string encodeMessage(const std::string& message) {
        std::string encoded_message;
        for (char ch : message) {
            if (ch >= 'A' && ch <= 'Z') {
                encoded_message += encodeChar(ch);
            }
            else {
                encoded_message += ch;  // preserve non-alphabet characters
            }
        }
        return encoded_message;
    }
    std::string decodeMessage(const std::string& message) {
        // For Enigma, encode and decode are the same operation
        return encodeMessage(message);
    }
private:
    std::vector<std::string> rotors_;
    std::string reflector_;
    std::vector<int> rotor_positions_;
    void stepRotors() {
        for (size_t i = 0; i < rotors_.size(); ++i) {
            if (++rotor_positions_[i] < 26) {
                break;
            }
            rotor_positions_[i] = 0;
        }
    }
    char transformCharacter(char ch) {
        int index = ch - 'A';
        for (size_t i = 0; i < rotors_.size(); ++i) {
            index = (index + rotor_positions_[i]) % 26;
            index = rotors_[i][index] - 'A';
            index = (index - rotor_positions_[i] + 26) % 26;
        }
        index = reflector_[index] - 'A';
        for (int i = rotors_.size() - 1; i >= 0; --i) {
            index = (index + rotor_positions_[i]) % 26;
            index = std::find(rotors_[i].begin(), rotors_[i].end(), 'A' + index) - rotors_[i].begin();
            index = (index - rotor_positions_[i] + 26) % 26;
        }
        return 'A' + index;
    }
};
int main() {
    std::vector<std::string> rotors = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO"
    };
    std::string reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    EnigmaMachine enigma(rotors, reflector);

    while (true) {
        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string text;
        std::cout << "Enter your text: ";
        std::cin >> text;
        for (auto& c : text) c = toupper(c);
        int choice_cipher;
        std::cout << "\nChoose your cipher:\n (1) - Simple substitution cipher, (2) - Vigenere cipher, (3) - Affin cipher, (4) - Enigma cipher, (5) - Caesar cipher.\n";
        std::cin >> choice_cipher;
        if (choice_cipher == 1) {
            std::string key;
            std::cout << "Enter your key: ";
            std::cin >> key;
            for (auto& c : key) c = toupper(c);
            std::cout << "\n Choose what you want: (1) - Encode, (2) - Decode\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) std::cout << EncodeSimple(alphabet, text, key);
            else if (choice == 2) std::cout << DecodeSimple(alphabet, text, key);
        }
        else if (choice_cipher == 2) {
            std::string key;
            std::cout << "Enter your key: ";
            std::cin >> key;
            for (auto& c : key) c = toupper(c);
            std::cout << "\nChoose what you want: (1) - Encode, (2) - Decode\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) std::cout << EncodeVigenere(alphabet, text, key) << "\n";
            else if (choice == 2) std::cout << DecodeVigenere(alphabet, text, key) << "\n";
        }
        else if (choice_cipher == 3) {
            int key1, key2;
            std::cout << "Enter your keys: ";
            std::cin >> key1;
            std::cin >> key2;
            std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) std::cout << EncodeAffin(alphabet, text, key1, key2) << "\n";
            if (choice == 2) std::cout << DecodeAffin(alphabet, text, key1, key2) << "\n";
        }
        else if (choice_cipher == 4) {
            enigma.setRotorPositions({ 0, 0, 0 });  // Reset rotor positions
            std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) std::cout << enigma.encodeMessage(text) << "\n";
            else if (choice == 2) std::cout << enigma.decodeMessage(text) << "\n";
        }
        else if (choice_cipher == 5) {
            int shift;
            std::cout << "Enter your shift value \n";
            std::cin >> shift;
            std::cout << "Choose what you want: (1) - Encode, (2) - Decode\n";
            int choice;
            std::cin >> choice;
            if (choice == 1) std::cout << encodeCaesar(alphabet, text, shift) << "\n";
            else if (choice == 2) std::cout << decodeCaesar(alphabet, text, shift) << "\n";
        }
    }
}
