#ifndef DATE_MANAGER_H
#define DATE_MANAGER_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "date.h"

using namespace std::chrono;
using namespace std;
using namespace date;

class DateManager{
public:
    static string GetSpendingSpeedString(const dataNS::DateStruct & startDate, const dataNS::DateStruct & endDate, const dataNS::DateStruct & expenseDate, const dataNS::Category & category);
    static dataNS::DateStruct ParseDate(const string & date);
    static dataNS::DateStruct GetTodaysDate();
    static bool DateInBetweenOtherDates(const dataNS::DateStruct & firstDate, const dataNS::DateStruct & inBetweenDate, const dataNS::DateStruct & lastDate);
};

#endif