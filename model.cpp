#include "model.hpp"
namespace dataNS{
    /**
     * @brief Functions, that are called by json library when converting structures
     * into json
     * @param j json
     * @param e Expense structure
     */
    void to_json(json& j, const DateStruct& d){
        j = json{{"day", d.day}, {"month", d.month}, {"year", d.year}};
    }
    void to_json(json& j, const Expense& e) {
        j = json{{"amount", e.amount}, {"comment", e.comment}, {"date", e.date}};
    }
    void to_json(json& j, const Income& i) {
        j = json{{"amount", i.amount}, {"comment", i.comment}};
    }
    void to_json(json& j, const Category& c){
        j = json{{"budgeted", c.budgeted}, {"expenses", c.expenses}};
    }
    void to_json(json& j, const Budget& b){
        j = json{{"incomes", b.incomes}, {"categories", b.categories}, {"start", b.start}, {"end", b.end}};
    }
    void to_json(json& j, const BudgetsHolder& h){
        j = json{{"primaryBudgetName", h.primaryBudgetName}, {"primaryBudget", h.primaryBudget}, {"otherBudgets", h.otherBudgets}};
    }
    /**
     * @brief Functions, that are called by json library when converting structures
     * from json
     * @param j json
     * @param e expense structure
     */
    void from_json(const json& j, DateStruct& d){
        j.at("day").get_to(d.day);
        j.at("month").get_to(d.month);
        j.at("year").get_to(d.year);
    }
    void from_json(const json& j, Expense& e) {
        j.at("amount").get_to(e.amount);
        j.at("comment").get_to(e.comment);
        j.at("date").get_to(e.date);
    }
    void from_json(const json& j, Income& i) {
        j.at("amount").get_to(i.amount);
        j.at("comment").get_to(i.comment);
    }
    void from_json(const json& j, Category& c){
        j.at("budgeted").get_to(c.budgeted);
        j.at("expenses").get_to(c.expenses);
    }
    void from_json(const json& j, Budget& b){
        j.at("incomes").get_to(b.incomes);
        j.at("categories").get_to(b.categories);
        j.at("start").get_to(b.start);
        j.at("end").get_to(b.end);
    }
    void from_json(const json& j, BudgetsHolder& h){
        j.at("primaryBudgetName").get_to(h.primaryBudgetName);
        j.at("primaryBudget").get_to(h.primaryBudget);
        j.at("otherBudgets").get_to(h.otherBudgets);
    }

}
/**
 * @brief Signals to the user incorrect number of command
 * parameters were used. 
 */
void Model::SignalIncorrectNumberOfParams(){
    cout << "Incorrect number of parameters. " << endl;
}
/**
 * @brief Signals to the user incorrect type of parameter
 * was used
 */
void Model::SignalIncorrectParamType(){
    cout << "Incorrect parameter type. " << endl;
}
/**
 * @brief Signals to the user, that he is trying to make a
 * duplicate name (of budget, category).
 */
void Model::SignalUsedName(){
    cout << "You are trying to use name that is used elsewhere. " << endl;
}
/**
 * @brief Signals to the user, that no primary budget is set. 
 */
void Model::SignalNoPrimaryBudget(){
    cout << "There is no primary budget set. " << endl;
}
/**
 * @brief Gets budgets holder from .json file
 * @return dataNS::BudgetsHolder 
 */
dataNS::BudgetsHolder Model::GetBudgetsHolder(){
    try{
        ifstream fs(jsonFile);
        json j;
        fs >> j;
        auto budgetsHolder = j.get<dataNS::BudgetsHolder>();
        return budgetsHolder;
    }
    catch(...){
        dataNS::BudgetsHolder bh;
        return bh;
    }
}
/**
 * @brief Saves budgets holder into a .json file
 * @param bh budgets holder
 */
void Model::SaveBudgetsHolder(dataNS::BudgetsHolder bh){
    json j;
    j = bh;
    std::ofstream ofstr(jsonFile);
    ofstr << std::setw(4) << j << std::endl;
}
/**
 * @brief Creates new budget and copies category names and budgeted amounts from old budget
 * @param params [0] new_budget_name, [1] old_budget_name
 * @return true operation successful
 * @return false operation not successful
 */
