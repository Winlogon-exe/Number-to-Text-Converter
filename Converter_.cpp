#include"Converter.h"

//Окончание
std::string rubleEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {  // Для чисел 10-19 всегда "рублей"
        return " рублей";
    }
    else if (lastDigit == 1) {  // Для чисел, оканчивающихся на 1 (кроме 11), "рубль"
        return " рубль";
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {  // Для чисел, оканчивающихся на 2-4 (кроме 12-14), "рубля"
        return " рубля";
    }
    else {  // Во всех остальных случаях "рублей"
        return " рублей";
    }
}
std::string thousandEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {  // Для чисел 10-19 всегда "тысяч"
        return " тысяч";
    }
    else if (lastDigit == 1) {  // Для чисел, оканчивающихся на 1 (кроме 11), "тысяча"
        return " тысяча";
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {  // Для чисел, оканчивающихся на 2-4 (кроме 12-14), "тысячи"
        return " тысячи";
    }
    else {  // Во всех остальных случаях "тысяч"
        return " тысяч";
    }
}
std::string millionEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {
        return " миллионов";
    }
    else if (lastDigit == 1) {
        return " миллион";
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return " миллиона";
    }
    else {
        return " миллионов";
    }
}
std::string billionEnding(const int number) {
    int lastDigit = number % 10;
    int penultimateDigit = (number / 10) % 10;

    if (penultimateDigit == 1) {
        return " миллиардов";
    }
    else if (lastDigit == 1) {
        return " миллиард";
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return " миллиарда";
    }
    else {
        return " миллиардов";
    }
}

//Data
struct Data {  
     std::array<std::string, 10> ones; 
     std::array<std::string, 10> onesThousand; 
     std::array<std::string, 10> teens; 
     std::array<std::string, 10> tens; 
     std::array<std::string, 10> hundredth; 

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

    // единицы
    if (number < 10) return massive.ones[number];
    // десятки
    else if (number < 20)  return massive.teens[number - 10];
    // десятки
    else if (number < 100) return massive.tens[number / 10] + nameForNumber(number % 10, isThousand, massive);
    // сотни
    else if (number < 1000) return massive.hundredth[number / 100] + nameForNumber(number % 100, isThousand, massive); 
    // тысячи
    else if (number < 1000000) return nameForNumber(number / 1000, isThousand, massive) + thousandEnding(number / 1000) + nameForNumber(number % 1000, isThousand, massive); 
    // миллионы
    else if (number < 1000000000)  return nameForNumber(number / 1000000, isThousand, massive) + millionEnding(number / 1000000) + nameForNumber(number % 1000000, isThousand, massive); 
    // миллиарды
    else if (number < 1000000000000) return nameForNumber(number / 1000000000, isThousand, massive) + billionEnding(number / 1000000000) + nameForNumber(number % 1000000000, isThousand, massive); 

    return "error";
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
        std::cout << nameForNumber(input, false, massive) + " " + rubleEnding(input % 1000) << "\n\n";
    } while (true);
    return 0;
}
