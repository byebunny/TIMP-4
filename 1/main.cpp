#include "modAlphaCipher.h"
#include <iostream>
#include <string>

void check(const std::string& Text, const std::string& key) {
    try {
        modAlphaCipher cipher(key); 
        std::string cipherText = cipher.encrypt(Text); 
        std::string decryptedText = cipher.decrypt(cipherText); 
        std::cout << "Исходный текст: " << Text << std::endl;
        std::cout << "Зашифрованный текст: " << cipherText << std::endl;
        std::cout << "Расшифрованный текст: " << decryptedText << std::endl;
        std::cout << "Ключ: " << key << std::endl;
        
        if (Text == decryptedText) {
            std::cout << "Ok" << std::endl;
        } else {
            std::cout << "Err" << std::endl;
        }
    } catch (const cipher_error& e) {
        
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    
    check("НОВЫЙГОД", "СКОРО");
    check("НОВЫЙГОД", "скоро");
    check("НОВЫЙГОД", "!СКОРО!");
    check("НОВЫЙГОД", "4657890");
    check("456738290", "NO");
    check("НОВЫЙГОД", "");
    check("45678390", "СКОРО");
    check("", "СКОРО");
    return 0;
}


