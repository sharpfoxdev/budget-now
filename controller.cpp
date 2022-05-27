#include "controller.hpp"


unique_ptr<IView> MasterController::ExecuteRequest(vector<string> & args){
    if(args.size() < 1){
        cout << "inside";
        unique_ptr<IView> ptr = make_unique<MessageView>("Too few arguments, use --help to see available commands. ", "");
        ptr.get()->RenderTo(cout);
        return ptr;
    }
    auto it = commandControllerMap.find(args[0]);
    if (it == commandControllerMap.end()) {
        return make_unique<MessageView>("Master controller doesn't know command: " + args[0], "");
    }
    else{
        shared_ptr<IController> controller = it->second;
        args.erase(args.begin());
        return controller.get()->HandleRequest(args[0], args);
    }
}
unique_ptr<IView> BudgetController::HandleRequest(string command, const vector<string> & params){
    auto it = actionMap.find(command);
    if (it == actionMap.end()) {
        //didnt find action
        return make_unique<MessageView>("Budget controller doesn't know command: " + command, "");
    }
    else{
        switch (it->second)
        {
            case Action::Add:
            {
                bool success = model.AddBudget(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            case Action::Copy:
            {
                bool success = model.CopyBudget(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            case Action::Info:
            {
                dataNS::Budget budget;
                try{
                    budget = model.GetBudget(params);
                }
                catch (const std::exception &exc)
                {
                    return make_unique<MessageView>(exc.what(), "");
                }
                catch(...){
                    return make_unique<MessageView>("Unknown error. ", "");
                }
                return make_unique<BudgetInfoView>(budget, model.GetMessage());
                break;
            }
            case Action::List:
            {
                dataNS::BudgetsHolder budgets = model.GetBudgetsHolder();
                return make_unique<BudgetsListView>(budgets, model.GetMessage());
                break;
            }
            case Action::SetPrimary:
            {
                bool success = model.SetPrimaryBudget(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            default:
            {
                return make_unique<MessageView>("How the hell did you get here. ", "");
                break;
            }
        }
    }
}

unique_ptr<IView> CategoryController::HandleRequest(string command, const vector<string> & params){
    auto it = actionMap.find(command);
    if (it == actionMap.end()) {
        //didnt find action
        return make_unique<MessageView>("Category controller doesn't know command: " + command, "");
    }
    else{
        switch (it->second)
        {
            case Action::Add:
            {
                bool success = model.AddCategory(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            case Action::Info:
            {
                dataNS::Category category;
                try{
                    category = model.GetCategory(params);
                }
                catch (const std::exception &exc)
                {
                    return make_unique<MessageView>(exc.what(), "");
                }
                catch(...){
                    return make_unique<MessageView>("Unknown error. ", "");
                }
                return make_unique<CategoryInfoView>(category, model.GetMessage());
                break;
            }
            default:
            {
                return make_unique<MessageView>("How the hell did you get here. ", "");
                break;
            }
        }
    }
}

unique_ptr<IView> IncomeController::HandleRequest(string command, const vector<string> & params){
    auto it = actionMap.find(command);
    if (it == actionMap.end()) {
        //didnt find action
        return make_unique<MessageView>("Income controller doesn't know command: " + command, "");
    }
    else{
        switch (it->second)
        {
            case Action::Add:
            {
                bool success = model.AddIncome(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            default:
            {
                return make_unique<MessageView>("How the hell did you get here. ", "");
                break;
            }
        }
    }
}

unique_ptr<IView> ExpenseController::HandleRequest(string command, const vector<string> & params){
    auto it = actionMap.find(command);
    if (it == actionMap.end()) {
        //didnt find action
        return make_unique<MessageView>("Expense controller doesn't know command: " + command, "");
    }
    else{
        switch (it->second)
        {
            case Action::Add:
            {
                bool success = model.AddExpense(params);
                return make_unique<OperationResultView>(success, model.GetMessage());
                break;
            }
            default:
            {
                return make_unique<MessageView>("How the hell did you get here. ", "");
                break;
            }
        }
    }
}
unique_ptr<IView> HelpController::HandleRequest(string command, const vector<string> & params){
    return make_unique<HelpView>();
}

// /**
//  * @brief Calls view to print help text to CLI
//  */
// void Controller::PrintHelp(){
//     view.PrintHelp();
// }

// /**
//  * @brief Calls model to set primary budget and then calls view to display results. 
//  * @param params primary budget parameters
//  */
// void Controller::SetPrimaryBudget(const vector<string> & params){
//     bool success = model.SetPrimaryBudget(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Gets BudgetHolder from Model and then calls View to display it
//  */
// void Controller::ListAllBudgets(){
//     dataNS::BudgetsHolder budgets = model.GetBudgetsHolder();
//     view.PrintBudgetsList(budgets);
// }
// /**
//  * @brief Calls Model to copy old budget information into new one. 
//  * @param params 
//  */
// void Controller::CopyBudget(const vector<string> & params){
//     bool success = model.CopyBudget(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Adds budget into Model and displays result
//  * @param params Budget parameters
//  */
// void Controller::AddBudget(const vector<string> & params){
//     bool success = model.AddBudget(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Adds Expense into Model and displays result through View
//  * @param params Expense parameters
//  */
// void Controller::AddExpense(const vector<string> & params){
//     bool success = model.AddExpense(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Adds category into Model and displays result through View
//  * @param params Category params
//  */
// void Controller::AddCategory(const vector<string> & params){
//     bool success = model.AddCategory(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Adds income into Model and displays result through View
//  * @param params Income params
//  */
// void Controller::AddIncome(const vector<string> & params){
//     bool success = model.AddIncome(params);
//     view.PrintOperationResult(success);
// }
// /**
//  * @brief Gets budget from Model and calls View to display it. 
//  * @param params Budget params
//  */
// void Controller::PrintBudgetInfo(const vector<string> & params){
//     dataNS::Budget budget;
//     try{
//         budget = model.GetBudget(params);
//     }
//     catch(...){
//         return;
//     }
//     view.PrintBudgetInfo(budget);
// }
// /**
//  * @brief Gets Category from Model and calls View to display it. 
//  * @param params Category params
//  */
// void Controller::PrintCategoryInfo(const vector<string> & params){
//     dataNS::Category category;
//     try{
//         category = model.GetCategory(params);
//     }
//     catch(...){
//         return;
//     }
//     view.PrintCategoryInfo(category);
// }