#include <iostream>
#include <string>
#include "modAlphaCipher.h"

void check(std::string Text, int key) {
    try {
        std::string cipherText;
        std::string decryptedText;
       
        modCipher cipher(key, Text); 
       
        cipherText = cipher.encryption(Text); 
        
        decryptedText = cipher.transcript(cipherText, Text); 
        
        std::cout << "Ключ = " << key << std::endl;
        std::cout << "Исходный текст: " << Text << std::endl;
        std::cout << "Зашифрованный текст: " << cipherText << std::endl;
        std::cout << "Расшифрованный текст: " << decryptedText << std::endl;
    } catch (const cipher_error& e) {
        
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}


int main() {
    try {
       
        check("NEWYEAR", 3);
        check("NEWYEAR", 2025);
        check("2025", 3);
        check("", 2025); 
    } catch (const cipher_error& e) {
        
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}

