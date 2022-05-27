// #include "commandLineParser.hpp"

// /**
//  * @brief Constructs new CommandLineParser object. Creates map between commands and functions
//  * to call, when those CLI commands are encountered
//  * @param args CLI arguments
//  */
// CommandLineParser::CommandLineParser(const vector<string> & args) : args(args){
//     commandMap = {
//     { "expense", CommandLineParser::ParseExpenseParams},
//     { "set_primary", CommandLineParser::ParseSetPrimaryParams},
//     { "add_budget", CommandLineParser::ParseAddBudgetParams},
//     { "add_category", CommandLineParser::ParseAddCategoryParams}, 
//     { "add_income", CommandLineParser::ParseAddIncomeParams}, 
//     { "copy_budget", CommandLineParser::ParseCopyBudgetParams}, 
//     { "list", CommandLineParser::ParseListParams}, 
//     { "info_budget", CommandLineParser::ParseInfoBudgetParams}, 
//     { "info_category", CommandLineParser::ParseInfoCategoryParams}, 
//     { "--help", CommandLineParser::ParseHelp}
//     };
// }
// /**
//  * @brief Used to signal to the user on the command line,
//  * that he used unknown command.
//  * @param arg CLI args
//  * @result Prints out which unknown command was used.
//  */
// void CommandLineParser::SignalUnknownCommand(const string & arg){
//     cout << "Unknown command: " << arg << endl;
// }

// /**
//  * @brief Signals user on the CLI, that he used incorrect number of arguments
//  */
// void CommandLineParser::SignalIncorrectNumberOfArgs(){
//     cout << "Incorrect number of args passed on command line. " << endl;
// }

// /**
//  * @brief Searches CLI args in map and calls appropriate member function. 
//  */
// void CommandLineParser::ParseArgs(){
//     if(args.size() < 1){
//         SignalIncorrectNumberOfArgs();
//         return;
//     }
//     auto it = commandMap.find(args[0]);
//     if (it != commandMap.end()) {
//         it->second(*this); //calling correct member function, that will handle args
//     }
//     else{
//         SignalUnknownCommand(args[0]);
//         return;
//     }
// }
// /**
//  * @brief Gets Expense parameters after calling expense command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseExpenseParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.AddExpense(self.args);
// }
// /**
//  * @brief Gets budget parameters after calling set_primary budget command and passes them to controller.  
//  * @param self 
//  */
// void CommandLineParser::ParseSetPrimaryParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.SetPrimaryBudget(self.args);
// }
// /**
//  * @brief Gets budget parameters after calling add_budget command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseAddBudgetParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.AddBudget(self.args);
// }
// /**
//  * @brief Gets category parameters after calling add_category command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseAddCategoryParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.AddCategory(self.args);
// }
// /**
//  * @brief Gets income parameters after calling add_income command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseAddIncomeParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.AddIncome(self.args);
// }
// /**
//  * @brief Gets budget parameters after calling copy_budget command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseCopyBudgetParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.CopyBudget(self.args);
// }
// /**
//  * @brief Calls controller to list all budgets. 
//  * @param self 
//  */
// void CommandLineParser::ParseListParams(CommandLineParser & self){
//     self.controller.ListAllBudgets();
// }
// /**
//  * @brief Gets budget parameters after calling info_budget command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseInfoBudgetParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.PrintBudgetInfo(self.args);
// }
// /**
//  * @brief Gets category parameters after calling info_category command and passes them to controller. 
//  * @param self 
//  */
// void CommandLineParser::ParseInfoCategoryParams(CommandLineParser & self){
//     self.args.erase(self.args.begin());
//     self.controller.PrintCategoryInfo(self.args);
// }
// /**
//  * @brief Calls Controller to display help text after command --help
//  * @param self 
//  */
// void CommandLineParser::ParseHelp(CommandLineParser & self){
//     self.controller.PrintHelp();
// }