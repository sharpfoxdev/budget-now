#ifndef VIEW_H
#define VIEW_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class IView{
public: 
	virtual ~IView() = default;
    virtual void RenderTo(ostream & stream) = 0;
};

class HelpView final : public IView 
{
private:
    istream & helpSourceStream;
public:
    HelpView(istream & helpSourceStream) : helpSourceStream(helpSourceStream){}
    virtual void RenderTo(ostream & stream) override{
        stream << helpSourceStream.rdbuf();
    }
};
class View{
public:
    void PrintHelp();
    void PrintBudgetsList(dataNS::BudgetsHolder budgets);
    void PrintOperationResult(bool success);
    void PrintBudgetInfo(dataNS::Budget budget);
    void PrintCategoryInfo(dataNS::Category category);
    void PrintSpendingSpeed(dataNS::Category category);
};


#endif