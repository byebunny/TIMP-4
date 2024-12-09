/** @file
 * @author Маматкулова Р.А.
 * @version 1.0
 * @date 03.12.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля Гронсфельда
 */
#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <map>
#include <algorithm> 
/**
 * @brief  Исключение, возникающее при ошибках шифрования/расшифрования.
 */
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

/**
 * @brief Класс modAlphaCipher реализует шифр простой замены (подстановка).
 */
class modAlphaCipher {
private:
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Русский алфавит для шифрования.
    std::map<wchar_t, int> alphaNum;  ///< Ассоциативный массив для быстрого поиска номера буквы по символу.
    std::vector<int> key;             ///< Ключ шифрования, представленный как вектор целых чисел.

    /**
     * @brief Преобразует строку в вектор целых чисел, представляющих номера букв в алфавите.
     * @param s Строка для преобразования.
     * @return Вектор целых чисел.
     */
    std::vector<int> convert(const std::string& s);

    /**
     * @brief Преобразует вектор целых чисел в строку.
     * @param v Вектор целых чисел, представляющих номера букв.
     * @return Строка.
     */
    std::string convert(const std::vector<int>& v);

    /**
     * @brief Проверяет ключ на корректность и преобразует его в верхний регистр.
     * @param s Ключ (строка).
     * @return Проверенный и преобразованный ключ (строка).
     * @throws cipher_error Если ключ пустой или содержит недопустимые символы.
     */
    std::string getValidKey(const std::string& s);

    /**
     * @brief Проверяет открытый текст на корректность и преобразует его в верхний регистр.
     * @param s Открытый текст (строка).
     * @return Проверенный и преобразованный открытый текст (строка).
     * @throws cipher_error Если открытый текст пустой или содержит недопустимые символы.
     */
    std::string getValidOpenText(const std::string& s);

    /**
     * @brief Проверяет зашифрованный текст на корректность.
     * @param s Зашифрованный текст (строка).
     * @return Проверенный зашифрованный текст (строка).
     * @throws cipher_error Если зашифрованный текст пустой или содержит недопустимые символы.
     */
    std::string getValidCipherText(const std::string& s);

public:
    modAlphaCipher() = delete;  ///< Запрещаем создание объекта без ключа.

    /**
     * @brief Конструктор класса modAlphaCipher.
     * @param skey Ключ шифрования (строка).
     * @throws cipher_error Если ключ некорректный.
     */
    modAlphaCipher(const std::string& skey);

    /**
     * @brief Шифрует открытый текст.
     * @param open_text Открытый текст (строка).
     * @return Зашифрованный текст (строка).
     * @throws cipher_error При ошибках обработки текста.
     */
    std::string encrypt(const std::string& open_text);

    /**
     * @brief Расшифровывает зашифрованный текст.
     * @param cipher_text Зашифрованный текст (строка).
     * @return Расшифрованный текст (строка).
     * @throws cipher_error При ошибках обработки текста.
     */
    std::string decrypt(const std::string& cipher_text);
};

#endif
