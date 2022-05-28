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

/**
 * @brief Interface for controller
 */
class IController{
public: 
	virtual ~IController() = default;
    /**
     * @brief Updates/retrieves data from Model based on command and returns view, that can display result
     * @param command command
     * @param params parameters of command
     * @return unique_ptr<IView> view that can display result
     */
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) = 0;
};

/**
 * @brief Implementation of IController interface, handles budget related commands
 */
class BudgetController final : public IController 
{
private:
    shared_ptr<IModel> model;
    enum class Action { List, Add, Copy, SetPrimary, Info };
	map<string, Action> actionMap;
public:
    BudgetController(shared_ptr<IModel> model) : model(model){
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

/**
 * @brief Implementation of IController interface, handles expense related commands
 */
class ExpenseController final : public IController 
{
private:
    shared_ptr<IModel> model;
    enum class Action { Add };
	map<string, Action> actionMap;
public:
    ExpenseController(shared_ptr<IModel> model) : model(model){
        actionMap = {
            { "expense", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

/**
 * @brief Implementation of IController interface, handles category related commands
 */
class CategoryController final : public IController 
{
private:
    shared_ptr<IModel> model;
    enum class Action { Add, Info };
	map<string, Action> actionMap;
public:
    CategoryController(shared_ptr<IModel> model) : model(model){
        actionMap = {
            { "info_category", Action::Info},
            { "add_category", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

/**
 * @brief Implementation of IController interface, income budget related commands
 */
class IncomeController final : public IController 
{
private:
    shared_ptr<IModel> model;
    enum class Action { Add };
    map<string, Action> actionMap;
public:
    IncomeController(shared_ptr<IModel> model) : model(model){
        actionMap = {
            { "add_income", Action::Add}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

/**
 * @brief Implementation of IController interface, handles when it is needed to display help to the user
 */
class HelpController final : public IController 
{
private:
    shared_ptr<IModel> model;
    enum class Action { Help };
    map<string, Action> actionMap;
public:
    HelpController(shared_ptr<IModel> model) : model(model){
        actionMap = {
            { "--help", Action::Help}
        };
    }
    virtual unique_ptr<IView> HandleRequest(string command, const vector<string> & params) override;
};

/**
 * @brief Class, that handles dispatching work to some exact controller based on the command.
 * Has map between commands and controllers. 
 */
class MasterController{
private:
    map<string, shared_ptr<IController>> & commandControllerMap;
public:
    MasterController(map<string, shared_ptr<IController>> & commandControllerMap) : commandControllerMap(commandControllerMap){}
    unique_ptr<IView> ExecuteRequest(vector<string> & args);
};

#endif