#include<iostream>
#include <string> 
#include<array>
using namespace std;

std::string nameForNumber(long long number, bool isThousand = false);
std::string thousandEnding(int number);
std::string millionEnding(int number);
std::string billionEnding(int number);
std::string rubleEnding(int number);

//Окончание
std::string rubleEnding(int number) {
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

std::string thousandEnding(int number) {
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

std::string millionEnding(int number) {
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

std::string billionEnding(int number) {
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

//Склонение
std::string nameForNumber(long long number, bool isThousand) {

    static const std::array<string, 10> ones = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    static const std::array<string, 10> onesThousand = { "", " одна", " две", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    static const std::array<string, 10> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
    static const std::array<string, 10> tens = { "", "", " двадцать", " тридцать", "сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
    static const std::array<string, 10> hundredth = { ""," сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот", };

    //единицы
    if (number < 10) return isThousand ? onesThousand[number] : ones[number];
    //числительные
    else if (number < 20)  return teens[number - 10];
    //десятки
    else if (number < 100) return tens[number / 10] + nameForNumber(number % 10, isThousand);
    //сотни
    else if (number < 1000) return hundredth[number / 100] + nameForNumber(number % 100, isThousand);
    //тысячи
    else if (number < 1000000) return nameForNumber(number / 1000, true) + thousandEnding(number / 1000) + nameForNumber(number % 1000);
    //миллионы
    else if (number < 1000000000)  return nameForNumber(number / 1000000) + millionEnding(number / 1000000) + nameForNumber(number % 1000000);
    //миллиарды 
    else if (number < 1000000000000) return nameForNumber(number / 1000000000) + billionEnding(number / 1000000000) + nameForNumber(number % 1000000000);
    return "error";
}

int main()
{
    setlocale(LC_ALL, "RUS");
    long long input;
    do
    {
        cout << "Enter a number: ";
        cin >> input;

        // Проверяем ввод
        if (cin.fail()) {
            cin.clear(); // сбрасываем состояние потока
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорируем "плохой" ввод
            cout << "Please enter a valid number." << endl;
            continue;
        }

        if (input < 0) {
            cout << "минус";
            input = -input;
        }
        else if (input == 0)
        {
            cout << "Ноль ";
        }
        cout << nameForNumber(input) + " " + rubleEnding(input % 1000) << "\n\n";
    } while (true);
    return 0;
}
