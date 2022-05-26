#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include "model.hpp"
#include "view.hpp"

using namespace std;

class IController{
public: 
	virtual ~IController() = default;
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) = 0;
};

class BudgetController final : public IController 
{
private:
    Model & model;
    enum class Action { List, Add, Copy, SetPrimary, Info };
	map<string, Action> actionMap;
public:
    BudgetController(Model & model) : model(model){
        actionMap = {
            { "list", Action::List},
            { "add_budget", Action::Add},
            { "copy_budget", Action::Copy},
            { "set_primary", Action::SetPrimary},
            { "info_budget", Action::Info}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

class ExpenseController final : public IController 
{
private:
    Model & model;
    enum class Action { Add };
	map<string, Action> actionMap;
public:
    ExpenseController(Model & model) : model(model){
        actionMap = {
            { "expense", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

class CategoryController final : public IController 
{
private:
    Model & model;
    enum class Action { Add, Info };
	map<string, Action> actionMap;
public:
    CategoryController(Model & model) : model(model){
        actionMap = {
            { "info_category", Action::Info},
            { "add_category", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

class IncomeController final : public IController 
{
private:
    Model & model;
    enum class Action { Add };
    map<string, Action> actionMap;
public:
    IncomeController(Model & model) : model(model){
        actionMap = {
            { "add_income", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

class HelpController final : public IController 
{
private:
    Model & model;
    enum class Action { Help };
    map<string, Action> actionMap;
public:
    HelpController(Model & model) : model(model){
        actionMap = {
            { "--help", Action::Help}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

/**
 * @brief Calls Model to get/set data and then calls View to show them to the user on CLI
 */
// class Controller{
// public: 
//     void ListAllBudgets();
//     void CopyBudget(const vector<string> & params);
//     void AddBudget(const vector<string> & params);
//     void AddExpense(const vector<string> & params);
//     void AddCategory(const vector<string> & params);
//     void AddIncome(const vector<string> & params);
//     void SetPrimaryBudget(const vector<string> & params);
//     void PrintBudgetInfo(const vector<string> & params);
//     void PrintCategoryInfo(const vector<string> & params);
//     void PrintHelp();
// private:
//     View view;
//     Model model;
// };

#endif