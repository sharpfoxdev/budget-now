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
        it->second(*this);
    }
    else{
        SignalUnknownCommand(args[0]);
        return;
    }
}

void CommandLineParser::ParseExpenseParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.AddExpense(self.args);
}
void CommandLineParser::ParseSetPrimaryParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.SetPrimaryBudget(self.args);
}
void CommandLineParser::ParseAddBudgetParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.AddBudget(self.args);
}
void CommandLineParser::ParseAddCategoryParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.AddCategory(self.args);
}
void CommandLineParser::ParseAddIncomeParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.AddIncome(self.args);
}
void CommandLineParser::ParseCopyBudgetParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.CopyBudget(self.args);
}
void CommandLineParser::ParseListParams(CommandLineParser self){
    self.controller.ListAllBudgets();
}
void CommandLineParser::ParseInfoBudgetParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.PrintBudgetInfo(self.args);
}
void CommandLineParser::ParseInfoCategoryParams(CommandLineParser self){
    self.args.erase(self.args.begin());
    self.controller.PrintCategoryInfo(self.args);
}
void CommandLineParser::ParseHelp(CommandLineParser self){
    self.controller.PrintHelp();
}