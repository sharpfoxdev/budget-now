#include <gtest/gtest.h>
#include "model.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdio.h>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

void compareTwoFiles(const string & file1, const string & file2){
    stringstream stream1;
    stringstream stream2;
    ifstream f1(file1);
    ifstream f2(file2);
    if(f1.is_open()){
        stream1 << f1.rdbuf();
    }
    if(f2.is_open()){
        stream2 << f2.rdbuf();
    }
    string str1 = stream1.str();
    string str2 = stream2.str();
    ASSERT_EQ(str1, str2);
    f1.close();
    f2.close();
}

class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        //we make copies that we edit with Model
        std::filesystem::copy_file(sourceTestJson, testJson);
    }
    string testJson = "test.json";
    void TearDown() override{
        remove("test.json");
    }
private:
    const string sourceTestJson = "source_test.json";
};

TEST_F(ModelTest, CopyBudgetWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    EXPECT_FALSE(model.get()->CopyBudget(vector<string>{"NotEnoughParams"}));
    EXPECT_FALSE(model.get()->CopyBudget(vector<string>{"Param1", "Param2", "NotADate", "NotADate"}));
    //june is already used
    EXPECT_FALSE(model.get()->CopyBudget(vector<string>{"may22", "june22", "1.6.2022", "30.6.2022"}));
    EXPECT_TRUE(model.get()->CopyBudget(vector<string>{"may22", "july22", "1.6.2022", "30.6.2022"}));
    compareTwoFiles(ModelTest::testJson, "expected_copy_budget.json");
}

TEST_F(ModelTest, SetPrimaryBudgetWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    EXPECT_FALSE(model.get()->SetPrimaryBudget(vector<string>{"NotBudgetName"}));
    EXPECT_TRUE(model.get()->SetPrimaryBudget(vector<string>{"april22"}));
    compareTwoFiles(ModelTest::testJson, "expected_set_primary.json");
}
TEST_F(ModelTest, AddBudgetWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    EXPECT_FALSE(model.get()->AddBudget(vector<string>{"NotEnoughParams"}));
    EXPECT_FALSE(model.get()->AddBudget(vector<string>{"Param1", "NotADate", "NotADate"}));
    //june is already used
    EXPECT_FALSE(model.get()->AddBudget(vector<string>{"june22", "1.6.2022", "30.6.2022"}));
    EXPECT_TRUE(model.get()->AddBudget(vector<string>{"july22", "1.7.2022", "31.7.2022"}));
    compareTwoFiles(ModelTest::testJson, "expected_add_budget.json");
}
TEST_F(ModelTest, AddExpenseWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    EXPECT_FALSE(model.get()->AddExpense(vector<string>{"NotEnoughParams"}));
    //not number passed as amount
    EXPECT_FALSE(model.get()->AddExpense(vector<string>{"food", "notNumber", "comment", "15.5.2022"}));
    EXPECT_FALSE(model.get()->AddExpense(vector<string>{"food", "123", "comment", "notDate"}));
    //date not in range of budget
    EXPECT_FALSE(model.get()->AddExpense(vector<string>{"food", "123", "comment", "15.8.2022"}));
    EXPECT_FALSE(model.get()->AddExpense(vector<string>{"unknownCategory", "123", "comment", "15.5.2022"}));
    EXPECT_TRUE(model.get()->AddExpense(vector<string>{"food", "123", "albert", "15.5.2022"}));
    compareTwoFiles(ModelTest::testJson, "expected_add_expense.json");
}
TEST_F(ModelTest, AddCategoryWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    EXPECT_FALSE(model.get()->AddCategory(vector<string>{"NotEnoughParams"}));
    //not number passed as amount
    EXPECT_FALSE(model.get()->AddCategory(vector<string>{"travel", "notNumber"}));
    //already used category
    EXPECT_FALSE(model.get()->AddCategory(vector<string>{"food", "123"}));
    EXPECT_TRUE(model.get()->AddCategory(vector<string>{"travel", "123"}));
    compareTwoFiles(ModelTest::testJson, "expected_add_category.json");
}
TEST_F(ModelTest, AddIncomeWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ModelTest::testJson);
    //not enough params
    EXPECT_FALSE(model.get()->AddIncome(vector<string>{}));
    //not number passed as amount
    EXPECT_FALSE(model.get()->AddIncome(vector<string>{"notNumber"}));
    //already used category
    EXPECT_TRUE(model.get()->AddIncome(vector<string>{"1234", "paycheck"}));
    compareTwoFiles(ModelTest::testJson, "expected_add_income.json");
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}