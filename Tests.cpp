#include <gtest/gtest.h>
#include "AffinCipher.h"
#include "VigenereCipher.h"

// Прототипы функций EncodeSimple и DecodeSimple
std::string EncodeSimple(std::string alphabet, std::string text, std::string key);
std::string DecodeSimple(std::string alphabet, std::string text, std::string key);

// AffineCipher tests
TEST(AffineCipherTest, EncodeTest) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(EncodeAffin(alphabet, "HELLO", 5, 8), "RCLLA");
}

TEST(AffineCipherTest, DecodeTest) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(DecodeAffin(alphabet, "RCLLA", 5, 8), "HELLO");
}

// VigenereCipher tests
TEST(VigenereCipherTest, EncodeBasic) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(EncodeVigenere(alphabet, "HELLO", "KEY"), "RIJVS");
}

TEST(VigenereCipherTest, DecodeBasic) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(DecodeVigenere(alphabet, "RIJVS", "KEY"), "HELLO");
}

TEST(VigenereCipherTest, EncodeWithLongKey) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(EncodeVigenere(alphabet, "HELLO", "LONGKEY"), "SSYRY");
}

TEST(VigenereCipherTest, DecodeWithLongKey) {
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    EXPECT_EQ(DecodeVigenere(alphabet, "SSYRY", "LONGKEY"), "HELLO");
}

// EncodeSimple tests
TEST(EncodeSimpleTest, CorrectKey) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfedcba";
    std::string text = "hello";
    std::string expected = "svool";
    
    EXPECT_EQ(EncodeSimple(alphabet, text, key), expected);
}

TEST(EncodeSimpleTest, IncorrectKey) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfed";
    std::string text = "hello";
    std::string expected = "Error. Key entered incorrectly.";
    
    EXPECT_EQ(EncodeSimple(alphabet, text, key), expected);
}

TEST(EncodeSimpleTest, EmptyText) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfedcba";
    std::string text = "";
    std::string expected = "";
    
    EXPECT_EQ(EncodeSimple(alphabet, text, key), expected);
}

// DecodeSimple tests
TEST(DecodeSimpleTest, CorrectKey) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfedcba";
    std::string text = "svool";
    std::string expected = "hello";
    
    EXPECT_EQ(DecodeSimple(alphabet, text, key), expected);
}

TEST(DecodeSimpleTest, IncorrectKey) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfed";
    std::string text = "svool";
    std::string expected = "Error. Key entered incorrectly.";
    
    EXPECT_EQ(DecodeSimple(alphabet, text, key), expected);
}

TEST(DecodeSimpleTest, EmptyText) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "zyxwvutsrqponmlkjihgfedcba";
    std::string text = "";
    std::string expected = "";
    
    EXPECT_EQ(DecodeSimple(alphabet, text, key), expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}