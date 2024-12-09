/** @file
 * @author Маматкулова Р.А.
 * @version 1.0
 * @date 03.12.2024
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля маршрутной перестановки
 */

#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

/**
 * @brief Исключение, которое выбрасывается при ошибках в работе с шифром.
 */
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};

/**
 * @brief Класс modCipher реализует шифр транспозиции столбцов.
 */
class modCipher {
private:
    int key; ///< Ключ шифрования (количество столбцов).

    /**
     * @brief Проверяет ключ на корректность.
     * @param key Ключ (целое число).
     * @param Text Текст (строка) - для проверки размера ключа относительно текста.
     * @return Проверенный ключ (целое число).
     * @throws cipher_error Если ключ меньше 2 или больше длины текста.
     */
    int getValidKey(int key, const std::string& Text);

    /**
     * @brief Проверяет открытый текст на корректность и удаляет пробелы.
     * @param s Открытый текст (строка).
     * @return Проверенный открытый текст (строка) без пробелов.
     * @throws cipher_error Если текст пустой или содержит некорректные символы.
     */
    std::string getValidOpenText(std::string& s);

    /**
     * @brief Проверяет зашифрованный текст и исходный текст на соответствие длины, удаляет пробелы.
     * @param s Зашифрованный текст (строка).
     * @param open_text Исходный текст (строка).
     * @return Зашифрованный текст (строка) без пробелов.
     * @throws cipher_error Если текст пустой или содержит некорректные символы.
     */
    std::string getValidCipherText(std::string& s, std::string& open_text);

public:
    modCipher() = delete; ///< Запрещает создание объекта без параметров.

    /**
     * @brief Конструктор класса modCipher.
     * @param skey Ключ шифрования (целое число).
     * @param text Исходный текст (строка).
     * @throws cipher_error Если текст пустой или ключ некорректный.
     */
    modCipher(int skey, std::string text);

    /**
     * @brief Шифрует текст методом транспозиции столбцов.
     * @param text Текст для шифрования (строка).
     * @return Зашифрованный текст (строка).
     */
    std::string encryption(std::string& text);

    /**
     * @brief Расшифровывает текст методом транспозиции столбцов.
     * @param text Зашифрованный текст (строка).
     * @param open_text Исходный текст (строка) - для проверки.
     * @return Расшифрованный текст (строка).
     */
    std::string transcript(std::string& text, std::string& open_text);
};

#endif

