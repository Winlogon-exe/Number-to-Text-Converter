#include <iostream>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <functional>

enum Constants : long long {
    Ten = 10,
    Twenty = 20,
    Hundred = 100,
    Thousand = 1000,
    Million = 1000000,
    Billion = 1000000000
};

struct Endings {
    std::array<std::string, 3> rubleEndings = { " рублей", " рубль", " рубля" };
    std::array<std::string, 3> thousandEndings = { " тысяч", " тысяча", " тысячи" };
    std::array<std::string, 3> millionEndings = { " миллионов", " миллион", " миллиона" };
    std::array<std::string, 3> billionEndings = { " миллиардов", " миллиард", " миллиарда" };
};

struct Numbers {
    std::array<std::string, 10> units = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    std::array<std::string, 10> unitsThousand = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    std::array<std::string, 10> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
    std::array<std::string, 10> tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
    std::array<std::string, 10> hundreds = { "", " сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот" };
};

std::string chooseEnding(long long number, const std::array<std::string, 3>& endings) {
    long long lastDigit = number % 10;
    long long penultimateDigit = (number / 10) % 10;

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

//еще функцию что ли добавлять для rubleEndings??

std::string convertNumberToWords(long long number, Numbers& numbers, Endings& endings)
{
    std::string handleError = "error";
    std::string result;

    const std::vector<std::pair<long long, std::array<std::string, 3>>> divisions = {
     { Billion, endings.billionEndings },
     { Million, endings.millionEndings },
     { Thousand, endings.thousandEndings }
    };

    for (const auto& division : divisions)
    {
        if (number >= division.first)
        {
            const long long divisionResult = number / division.first; // Вычисляем результат деления заранее

            if (division.first == Thousand && (divisionResult == 1 || divisionResult == 2))
                result += numbers.unitsThousand[divisionResult] + chooseEnding(divisionResult, division.second);
            else
                result += convertNumberToWords(divisionResult, numbers, endings) + chooseEnding(divisionResult, division.second);
            number %= division.first;
        }
    }

    if (number >= Hundred) 
    {
        result += numbers.hundreds[number / Hundred];
        number %= Hundred;
    }

    if (number >= Twenty)
    {
        result += numbers.tens[number / Ten];
        number %= Ten;
    }

    if (number >= Ten)
    {
        result += numbers.teens[number - Ten];
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
            std::cout << "Введите корректное число." << std::endl;
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
        std::string result = convertNumberToWords(getInput, numbers, endings) + chooseEnding(getInput, endings.rubleEndings);
        std::cout << result << std::endl;
    }

    return 0;
}
