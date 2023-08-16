#include <string>
#include<array>
#include<iostream>
#include <unordered_map>

const long long Ten = 10;
const long long Twenty = 20;
const long long Hundred = 100;
const long long Thousand = 1000;
const long long Million = 1000000;
const long long Billion = 1000000000;

//Окончание
std::string rubleEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    const std::string Rubles = " рублей";
    const std::string Ruble = " рубль";
    const std::string Rublia = " рубля";

    if (penultimateDigit == 1) {
        return Rubles;
    }
    else if (lastDigit == 1) {
        return Ruble;
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return Rublia;
    }
    else {
        return Rubles;
    }
}

std::string thousandEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    const std::string Thousands = " тысяч";
    const std::string Thousand = " тысяча";
    const std::string Tysiachi = " тысячи";

    if (penultimateDigit == 1) {
        return Thousands;
    }
    else if (lastDigit == 1) {
        return Thousand;
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return Tysiachi;
    }
    else {
        return Thousands;
    }
}

std::string millionEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    const std::string Millions = " миллионов";
    const std::string Million = " миллион";
    const std::string Milliona = " миллиона";

    if (penultimateDigit == 1) {
        return Millions;
    }
    else if (lastDigit == 1) {
        return Million;
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return Milliona;
    }
    else {
        return Millions;
    }
}

std::string billionEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    const std::string Billions = " миллиардов";
    const std::string Billion = " миллиард";
    const std::string Billiona = " миллиарда";

    if (penultimateDigit == 1) {
        return Billions;
    }
    else if (lastDigit == 1) {
        return Billion;
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return Billiona;
    }
    else {
        return Billions;
    }
}

//Data
struct Data {
    std::array<std::string, 10> ones;
    std::array<std::string, 10> onesThousand;
    std::array<std::string, 10> teens;
    std::array<std::string, 10> tens;
    std::array<std::string, 10> hundredth;

    std::unordered_map<long long, std::string> cachedResults;

    Data() {
        ones = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
        onesThousand = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
        teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
        tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
        hundredth = { "", " сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот" };
    }
};

//Склонение
std::string nameForNumber(long long number, bool isThousand, Data& massive) {
    if (massive.cachedResults.find(number) != massive.cachedResults.end()) {
        return massive.cachedResults[number];
    }

    std::string handleError = "error";
    std::string result;

    if (number < Ten)
        result = massive.ones[number];
    else if (number < Twenty)
        result = massive.teens[number - Ten];
    else if (number < Hundred)
        result = massive.tens[number / Ten] + nameForNumber(number % Ten, isThousand, massive);
    else if (number < Thousand)
        result = massive.hundredth[number / Hundred] + nameForNumber(number % Hundred, isThousand, massive);
    else if (number < Million)
        result = nameForNumber(number / Thousand, isThousand, massive) + thousandEnding(number / Thousand) + nameForNumber(number % Thousand, isThousand, massive);
    else if (number < Billion)
        result = nameForNumber(number / Million, isThousand, massive) + millionEnding(number / Million) + nameForNumber(number % Million, isThousand, massive);
    else
        result = handleError;

    massive.cachedResults[number] = result; // Cache the result before returning
    return result;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    Data massive;
    long long input;
    do
    {
        std::cout << "Enter a number: ";
        std::cin >> input;

        // Проверяем ввод
        if (std::cin.fail()) {
            std::cin.clear(); // сбрасываем состояние потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем "плохой" ввод
            std::cout << "Please enter a valid number." << std::endl;
            continue;
        }

        if (input < 0) {
            std::cout << "минус";
            input = -input;
        }
        else if (input == 0)
        {
            std::cout << "Ноль ";
        }
        std::cout << nameForNumber(input, false, massive) + " " + rubleEnding(input % Thousand) << "\n\n";
    } while (true);
    return 0;
}
