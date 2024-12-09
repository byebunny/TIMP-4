#include "modAlphaCipher.h"
#include <iostream>
#include <algorithm>
#include <vector> 

modCipher::modCipher(int skey, std::string text) {
    if (text.empty()) {
        throw cipher_error("Отсутствует открытый текст");
    }
    key = getValidKey(skey, text);
}


std::string modCipher::encryption(std::string& text) {
    std::string t = getValidOpenText(text);
    int symbols = t.length();
    int rows = (symbols + key - 1) / key;
    int cols = key;

    
    std::vector<std::vector<char>> table(rows, std::vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i * cols + j < symbols) {
                table[i][j] = t[i * cols + j];
            } else {
                table[i][j] = ' '; 
            }
        }
    }

    t.clear();
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (table[i][j] != ' ') {
                t += table[i][j];
            }
        }
    }
    return t;
}


inline std::string modCipher::getValidCipherText(std::string& s, std::string& open_text) {
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    if (s.length() != open_text.length()) {
        std::cerr << "Предупреждение: Длина зашифрованного текста не соответствует длине открытого текста" << std::endl;
    }
    return s;
}


std::string modCipher::transcript(std::string& text, std::string& open_text) {
    std::string t = getValidCipherText(text, open_text);
    int symbols = t.length();
    int rows = (symbols + key - 1) / key;
    int cols = key;

    std::vector<std::vector<char>> table(rows, std::vector<char>(cols));

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (j * rows + i < symbols) {
                table[i][j] = t[j * rows + i];
            } else {
                table[i][j] = ' ';
            }
        }
    }

    t.clear();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (table[i][j] != ' ') {
                t += table[i][j];
            }
        }
    }
    return t;
}


inline std::string modCipher::getValidOpenText(std::string& s) {
    if (s.empty()) {
        throw cipher_error("Отсутствует открытый текст");
    }
    s.erase(std::remove_if(s.begin(), s.end(), [](char c){ return !isalpha(c); }), s.end());
    return s;
}


inline int modCipher::getValidKey(int key, const std::string& Text) {
    if (key < 2 || key > static_cast<int>(Text.length())) {
        throw cipher_error("Ключ некорректного размера");
    }
    return key;
}
