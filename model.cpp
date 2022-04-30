#include "model.hpp"
namespace dataNS{
    void to_json(json& j, const Expense& e) {
        j = json{{"amount", e.amount}, {"comment", e.comment}};
    }
    void to_json(json& j, const Income& i) {
        j = json{{"amount", i.amount}, {"comment", i.comment}};
    }
    void to_json(json& j, const Category& c){
        j = json{{"budgeted", c.budgeted}, {"expenses", c.expenses}};
    }
    void to_json(json& j, const Budget& b){
        j = json{{"incomes", b.incomes}, {"categories", b.categories}};
    }
    void to_json(json& j, const BudgetsHolder& h){
        j = json{{"primaryBudgetName", h.primaryBudgetName}, {"primaryBudget", h.primaryBudget}, {"otherBudgets", h.otherBudgets}};
    }
    void from_json(const json& j, Expense& e) {
        j.at("amount").get_to(e.amount);
        j.at("comment").get_to(e.comment);
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
    }
    void from_json(const json& j, BudgetsHolder& h){
        j.at("primaryBudgetName").get_to(h.primaryBudgetName);
        j.at("primaryBudget").get_to(h.primaryBudget);
        j.at("otherBudgets").get_to(h.otherBudgets);
    }
}
void Model::SignalIncorrectNumberOfParams(){
    cout << "Incorrect number of parameters. " << endl;
}
void Model::SignalIncorrectParamType(){
    cout << "Incorrect parameter type. " << endl;
}
void Model::SignalUsedName(){
    cout << "You are trying to use name that is used elsewhere. " << endl;
}
void Model::SignalNoPrimaryBudget(){
    cout << "There is no primary budget set. " << endl;
}
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
void Model::SaveBudgetsHolder(dataNS::BudgetsHolder bh){
    json j;
    j = bh;
    std::ofstream ofstr(jsonFile);
    ofstr << std::setw(4) << j << std::endl;
}

bool Model::CopyBudget(const vector<string> & params){

    // write prettified JSON to another file
    /*json j;
    dataNS::Expense ex{52, "haha"};
    dataNS::Expense ex2{98.3, "hehe"};
    dataNS::Income inc{800, "incc"};
    vector<dataNS::Expense> vec = {ex, ex2};
    dataNS::Category cat{"categ", 800, vec};
    dataNS::Budget budg{vector<dataNS::Income>{inc}, vector<dataNS::Category>{cat}};
    dataNS::BudgetsHolder bh{"none", budg, map<string, dataNS::Budget>{make_pair("leden", budg)}};
    j = bh;
    std::ofstream ofstr(jsonFile);
    ofstr << std::setw(4) << j << std::endl;*/
    return true;
}
bool Model::SetPrimaryBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        return false;
    }
    //searching for given budget
    auto it = bh.otherBudgets.find(params[0]);
    if (it == bh.otherBudgets.end()) {
        cout << "Couldn't locate budget: " << params[0] << endl;
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
bool Model::AddBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() < 1){
        SignalIncorrectNumberOfParams();
        return false;
    }
    string name = params[0];
    dataNS::Budget budget;
    //check for duplicates
    auto it = bh.otherBudgets.find(name);
    if (it != bh.otherBudgets.end() || bh.primaryBudgetName == name) {
        //found duplicate
        SignalUsedName();
        return false;
    }
    if(bh.primaryBudgetName == ""){
        bh.primaryBudgetName = name;
        bh.primaryBudget = budget;
    }
    else{
        bh.otherBudgets.insert(make_pair(name, budget));
    }
    SaveBudgetsHolder(bh);
    return true;
}
bool Model::AddExpense(const vector<string> & params){
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
    //searching for given category in primary budget
    auto it = bh.primaryBudget.categories.find(params[0]);
    if (it == bh.primaryBudget.categories.end()) {
        cout << "Couldn't find category: " << params[0] << endl;
        return false;
    }
    dataNS::Expense expense;
    try{
        expense.amount = std::stod(params[1]);
    }
    catch(...){
        SignalIncorrectParamType();
        return false;
    }
    //we have comment as well with the expense
    if(params.size() == 3){
        expense.comment = params[2];
    }
    it->second.expenses.push_back(expense);
    SaveBudgetsHolder(bh);
    return true;
}
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
    dataNS::Category category;
    try{
        double budgeted = std::stod(params[1]);
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
dataNS::Budget Model::GetBudget(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() == 0){
        //no arguments, print primary budget
        return bh.primaryBudget;
    }
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        //todo raise exception
    }
    string name = params[0];
    if(bh.primaryBudgetName == name){
        return bh.primaryBudget;
    }
    //searching for given budget
    auto it = bh.otherBudgets.find(name);
    if (it == bh.otherBudgets.end()) {
        cout << "Couldnt locate given budget. " << endl;
        //return false;
        //todo exception
    }
    return it->second;
}
dataNS::Category Model::GetCategory(const vector<string> & params){
    dataNS::BudgetsHolder bh = GetBudgetsHolder();
    if(params.size() != 1){
        SignalIncorrectNumberOfParams();
        //todo raise exception
    }
    string name = params[0];
    //searching for given budget
    auto it = bh.primaryBudget.categories.find(name);
    if (it == bh.primaryBudget.categories.end()) {
        cout << "Couldnt locate given category. " << endl;
        //return false;
        //todo exception
    }
    return it->second;
}