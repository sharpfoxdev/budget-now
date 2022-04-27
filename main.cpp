#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iostream>


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

using MapType = std::map<string, std::function<void()>>;

class CommandLineParser{
public:
    MapType commandMap;
    vector<string> args;
    void ParseArgs();

    CommandLineParser(const vector<string> & args) : args(args){
        commandMap = {
        { "expense", CommandLineParser::ParseExpenseParams},
        { "set_primary", CommandLineParser::ParseSetPrimaryParams},
        { "add_budget", CommandLineParser::ParseAddBudgetParams},
        { "add_category", CommandLineParser::ParseAddCategoryParams}, 
        { "add_income", CommandLineParser::ParseAddIncomeParams}, 
        { "copy_budget", CommandLineParser::ParseCopyBudgetParams}, 
        { "list", CommandLineParser::ParseListParams}, 
        { "info_budget", CommandLineParser::ParseInfoBudgetParams}, 
        { "info_category", CommandLineParser::ParseInfoCategoryParams}, 
        { "--help", CommandLineParser::ParseHelp}
        };
    }
private:
    static void SignalUnknownCommand(const string & command);
    static void SignalIncorrectNumberOfArgs();
    static void ParseExpenseParams();
    static void ParseSetPrimaryParams();
    static void ParseAddBudgetParams();
    static void ParseAddCategoryParams();
    static void ParseAddIncomeParams();
    static void ParseCopyBudgetParams();
    static void ParseListParams();
    static void ParseInfoBudgetParams();
    static void ParseInfoCategoryParams();
    static void ParseHelp();
};
void CommandLineParser::SignalUnknownCommand(const string & arg){
    cout << "Unknown command: " << arg << endl;
}
void CommandLineParser::SignalIncorrectNumberOfArgs(){
    cout << "Incorrect number of args passed on command line. " << endl;
}

void CommandLineParser::ParseArgs(){
    if(args.size() < 1){
        SignalIncorrectNumberOfArgs();
        return;
    }
    auto it = commandMap.find(args[0]);
    if (it != commandMap.end()) {
        it->second();
    }
    else{
        SignalUnknownCommand(args[0]);
        return;
    }
}

void CommandLineParser::ParseExpenseParams(){
    cout << "expense" << endl;
}
void CommandLineParser::ParseSetPrimaryParams(){
    cout << "setprim" << endl;
}
void CommandLineParser::ParseAddBudgetParams(){
    cout << "addbudg" << endl;
}
void CommandLineParser::ParseAddCategoryParams(){
    cout << "addcat" << endl;
}
void CommandLineParser::ParseAddIncomeParams(){
    cout << "addinc" << endl;
}
void CommandLineParser::ParseCopyBudgetParams(){
    cout << "copy" << endl;
}
void CommandLineParser::ParseListParams(){
    cout << "list" << endl;
}
void CommandLineParser::ParseInfoBudgetParams(){
    cout << "infobudg" << endl;
}
void CommandLineParser::ParseInfoCategoryParams(){
    cout << "infocat" << endl;
}
void CommandLineParser::ParseHelp(){
    cout << "hellp" << endl;
}

int main(int argc, char * argv[]) {
    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;
}