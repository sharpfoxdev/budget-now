#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "controller.hpp"
#include "model.hpp"
#include "dataClasses.hpp"
#include "view.hpp"
#include <string>
#include <vector>
#include <memory>

using namespace std;
using ::testing::AtLeast;
using ::testing::InSequence;

class MockSubController : public IController {
    public:
    MOCK_METHOD(unique_ptr<IView>, HandleRequest, (string command, const vector<string> & params), (override));
};

class MockModel : public IModel{
    public:
    MOCK_METHOD(dataNS::BudgetsHolder, GetBudgetsHolder, (), (override));
    MOCK_METHOD(bool, CopyBudget, (const vector<string> & params), (override));
    MOCK_METHOD(bool, SetPrimaryBudget, (const vector<string> & params), (override));
    MOCK_METHOD(bool, AddBudget, (const vector<string> & params), (override));
    MOCK_METHOD(bool, AddExpense, (const vector<string> & params), (override));
    MOCK_METHOD(bool, AddCategory, (const vector<string> & params), (override));
    MOCK_METHOD(bool, AddIncome, (const vector<string> & params), (override));
    MOCK_METHOD(dataNS::Budget, GetBudget, (const vector<string> & params), (override));
    MOCK_METHOD(dataNS::Category, GetCategory, (const vector<string> & params), (override));
    MOCK_METHOD(string, GetMessage, (), (override));
};

TEST(CallingSubController, MasterControllerWorks) {
    shared_ptr<MockSubController> mockSubController = make_shared<MockSubController>();
    map<string, shared_ptr<IController>> commandControllerMap = {
        { "test_command", mockSubController},
    };
    vector<string> args{"test_command", "param1", "param2"};

    vector<string> expectedParams{"param1", "param2"};
    EXPECT_CALL(*mockSubController, HandleRequest("test_command", expectedParams));

    MasterController masterContr(commandControllerMap);
    //this should call HandleRequest on mockSubController
    masterContr.ExecuteRequest(args); 
}
TEST(CallingModel, BudgetControllerWorks) {
    shared_ptr<MockModel> mockModel = make_shared<MockModel>();
    unique_ptr<IController> controller = make_unique<BudgetController>(mockModel);

    {
        //we expect that methods on mockModel will be called in this order
        InSequence s;
        EXPECT_CALL(*mockModel, GetBudgetsHolder());
        EXPECT_CALL(*mockModel, AddBudget(vector<string>{"param1", "param2"}));
        EXPECT_CALL(*mockModel, CopyBudget(vector<string>{"param1", "param2"}));
        EXPECT_CALL(*mockModel, SetPrimaryBudget(vector<string>{"param1", "param2"}));
        EXPECT_CALL(*mockModel, GetBudget(vector<string>{"param1", "param2"}));
    }
    EXPECT_CALL(*mockModel, GetMessage()).Times(AtLeast(1));
    controller.get()->HandleRequest("list", vector<string>{"param1", "param2"});
    controller.get()->HandleRequest("add_budget", vector<string>{"param1", "param2"});
    controller.get()->HandleRequest("copy_budget", vector<string>{"param1", "param2"});
    controller.get()->HandleRequest("set_primary", vector<string>{"param1", "param2"});
    controller.get()->HandleRequest("info_budget", vector<string>{"param1", "param2"});
}

TEST(CallingModel, ExpenseControllerWorks) {
    shared_ptr<MockModel> mockModel = make_shared<MockModel>();
    unique_ptr<IController> controller = make_unique<ExpenseController>(mockModel);
    {
        //we expect that methods on mockModel will be called in this order
        InSequence s;
        EXPECT_CALL(*mockModel, AddExpense(vector<string>{"param1", "param2"}));
    }
    EXPECT_CALL(*mockModel, GetMessage()).Times(AtLeast(1));;
    controller.get()->HandleRequest("expense", vector<string>{"param1", "param2"});
}
TEST(CallingModel, CategoryControllerWorks) {
    shared_ptr<MockModel> mockModel = make_shared<MockModel>();
    unique_ptr<IController> controller = make_unique<CategoryController>(mockModel);
    {
        //we expect that methods on mockModel will be called in this order
        InSequence s;
        EXPECT_CALL(*mockModel, GetCategory(vector<string>{"param1", "param2"}));
        EXPECT_CALL(*mockModel, AddCategory(vector<string>{"param1", "param2"}));
    }
    EXPECT_CALL(*mockModel, GetMessage()).Times(AtLeast(1));;
    controller.get()->HandleRequest("info_category", vector<string>{"param1", "param2"});
    controller.get()->HandleRequest("add_category", vector<string>{"param1", "param2"});
}

TEST(CallingModel, IncomeControllerWorks) {
    shared_ptr<MockModel> mockModel = make_shared<MockModel>();
    unique_ptr<IController> controller = make_unique<IncomeController>(mockModel);
    {
        //we expect that methods on mockModel will be called in this order
        InSequence s;
        EXPECT_CALL(*mockModel, AddIncome(vector<string>{"param1", "param2"}));
    }
    EXPECT_CALL(*mockModel, GetMessage()).Times(AtLeast(1));;
    controller.get()->HandleRequest("add_income", vector<string>{"param1", "param2"});
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}