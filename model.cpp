#include "model.hpp"
namespace dataNS{
    void to_json(json& j, const Expense& e) {
        j = json{{"amount", e.amount}, {"comment", e.comment}};
    }
    void to_json(json& j, const Income& i) {
        j = json{{"amount", i.amount}, {"comment", i.comment}};
    }
    void to_json(json& j, const Category& c){
        j = json{{"name", c.name}, {"budgeted", c.budgeted}, {"expenses", c.expenses}};
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
        j.at("name").get_to(c.name);
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
dataNS::BudgetsHolder Model::GetAllBudgets(){
    ifstream fs("pretty.json");
    json j;
    fs >> j;
    auto budgetsHolder = j.get<dataNS::BudgetsHolder>();
    return budgetsHolder;
}
void Model::SaveBudgetsHolder(dataNS::BudgetsHolder bh){
    json j;
    j = bh;
    std::ofstream ofstr("pretty.json");
    ofstr << std::setw(4) << j << std::endl;
}

bool Model::CopyBudget(const vector<string> & params){

    // write prettified JSON to another file
    json j;
    dataNS::Expense ex{52, "haha"};
    dataNS::Expense ex2{98.3, "hehe"};
    dataNS::Income inc{800, "incc"};
    vector<dataNS::Expense> vec = {ex, ex2};
    dataNS::Category cat{"categ", 800, vec};
    dataNS::Budget budg{vector<dataNS::Income>{inc}, vector<dataNS::Category>{cat}};
    dataNS::BudgetsHolder bh{"none", budg, map<string, dataNS::Budget>{make_pair("leden", budg)}};
    j = bh;
    std::ofstream ofstr("pretty.json");
    ofstr << std::setw(4) << j << std::endl;
    return true;
}
bool Model::SetPrimaryBudget(const vector<string> & params){
    cout << "called";
    dataNS::BudgetsHolder bh = GetAllBudgets();
    if(params.size() != 1){
        return false;
    }
    //searching for given budget
    auto it = bh.otherBudgets.find(params[0]);
    if (it == bh.otherBudgets.end()) {
        return false;
    }
    //making copies, because inserting into map can make it broken possibly, since we are working with iterators
    string newPrimName = it->first;
    dataNS::Budget newPrimBudg = it->second;
    bh.otherBudgets.erase(it);
    bh.otherBudgets.insert(make_pair(bh.primaryBudgetName, bh.primaryBudget));
    cout << bh.primaryBudgetName;
    bh.primaryBudgetName = newPrimName;
    bh.primaryBudget = newPrimBudg;
    SaveBudgetsHolder(bh);
    return true;
}
bool Model::AddBudget(const vector<string> & params){
    return true;
}
bool Model::AddExpense(const vector<string> & params){
    return true;
}
bool Model::AddCategory(const vector<string> & params){
    return true;
}
bool Model::AddIncome(const vector<string> & params){
    return true;
}
dataNS::Budget Model::GetBudget(const vector<string> & params){
    dataNS::Budget budget;
    return budget;
}
dataNS::Category Model::GetCategory(const vector<string> & params){
    dataNS::Category cat;
    return cat;
}