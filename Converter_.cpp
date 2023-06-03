#include<iostream>
#include<vector>
#include <string> 
using namespace std;
std::string nameForNumber(long long number);
std::string thousandEnding(int number);
std::string millionEnding(int number);
std::string billionEnding(int number);
std::string rubleEnding(int number);


/*пример самый наглядный будет:
* Рассмотрим случай, когда number равно 21.Здесь number / 10 это 2, так что tens[number / 10] это "двадцать".
* Далее number % 10 это 1, так что convert(number % 10) это "один".
* Тогда конечная строка будет "двадцать один"
* И так со всем числами
*/

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
    //берем 2 последних числа
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
// склонения  доделать - "одна"  и "две"
std::string nameForNumber(long long number) {

    static const std::vector<std::string> ones = { "", " один", " два", " три", " четыре", " пять", " шесть", " семь", " восемь", " девять" };
    static const std::vector<std::string> teens = { " десять", " одиннадцать", " двенадцать", " тринадцать", " четырнадцать", " пятнадцать", " шестнадцать", " семнадцать", " восемнадцать", " девятнадцать" };
    static const std::vector<std::string> tens = { "", "", " двадцать", " тридцать", " сорок", " пятьдесят", " шестьдесят", " семьдесят", " восемьдесят", " девяносто" };
    static const std::vector<std::string> hundredth = { ""," сто", " двести", " триста", " четыреста", " пятьсот", " шестьсот", " семьсот", " восемьсот", " девятьсот", };

    //единицы
    if (number < 10 ) {
        return ones[number];
    }
    //числительные
    else if (number < 20) {
        return teens[number - 10];
    }
    //десятки
    else if (number < 100) {
        return tens[number / 10] + nameForNumber(number % 10);
    }
    //сотни
    else if (number < 1000) {
        return hundredth[number / 100] + nameForNumber(number % 100);
    }
    //тысячи
    else if (number < 1000000) {
        return nameForNumber(number / 1000) + thousandEnding(number / 1000) + nameForNumber(number % 1000);
    }
    //миллионы
    else if (number < 1000000000) {
        return nameForNumber(number / 1000000) + millionEnding (number/ 1000000) + nameForNumber(number % 1000000);
    }
    //миллиарды 
    else if (number < 1000000000000) {
        return nameForNumber(number / 1000000000) + billionEnding(number/ 1000000000) + nameForNumber(number % 1000000000);
    }
    return "error";
}


int main()
{
    setlocale(LC_ALL, "RUS");
    long long input;
    do
    {
        cout << "Enter a positive integer: ";
        cin >> input;
        cout << "\n" <<  nameForNumber(input) + rubleEnding(input) << endl;
        cout << "\n\n" << endl;
    } while (input > 0);
    return 0;
}
