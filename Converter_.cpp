#include <iostream>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <functional>

struct Constants {
    static constexpr long long Ten = 10;
    static constexpr long long Twenty = 20;
    static constexpr long long Hundred = 100;
    static constexpr long long Thousand = 1000;
    static constexpr long long Million = 1000000;
    static constexpr long long Billion = 1000000000;
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

std::string convertNumberToWords(long long number, Numbers& numbers, Endings& endings)
{
    std::string handleError = "error";
    std::string result;

    const std::vector<std::pair<long long, std::array<std::string, 3>>> divisions = {
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
                result += std::string(numbers.unitsThousand[divisionResult]) + std::string(chooseEnding(divisionResult, division.second));
            else
                result += convertNumberToWords(divisionResult, numbers, endings) + std::string(chooseEnding(divisionResult, division.second));
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

    result += std::string(chooseEnding(number, endings.rubleEndings)); // Добавление "рублей"

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
        std::string result = convertNumberToWords(getPositiveNumberInput(), numbers, endings);
        std::cout << result << std::endl;
    }

    return 0;
}
