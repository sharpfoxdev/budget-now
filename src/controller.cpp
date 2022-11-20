#include "controller.hpp"

/**
 * @brief Based on the command-controller map calls correct controller, passes arguments to it
 * and after request is finished, returns view that can display result
 * @param args arguments from command line
 * @return unique_ptr<IView> view that can display result of request
 */
unique_ptr<IView> MasterController::ExecuteRequest(vector<string> & args){
    //not enough args
    if(args.size() < 1){
        unique_ptr<IView> ptr = make_unique<MessageView>("Too few arguments, use --help to see available commands. ", "");
        cout.flush();
        return ptr;
    }
    //get controller
    auto it = commandControllerMap.find(args[0]);
    if (it == commandControllerMap.end()) {
        return make_unique<MessageView>("Master controller doesn't know command: " + args[0], "");
    }
    else{
        shared_ptr<IController> controller = it->second;
        string command = args[0];
        args.erase(args.begin());
        return controller.get()->HandleRequest(command, args);
    }
}
/**
 * @brief Updates/retrieves data from Model based on command and returns view, that can display result
 * @param command command
 * @param params parameters of command
 * @return unique_ptr<IView> view that can display result
 */
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
                bool success = model.get()->AddBudget(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
                break;
            }
            case Action::Copy:
            {
                bool success = model.get()->CopyBudget(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
                break;
            }
            case Action::Info:
            {
                dataNS::Budget budget;
                try{
                    budget = model.get()->GetBudget(params);
                }
                catch (const std::exception &exc)
                {
                    return make_unique<MessageView>(exc.what(), "");
                }
                catch(...){
                    return make_unique<MessageView>("Unknown error. ", "");
                }
                return make_unique<BudgetInfoView>(budget, model.get()->GetMessage());
                break;
            }
            case Action::List:
            {
                dataNS::BudgetsHolder budgets = model.get()->GetBudgetsHolder();
                return make_unique<BudgetsListView>(budgets, model.get()->GetMessage());
                break;
            }
            case Action::SetPrimary:
            {
                bool success = model.get()->SetPrimaryBudget(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
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

/**
 * @brief Updates/retrieves data from Model based on command and returns view, that can display result
 * @param command command
 * @param params parameters of command
 * @return unique_ptr<IView> view that can display result
 */
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
                bool success = model.get()->AddCategory(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
                break;
            }
            case Action::Info:
            {
                dataNS::Category category;
                try{
                    category = model.get()->GetCategory(params);
                }
                catch (const std::exception &exc)
                {
                    return make_unique<MessageView>(exc.what(), "");
                }
                catch(...){
                    return make_unique<MessageView>("Unknown error. ", "");
                }
                return make_unique<CategoryInfoView>(category, model.get()->GetMessage());
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
/**
 * @brief Updates/retrieves data from Model based on command and returns view, that can display result
 * @param command command
 * @param params parameters of command
 * @return unique_ptr<IView> view that can display result
 */
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
                bool success = model.get()->AddIncome(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
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

/**
 * @brief Updates/retrieves data from Model based on command and returns view, that can display result
 * @param command command
 * @param params parameters of command
 * @return unique_ptr<IView> view that can display result
 */
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
                bool success = model.get()->AddExpense(params);
                return make_unique<OperationResultView>(success, model.get()->GetMessage());
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
/**
 * @brief Gets called when helptext is needed, returns HelpView that can display it
 * @param command command
 * @param params parameters of command
 * @return unique_ptr<IView> view that can display result
 */
unique_ptr<IView> HelpController::HandleRequest(string command, const vector<string> & params){
    return make_unique<HelpView>("howToUse.txt");
}