#ifndef MODEL_H
#define MODEL_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "json.hpp"
#include "date.h"
#include "dateManager.hpp"


using json = nlohmann::json;
using namespace std;
using namespace std::chrono;
using namespace date;

class IModel{
public: 
    virtual ~IModel() = default;
    virtual dataNS::BudgetsHolder GetBudgetsHolder() = 0;
    virtual bool CopyBudget(const vector<string> & params) = 0;
    virtual bool SetPrimaryBudget(const vector<string> & params) = 0;
    virtual bool AddBudget(const vector<string> & params) = 0;
    virtual bool AddExpense(const vector<string> & params) = 0;
    virtual bool AddCategory(const vector<string> & params) = 0;
    virtual bool AddIncome(const vector<string> & params) = 0;
    virtual dataNS::Budget GetBudget(const vector<string> & params) = 0;
    virtual dataNS::Category GetCategory(const vector<string> & params) = 0;
    virtual string GetMessage() = 0;

};

class Model final : public IModel{
public:
    Model(string jsonFile) : jsonFile(jsonFile) {}
    dataNS::BudgetsHolder GetBudgetsHolder();
    bool CopyBudget(const vector<string> & params);
    bool SetPrimaryBudget(const vector<string> & params);
    bool AddBudget(const vector<string> & params);
    bool AddExpense(const vector<string> & params);
    bool AddCategory(const vector<string> & params);
    bool AddIncome(const vector<string> & params);
    dataNS::Budget GetBudget(const vector<string> & params);
    dataNS::Category GetCategory(const vector<string> & params);
    string GetMessage();
private:
    stringstream message;
    void SaveBudgetsHolder(dataNS::BudgetsHolder bh);
    string jsonFile;
    void MessageIncorrectNumberOfParams();
    void MessageIncorrectParamType();
    void MessageUsedName();
    void MessageNoPrimaryBudget();
};

#endif