bool Model::CopyBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() < 4){
        SignalIncorrectNumberOfParams();
        return false;
    }
    string oldName = params[0];
    string newName = params[1];
    string startDateString = params[2];
    string endDateString = params[3];
    dataNS::DateStruct startDateParsed;
    dataNS::DateStruct endDateParsed;
    //parsing date
    try{
        startDateParsed = DateManager::ParseDate(startDateString);
        endDateParsed = DateManager::ParseDate(endDateString);
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    if(!(startDateParsed <= endDateParsed)){
        cout << "first date should be smaller than second. " << endl;
        return false;
    }
    //Get old budget
    dataNS::Budget oldBudget;
    try{
        oldBudget = GetBudget(vector<string>{oldName});
    }
    catch(...){
        cout << "Couldn't locate old budget: " << oldName << endl;
        return false;
    }
    dataNS::Budget newBudget;
    newBudget.start = startDateParsed;
    newBudget.end = endDateParsed;
    //search duplicate name
    auto it = bh.otherBudgets.find(newName);
    if (it != bh.otherBudgets.end() || bh.primaryBudgetName == newName) {
        //found duplicate
        SignalUsedName();
        return false;
    }
    //iterate over old budget categories and copy them into new one
    for(const auto &myPair : oldBudget.categories){
        dataNS::Category newCategory;
        newCategory.budgeted = myPair.second.budgeted;
        newBudget.categories.insert(make_pair(myPair.first, newCategory));
    }
    bh.otherBudgets.insert(make_pair(newName, newBudget));
    SaveBudgetsHolder(bh);
    return true;
}
/**
 * @brief Sets given budget as primary
 * @param params 
 * @return true operation successful
 * @return false operation not successful
 */
bool Model::SetPrimaryBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        return false;
    }
    string name = params[0];
    if(bh.primaryBudgetName == name){
        // budget is already primary
        return true;
    }
    //searching for given budget
    auto it = bh.otherBudgets.find(name);
    if (it == bh.otherBudgets.end()) {
        cout << "Couldn't locate budget: " << name << endl;
        return false;
    }
    //making copies, because inserting into map can make it broken possibly, since we are working with iterators
    string newPrimName = it->first;
    dataNS::Budget newPrimBudg = it->second;
    //remove new main budget from others
    bh.otherBudgets.erase(it);
    //move primary budget into other
    bh.otherBudgets.insert(make_pair(bh.primaryBudgetName, bh.primaryBudget)); 
    //set new primary name and budget
    bh.primaryBudgetName = newPrimName;
    bh.primaryBudget = newPrimBudg;
    SaveBudgetsHolder(bh);
    return true;
}
/**
 * @brief Adds new budget into budgets holder
 * @param params budget name [0]
 * @return true operation successful
 * @return false operation not successful
 */
bool Model::AddBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() < 3){
        SignalIncorrectNumberOfParams();
        return false;
    }
    string name = params[0];
    string startDateString = params[1];
    string endDateString = params[2];
    dataNS::DateStruct startDateParsed;
    dataNS::DateStruct endDateParsed;
    //parsing date
    try{
        startDateParsed = DateManager::ParseDate(startDateString);
        endDateParsed = DateManager::ParseDate(endDateString);
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    if(!(startDateParsed <= endDateParsed)){
        cout << "first date should be smaller than second. " << endl;
        return false;
    }

    //check for duplicates
    auto it = bh.otherBudgets.find(name);
    if (it != bh.otherBudgets.end() || bh.primaryBudgetName == name) {
        //found duplicate
        SignalUsedName();
        return false;
    }
    dataNS::Budget budget;
    budget.start = startDateParsed;
    budget.end = endDateParsed;
    if(bh.primaryBudgetName == ""){
        //we have no budgets yet, this is the first one
        //so we set it as primary
        bh.primaryBudgetName = name;
        bh.primaryBudget = budget;
    }
    else{
        bh.otherBudgets.insert(make_pair(name, budget));
    }
    SaveBudgetsHolder(bh);
    return true;
}
/**
 * @brief Adds expense to primary budget
 * @param params category[0], amount[1], comment[2]
 * @return true operation successful
 * @return false operation not successful
 */
