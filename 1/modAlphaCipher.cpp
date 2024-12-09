#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>
#include <vector>
#include <stdexcept>
#include <algorithm> 

std::locale loc("ru_RU.UTF-8");
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;

modAlphaCipher::modAlphaCipher(const std::string& skey) {
   
    for (size_t i = 0; i < numAlpha.size(); ++i) {
        alphaNum[numAlpha[i]] = i;
    }
   
    key = convert(getValidKey(skey));
}

std::string modAlphaCipher::encrypt(const std::string& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    
    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    
    return convert(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text) {
    
    std::vector<int> work = convert(getValidCipherText(cipher_text));
  
    for (size_t i = 0; i < work.size(); ++i) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    
    return convert(work);
}


inline std::vector<int> modAlphaCipher::convert(const std::string& s) {
    std::vector<int> result;
    std::wstring ws = codec.from_bytes(s); 
    for (wchar_t c : ws) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

inline std::string modAlphaCipher::convert(const std::vector<int>& v) {
    std::string result;
    std::wstring ws;
    for (int i : v) {
        ws.push_back(numAlpha[i]);
    }
    result = codec.to_bytes(ws);
    return result;
}


inline std::string modAlphaCipher::getValidKey(const std::string& s) {
    std::string result;
    std::wstring ws = codec.from_bytes(s);
    if (ws.empty()) {
        throw cipher_error("Пустой ключ");
    }
    std::wstring tmp(ws);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [&](wchar_t c) {
        if (!std::iswalpha(c, loc)) {
            throw cipher_error("Недействительный ключ: недопустимый символ");
        }
        return std::towupper(c, loc);
    });
    result = codec.to_bytes(tmp);
    return result;
}


inline std::string modAlphaCipher::getValidOpenText(const std::string& s) {
    std::string result;
    std::wstring tmp;
    std::wstring ws = codec.from_bytes(s);
    for (wchar_t c : ws) {
        if (std::iswalpha(c, loc)) {
            tmp.push_back(std::towupper(c, loc));
        }
    }
    if (tmp.empty()) {
        throw cipher_error("Пустой открытый текст");
    }
    result = codec.to_bytes(tmp);
    return result;
}


inline std::string modAlphaCipher::getValidCipherText(const std::string& s) {
    std::string result;
    std::wstring ws = codec.from_bytes(s);
    if (ws.empty()) {
        throw cipher_error("Пустой зашифрованный текст");
    }
    for (wchar_t c : ws) {
        if (!std::iswupper(c, loc)) {
            throw cipher_error("Недопустимый зашифрованный текст: строчные буквы");
        }
    }
    result = codec.to_bytes(ws);
    return result;
}
