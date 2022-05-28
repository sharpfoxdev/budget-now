#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "controller.hpp"
#include "model.hpp"
#include "dataClasses.hpp"
#include "view.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdio.h>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;
using ::testing::AtLeast; 


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
    shared_ptr<MockModel> mockModel1 = make_shared<MockModel>();
    shared_ptr<MockModel> mockModel2 = make_shared<MockModel>();
    shared_ptr<MockModel> mockModel3 = make_shared<MockModel>();

    shared_ptr<IController> controller = it->second;
    string command = args[0];
    args.erase(args.begin());
    return controller.get()->HandleRequest(command, args);
}

TEST(CallingModel, ExpenseControllerWorks) {
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
TEST(CallingModel, CategoryControllerWorks) {
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

TEST(CallingModel, IncomeControllerWorks) {
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


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}