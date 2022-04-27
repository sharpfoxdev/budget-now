#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

class Expense{

};

class Category{

};
class Budget{

};
class View{
public:
    static void PrintAllBudgets(vector<Budget> budgets);

};

class Model{

};

class Controller{
public: 
    void ListAllBudgets();
    void AddBudget();
    void CopyBudget();
    void AddExpense();
    void AddCategory();
    void SetCurrentBudget();
    void AddIncome();
private:

};

class CommandLineParser{
public:
    void ParseArgs(vector<string> args);
private:
    Controller controller;
    const string ADD = "add";
    const string BUDGET = "budget";
    const string CATEGORY = "category";
    const string INCOME = "income";
    const string LIST = "list";
    const string SET = "set";
    const string COPY = "copy";
    const string INFO = "info";
    const string EXPENSE = "expense";
    const string HELP = "--help";
    void ReadFirstArg(vector<string> args);
    void SignalUnknownCommand(const string & command);
    void SignalIncorrectNumberOfArgs();
    void ManageAdd(vector<string> restArgs);
    void ManageCopy(vector<string> restArgs);
    void ManageList(vector<string> restArgs);
    void ManageInfo(vector<string> restArgs);
    void ParseSetParams(vector<string> restArgs);
    void ParseExpenseParams(vector<string> restArgs);
    void ParseBudgetParams(vector<string> restArgs);
    void ParseCategoryParams(vector<string> restArgs);
    void ParseIncomeParams(vector<string> restArgs);
    void ParseCopyParams(vector<string> restArgs);
    void ParseBudgetName(vector<string> restArgs);
    void ParseCategoryName(vector<string> restArgs);
};
void CommandLineParser::SignalUnknownCommand(const string & arg){
    cout << "Unknown command: " << arg << endl;
}
void CommandLineParser::SignalIncorrectNumberOfArgs(){
    cout << "Incorrect number of args passed on command line. " << endl;
}
void CommandLineParser::ParseArgs(vector<string> args){
    ReadFirstArg(args);
}
void CommandLineParser::ReadFirstArg(vector<string> args){
    if(args.size() < 1){
        SignalIncorrectNumberOfArgs();
        return;
    }
    if(args[0] == ADD){
        args.erase(args.begin());
        ManageAdd(args);
    }
    else if(args[0] == SET){
        args.erase(args.begin());
        ParseSetParams(args);
    }
    else if(args[0] == COPY){
        args.erase(args.begin());
        ParseCopyParams(args);
    }
    else if(args[0] == LIST){
        args.erase(args.begin());
        controller.ListAllBudgets();
    }
    else if(args[0] == INFO){
        args.erase(args.begin());
        ManageInfo(args);
    }
    else if(args[0] == EXPENSE){
        args.erase(args.begin());
        ParseExpenseParams(args);
    }
    else{
        SignalUnknownCommand(args[0]);
        return;
    }
}
void CommandLineParser::ManageAdd(vector<string> restArgs){
    if(restArgs.size() < 1){
        SignalIncorrectNumberOfArgs();
        return;
    }
    if(restArgs[0] == BUDGET){
        restArgs.erase(restArgs.begin());
        ParseBudgetParams(restArgs);
    }
    else if(restArgs[0] == CATEGORY){
        restArgs.erase(restArgs.begin());
        ParseCategoryParams(restArgs);
    }
    else if(restArgs[0] == INCOME){
        restArgs.erase(restArgs.begin());
        ParseIncomeParams(restArgs);
    }
    else{
        SignalUnknownCommand(restArgs[0]);
        return;
    }
}

void CommandLineParser::ManageInfo(vector<string> restArgs){
    if(restArgs.size() < 1){
        SignalIncorrectNumberOfArgs();
        return;
    }
    if(restArgs[0] == BUDGET){
        restArgs.erase(restArgs.begin());
        ParseBudgetName(restArgs); //mozna by slo udelat primo
    }
    else if(restArgs[0] == CATEGORY){
        restArgs.erase(restArgs.begin());
        ParseCategoryName(restArgs);
    }
}

int main(int argc, char * argv[]){
    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser;
    parser.ParseArgs(args);

    return 0;
}