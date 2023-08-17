#include <iostream>
#include <unordered_map>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <functional>

struct Constants {
    static const long long Ten = 10;
    static const long long Twenty = 20;
    static const long long Hundred = 100;
    static const long long Thousand = 1000;
    static const long long Million = 1000000;
    static const long long Billion = 1000000000;
};

struct Endings {
    const std::vector<std::string> rubleEndings = { " рублей", " рубль", " рубля" };
    const std::vector<std::string> thousandEndings = { " тысяч", " тысяча", " тысячи" };
    const std::vector<std::string> millionEndings = { " миллионов", " миллион", " миллиона" };
    const std::vector<std::string> billionEndings = { " миллиардов", " миллиард", " миллиарда" };
};

struct Numbers {
    const std::array<std::string, 10> units = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    const std::array<std::string, 10> unitsThousand = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    const std::array<std::string, 10> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
    const std::array<std::string, 10> tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
    const std::array<std::string, 10> hundreds = { "", " сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот" };
};

std::string chooseEnding(const int number, const std::vector<std::string>& endings) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {
        return endings[0];
    }
    else if (lastDigit == 1) {
        return endings[1];
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return endings[2];
    }
    else {
        return endings[0];
    }
}

std::string convertNumberToWords(long long number, Numbers& numbers, Endings& endings)
{
    std::string handleError = "error";
    std::string result;

    const std::vector<std::pair<long long, std::vector<std::string>>> divisions = {
     { Constants::Billion, endings.billionEndings },
     { Constants::Million, endings.millionEndings },
     { Constants::Thousand, endings.thousandEndings }
    };

    for (const auto& division : divisions)
    {
        if (number >= division.first)
        {
            long long divisionResult = number / division.first; // Вычисляем результат деления заранее

            if (division.first == Constants::Thousand && (divisionResult == 1 || divisionResult == 2))
                result += numbers.unitsThousand[divisionResult] + chooseEnding(divisionResult, division.second);
            else
                result += convertNumberToWords(divisionResult, numbers, endings) + chooseEnding(divisionResult, division.second);
            number %= division.first;
        }
    }

    if (number >= Constants::Hundred)
    {
        result += numbers.hundreds[number / Constants::Hundred];
        number %= Constants::Hundred;
    }

    if (number >= Constants::Twenty)
    {
        result += numbers.tens[number / Constants::Ten];
        number %= Constants::Ten;
    }

    if (number >= Constants::Ten)
    {
        result += numbers.teens[number - Constants::Ten];
    }
    else if (number > 0)
    {
        result += numbers.units[number];
    }

    return result.empty() ? handleError : result;
}

long long getPositiveNumberInput() {
    long long input;
    do
    {
        std::cout << "Введите число: ";
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Пожалуйста, введите корректное число." << std::endl;
            continue;
        }

        if (input < 0) {
            std::cout << "минус ";
            input = -input;
        }
        else if (input == 0)
        {
            std::cout << "Ноль ";
        }
        return input;
    } while (true);
}

int main()
{
    setlocale(LC_ALL, "RUS");

    Numbers numbers;
    Endings endings;

    while (true)
    {
        long long getInput = getPositiveNumberInput();
        std::string result = convertNumberToWords(getInput, numbers, endings); 
        std::cout << result << std::endl;
    }

    return 0;
}
