#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "json.hpp"
#include "date.h"

using json = nlohmann::json;
using namespace std;

/**
 * @brief Namespace holding structures that hold programs data.
 * This namespace also define functions to convert data from and to json, for
 * this reason they are encapsulated in this namespace to not colide with names
 * in json.hpp library. 
 */
namespace dataNS{
    /**
     * @brief Structure that holds dates (day, month, year)
     */
    struct DateStruct{
        unsigned int day;
        unsigned int month;
        int year;
        /**
         * @brief Compare two dates
         * @param other right operand
         * @return true if left operand is less or equal to the right operand
         * @return false otherwise
         */
        bool operator<=(const DateStruct& other) const
        {
            auto ymdLeft = date::year{this->year}/this->month/this->day;
            auto ymdRight = date::year{other.year}/other.month/other.day;
            if(!ymdLeft.ok() || !ymdLeft.ok()){
                throw std::invalid_argument("compare error");
            }
            return ((ymdLeft < ymdRight) || (ymdLeft == ymdRight)); 
        }
        /**
         * @brief Converts DateStruct to string, used for printing
         * @return string of date in dd.mm.yyy format
         */
        string ToString() const{
            stringstream strs;
            strs << this->day << "." << this->month << "." << this->year;
            string stri;
            strs >> stri;
            return stri;
        }
    };
    /**
     * @brief Expense structure
     */
    struct Expense{
        double amount;
        string comment;
        DateStruct date;
    };
    /**
     * @brief Income structure
     */
    struct Income{
        double amount;
        string comment;
    };
    /**
     * @brief Category in budget structure holding its expenses
     */
    struct Category{
        double budgeted;
        vector<Expense> expenses;
    };
    /**
     * @brief Budget structure holding its categories and incomes
     */
    struct Budget{
        vector<Income> incomes;
        map<string, Category> categories;
        DateStruct start;
        DateStruct end;
    };
    /**
     * @brief Structure holding all budgets.
     * Also holding primary budget separately from others for simpler access. 
     */
    struct BudgetsHolder{
        string primaryBudgetName;
        Budget primaryBudget;
        map<string, Budget> otherBudgets;
    };

}

#endif