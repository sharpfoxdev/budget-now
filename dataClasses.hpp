#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

namespace dataNS{
    struct Expense{
        float amount;
        string comment;
    };
    struct Category{
        string name;
        float budgeted;
        vector<Expense> expenses;
    };
    struct Budget{

    };
}

#endif