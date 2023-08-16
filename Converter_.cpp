#include <iostream>
#include <unordered_map>
#include <limits>
#include <string>
#include <array>
#include <vector>

 struct Constants {
    static const long long Ten = 10;
    static const long long Twenty = 20;
    static const long long Hundred = 100;
    static const long long Thousand = 1000;
    static const long long Million = 1000000;
    static const long long Billion = 1000000000;
};

struct Endings {
    std::vector<std::string> rubleEndings = { " рублей", " рубль", " рубля" };
    std::vector<std::string> thousandEndings = { " тысяч", " тысяча", " тысячи" };
    std::vector<std::string> millionEndings = { " миллионов", " миллион", " миллиона" };
    std::vector<std::string> billionEndings = { " миллиардов", " миллиард", " миллиарда" };
};

 struct Numbers {
    const std::array<std::string, 10> ones = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    const std::array<std::string, 10> onesThousand = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    const std::array<std::string, 10> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
    const std::array<std::string, 10> tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
    const std::array<std::string, 10> hundredth = { "", " сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот" };
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

    while (number >= Constants::Billion)
    {
        if (number >= Constants::Billion)
        {
            result += convertNumberToWords(number / Constants::Billion, numbers, endings) + chooseEnding(number / Constants::Billion, endings.billionEndings);
            number %= Constants::Billion;
        }
    }

    while (number >= Constants::Million)
    {
        if (number >= Constants::Million)
        {
            result += convertNumberToWords(number / Constants::Million, numbers, endings) + chooseEnding(number / Constants::Million, endings.millionEndings);
            number %= Constants::Million;
        }
    }

    while (number >= Constants::Thousand)
    {
        if (number >= Constants::Thousand)
        {
            if (number / Constants::Thousand == 1 || number / Constants::Thousand == 2)
                result += numbers.onesThousand[number / Constants::Thousand] + chooseEnding(number / Constants::Thousand, endings.thousandEndings);
            else
                result += convertNumberToWords(number / Constants::Thousand, numbers, endings) + chooseEnding(number / Constants::Thousand, endings.thousandEndings);
            number %= Constants::Thousand;
        }
    }

    if (number >= Constants::Hundred)
    {
        result += numbers.hundredth[number / Constants::Hundred];
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
        result += numbers.ones[number];
    }

    return result.empty() ? handleError : result;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    Endings endings; 
    Numbers numbers; 
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
        std::cout << convertNumberToWords(input,numbers, endings) + " " + chooseEnding(input % Constants::Thousand, endings.rubleEndings) << "\n\n";
    } while (true);
    return 0;
}
