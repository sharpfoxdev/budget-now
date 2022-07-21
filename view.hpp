#ifndef VIEW_H
#define VIEW_H

#include "dataClasses.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief Interface for view, an object, that can display data to the user
 * 
 */
class IView{
public: 
    IView() = default;
	IView(const IView &base) = default;
	IView(IView &&base) = default;

	IView &operator =(const IView &base) = default;
	IView &operator =(IView &&base) = default;

	virtual ~IView() = default;
    /**
     * @brief Renders data to the specified stream. 
     * @param stream 
     */
    virtual void RenderTo(ostream & stream) = 0;
};

/**
 * @brief Implementation of IView, handles displaying help text
 */
class HelpView final : public IView 
{
private:
    string pathHelpFile;
public:
    HelpView(string pathHelpFile) : pathHelpFile(pathHelpFile) {}
    virtual void RenderTo(ostream & stream) override;
};

/**
 * @brief Implementation of IView, handles displaying list of budgets
 */
class BudgetsListView final : public IView 
{
private:
    dataNS::BudgetsHolder budgets;
    string modelMessage;
public:
    BudgetsListView(dataNS::BudgetsHolder budgets, string modelMessage) : budgets(budgets), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

/**
 * @brief Implementation of IView, handles displaying whether an operation was successful or not
 */
class OperationResultView final : public IView 
{
private:
    bool success;
    string modelMessage;
public:
    OperationResultView(bool success, string modelMessage) : success(success), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

/**
 * @brief Implementation of IView, handles displaying information about budget
 */
class BudgetInfoView final : public IView 
{
private:
    dataNS::Budget budget;
    string modelMessage;
public:
    BudgetInfoView(dataNS::Budget budget, string modelMessage) : budget(budget), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

/**
 * @brief Implementation of IView, handles displaying information about category
 */
class CategoryInfoView final : public IView 
{
private:
    dataNS::Category category;
    string modelMessage;
public:
    CategoryInfoView(dataNS::Category category, string modelMessage) : category(category), modelMessage(modelMessage){}
    virtual void RenderTo(ostream & stream) override;
};

/**
 * @brief Implementation of IView, handles displaying given message to the user
 */
class MessageView final : public IView 
{
private:
    string message;
    string modelMessage;
public:
    MessageView(string message, string modelMessage) : message(message), modelMessage(modelMessage) {}
    virtual void RenderTo(ostream & stream) override;
};

#endif