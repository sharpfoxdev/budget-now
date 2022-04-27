#include "commandLineParser.hpp"


CommandLineParser::CommandLineParser(const vector<string> & args) : args(args){
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