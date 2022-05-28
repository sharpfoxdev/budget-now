#include <string>
#include <vector>
#include <memory>
#include <map>
#include "commandLineParser.hpp"
#include "controller.hpp"

#include "view.hpp"

using namespace std;

/**
 * @brief 
 * Entry point of the program, passes CLI args into CommandLineParser. 
 * @param argc Number of arguments
 * @param argv CLI arguments
 * @return int 
 */
int main(int argc, char * argv[]) {
    shared_ptr<IModel> model = make_shared<Model>("budgetResult.json");
    shared_ptr<IController> budgetContr = make_shared<BudgetController>(model);
    shared_ptr<IController> incomeContr = make_shared<IncomeController>(model);
    shared_ptr<IController> categoryContr = make_shared<CategoryController>(model);
    shared_ptr<IController> expenseContr = make_shared<ExpenseController>(model);
    shared_ptr<IController> helpContr = make_shared<HelpController>(model);

    map<string, shared_ptr<IController>> commandControllerMap = {
        { "expense", expenseContr},
        { "set_primary", budgetContr},
        { "add_budget", budgetContr},
        { "add_category", categoryContr}, 
        { "add_income", incomeContr}, 
        { "copy_budget", budgetContr}, 
        { "list", budgetContr}, 
        { "info_budget", budgetContr}, 
        { "info_category", categoryContr}, 
        { "--help", helpContr}
    };
    vector<string> args (argv + 1, argv + argc);
    MasterController masterContr(commandControllerMap);
    unique_ptr<IView> resultView = masterContr.ExecuteRequest(args);
    resultView.get()->RenderTo(cout);
	return 0;
}