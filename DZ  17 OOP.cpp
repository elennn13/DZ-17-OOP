#include <iostream>
#include <exception>
#include <random>
#include <sstream>
#include <string>


class RangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Неверный диапазон: значение N больше или равно значению M";
    }
};

int getRandomNumber(int N, int M) {
    if (N >= M) {
        throw RangeException();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(N, M - 1);

    return dis(gen);
}



class FormatException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Неверный формат строки";
    }
};

bool checkWordLength(const std::string& input) {
    std::istringstream iss(input);
    std::string word;
    int length;

    iss >> word >> length;

    if (iss.fail() || iss.peek() != std::char_traits<char>::eof()) {
        throw FormatException();
    }

    return word.length() == length;
}




int main() {
    setlocale(LC_ALL, "ru");

    try {
        int N = 10, M = 20;
        int randomNumber = getRandomNumber(N, M);
        std::cout << "Случайное число в диапазоне [" << N << ", " << M << "): " << randomNumber << std::endl;

        N = 20, M = 10;
        randomNumber = getRandomNumber(N, M);
    }
    catch (const RangeException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;

    try {
        std::string input1 = "hello 5";
        std::string input2 = "world 10";
        std::string input3 = "hello world";

        std::cout << "'" << input1 << "' - " << std::boolalpha << checkWordLength(input1) << std::endl;
        std::cout << "'" << input2 << "' - " << std::boolalpha << checkWordLength(input2) << std::endl;
        std::cout << "'" << input3 << "' - " << std::boolalpha << checkWordLength(input3) << std::endl;
    }
    catch (const FormatException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}