bool Model::AddExpense(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    //check that we have primary budget
    if(bh.primaryBudgetName == ""){
        SignalNoPrimaryBudget();
        return false;
    }
    if(params.size() < 3){
        SignalIncorrectNumberOfParams();
        return false;
    }
    dataNS::Expense expense;
    string categoryName = params[0];
    string amount = params[1];
    expense.comment = params[2];
    string date = params[3];

    //searching for given category in primary budget
    auto it = bh.primaryBudget.categories.find(categoryName);
    if (it == bh.primaryBudget.categories.end()) {
        cout << "Couldn't find category: " << categoryName << endl;
        return false;
    }
    try{
        // parsing expense amount
        expense.amount = std::stod(amount);
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    //parsing date
    if(params.size() >= 4){
        try{
            dataNS::DateStruct dateParsed = DateManager::ParseDate(date);
            expense.date = dateParsed;
        }
        catch(...){
            SignalIncorrectParamType();
            return false;
        }
    }
    if(params.size() == 3){
        expense.date = DateManager::GetTodaysDate();
    }
    bool correctDate = DateManager::DateInBetweenOtherDates(bh.primaryBudget.start, expense.date, bh.primaryBudget.end);
    if(!correctDate){
        cout << "Expense date not in the budget date range. " << endl;
        return false;
    }
    it->second.expenses.push_back(expense);
    DateManager::SignalSpendingSpeed(bh.primaryBudget.start, bh.primaryBudget.end, expense.date, it->second);
    SaveBudgetsHolder(bh);
    return true;
}

/**
 * @brief Adds category to primary budget
 * @param params category name[0], budgeted amount[1]
 * @return true opetation successful
 * @return false operation not successful
 */
bool Model::AddCategory(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    //check that we have primary budget
    if(bh.primaryBudgetName == ""){
        SignalNoPrimaryBudget();
        return false;
    }
    if(params.size() < 2){
        SignalIncorrectNumberOfParams();
        return false;
    }
    //params parsing
    string name = params[0];
    string amountToBudget = params[1];
    //parsing string amount into double
    dataNS::Category category;
    try{
        double budgeted = std::stod(amountToBudget);
        category.budgeted = budgeted;
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    //check for duplicate
    auto it = bh.primaryBudget.categories.find(name);
    if (it != bh.primaryBudget.categories.end()) {
        //we found duplicate
        SignalUsedName();
        return false;
    }
    bh.primaryBudget.categories.insert(make_pair(name, category));
    SaveBudgetsHolder(bh);
    return true;
}
/**
 * @brief Adds income to primary budget
 * @param params amount[0], comment[1]
 * @return true operation successful
 * @return false operation not successful
 */
bool Model::AddIncome(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    //check that we have primary budget
    if(bh.primaryBudgetName == ""){
        SignalNoPrimaryBudget();
        return false;
    }
    if(params.size() < 1){
        SignalIncorrectNumberOfParams();
        return false;
    }
    dataNS::Income income;
    try{
        income.amount = std::stod(params[0]);
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    //we have comment as well with the expense
    if(params.size() == 2){
        income.comment = params[1];
    }
    bh.primaryBudget.incomes.push_back(income);
    SaveBudgetsHolder(bh);
    return true;
}
/**
 * @brief Gets budget by name from budgets holder
 * @param params budget name[0]
 * @return dataNS::Budget requested budget
 * @throws std::lenght_error When incorrect number of params is passed
 * @throws std::invalid_argument when no primary budget is set or couldnt locate budget by name
 */
dataNS::Budget Model::GetBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    //check for primary budget
    if(bh.primaryBudgetName == ""){
        SignalNoPrimaryBudget();
        throw std::invalid_argument("No primary budget set. ");
    }
    if(params.size() == 0){
        //no arguments, print primary budget
        return bh.primaryBudget;
    }
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        throw std::length_error("Incorrect number of params. ");
    }
    string name = params[0];
    if(bh.primaryBudgetName == name){
        // requested budget is primary budget
        return bh.primaryBudget;
    }
    //searching for given budget
    auto it = bh.otherBudgets.find(name);
    if (it == bh.otherBudgets.end()) {
        cout << "Couldnt locate given budget. " << endl;
        throw std::invalid_argument("Couldnt locate given budget. ");
    }
    return it->second;
}
/**
 * @brief Gets category from primary budget
 * @param params category name [0]
 * @return dataNS::Category requested category
 * @throws std::lenght_error When incorrect number of params is passed
 * @throws std::invalid_argument when no primary budget is set or couldnt locate category by name
 */
dataNS::Category Model::GetCategory(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        throw std::length_error("Incorrect number of params. ");
    }
    if(bh.primaryBudgetName == ""){
        SignalNoPrimaryBudget();
        throw std::invalid_argument("No primary budget set. ");
    }
    string name = params[0];
    //searching for given budget
    auto it = bh.primaryBudget.categories.find(name);
    if (it == bh.primaryBudget.categories.end()) {
        cout << "Couldnt locate given category. " << endl;
        throw std::invalid_argument("Couldnt locate given category. ");
    }
    return it->second;
}