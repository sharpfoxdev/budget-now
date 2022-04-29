#include "view.hpp"

void View::PrintHelp(){
    cout << "Printing help from view. " << endl;
}
void View::PrintOperationResult( bool success){
    if(success){
        cout << "Operation Successful. " << endl;
    }
    else{
        cout << "Operation unsuccessful, please repeat the operation. " << endl;
    }
}
void View::PrintBudgetInfo(dataNS::Budget budget){

}
void View::PrintCategoryInfo(dataNS::Category category){

}
void View::PrintBudgetsList(dataNS::BudgetsHolder budgets){
    if(budgets.primaryBudgetName == "" && budgets.otherBudgets.size() == 0){
        cout << "No budgets specified. " << endl;
    }
    else{
        cout << budgets.primaryBudgetName << " - primary budget" << endl;
        for ( const auto &myPair : budgets.otherBudgets ) {
            std::cout << myPair.first << endl;
        }
    }
}

