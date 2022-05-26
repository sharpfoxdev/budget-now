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
    virtual void RenderTo(ostream & stream) override;
};

class BudgetsListView final : public IView 
{
private:
    dataNS::BudgetsHolder budgets;
public:
    BudgetsListView(dataNS::BudgetsHolder budgets) : budgets(budgets){}
    virtual void RenderTo(ostream & stream) override;
};

class OperationResultView final : public IView 
{
private:
    bool success;
public:
    OperationResultView(bool success) : success(success){}
    virtual void RenderTo(ostream & stream) override;
};

class BudgetInfoView final : public IView 
{
private:
    dataNS::Budget budget;
public:
    BudgetInfoView(dataNS::Budget budget) : budget(budget){}
    virtual void RenderTo(ostream & stream) override;
};

class CategoryInfoView final : public IView 
{
private:
    dataNS::Category category;
public:
    CategoryInfoView(dataNS::Category category) : category(category){}
    virtual void RenderTo(ostream & stream) override;
};

class MessageView final : public IView 
{
private:
    const string & message;
public:
    MessageView(const string & message) : message(message){}
    virtual void RenderTo(ostream & stream) override;
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