#include "model.hpp"
namespace dataNS{
    void to_json(json& j, const Expense& e) {
        j = json{{"amount", e.amount}, {"comment", e.comment}};
    }
    void to_json(json& j, const Category& c){
        j = json{{"name", c.name}, {"budgeted", c.budgeted}, {"expenses", c.expenses}};
    }
}
vector<dataNS::Budget> Model::GetAllBudgets(){
    dataNS::Budget budget;
    vector<dataNS::Budget> vec;
    vec.push_back(budget);
    return vec;
}

bool Model::CopyBudget(const vector<string> & params){

    // write prettified JSON to another file
    json j;
    dataNS::Expense ex{52, "haha"};
    dataNS::Expense ex2{98.3, "hehe"};
    vector<dataNS::Expense> vec = {ex, ex2};
    dataNS::Category cat{"categ", 800, vec};
    j = cat;
    std::ofstream ofstr("pretty.json");
    ofstr << std::setw(4) << j << std::endl;
    return true;
}
bool Model::SetPrimaryBudget(const vector<string> & params){
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