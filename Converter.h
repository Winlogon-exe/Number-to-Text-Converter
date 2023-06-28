#include<iostream>
#include <string> 
#include<array>

struct Data;
std::string nameForNumber(long long number, bool isThousand, Data& massive);
std::string thousandEnding(int number);
std::string millionEnding(int number);
std::string billionEnding(int number);
std::string rubleEnding(int number);