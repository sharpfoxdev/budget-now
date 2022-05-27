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
    IView() = default;
	IView(const IView &base) = default;
	IView(IView &&base) = default;

	IView &operator =(const IView &base) = default;
	IView &operator =(IView &&base) = default;

	virtual ~IView() = default;
    virtual void RenderTo(ostream & stream) = 0;
};

class HelpView final : public IView 
{
private:
    string pathHelpFile;
public:
    HelpView(string pathHelpFile) : pathHelpFile(pathHelpFile) {}
    virtual void RenderTo(ostream & stream) override;
};

class BudgetsListView final : public IView 
{
private:
    dataNS::BudgetsHolder budgets;
    string modelMessage;
public:
    BudgetsListView(dataNS::BudgetsHolder budgets, string modelMessage) : budgets(budgets), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

class OperationResultView final : public IView 
{
private:
    bool success;
    string modelMessage;
public:
    OperationResultView(bool success, string modelMessage) : success(success), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

class BudgetInfoView final : public IView 
{
private:
    dataNS::Budget budget;
    string modelMessage;
public:
    BudgetInfoView(dataNS::Budget budget, string modelMessage) : budget(budget), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

class CategoryInfoView final : public IView 
{
private:
    dataNS::Category category;
    string modelMessage;
public:
    CategoryInfoView(dataNS::Category category, string modelMessage) : category(category), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

class MessageView final : public IView 
{
private:
    string message;
    string modelMessage;
public:
    MessageView(string message, string modelMessage) : message(message), modelMessage(modelMessage) {}
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