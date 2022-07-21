#include <gtest/gtest.h>
#include "model.hpp"
#include "view.hpp"
#include "dataClasses.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdio.h>
#include <vector>
#include <memory>

using namespace std;

void compareFileAndString(const string & file, const string & stringIn){
    stringstream stream1;
    ifstream f1(file);
    if(f1.is_open()){
        stream1 << f1.rdbuf();
    }

    string str1 = stream1.str();
    ASSERT_EQ(str1, stringIn);
    f1.close();
}

class ViewTest : public ::testing::Test {
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

TEST_F(ViewTest, HelpViewWorks) {
    stringstream stream1;
    ifstream f1("source_helptext.txt");
    if(f1.is_open()){
        stream1 << f1.rdbuf();
    }
    string str1 = stream1.str();
    string str2 = "help text";
    ASSERT_EQ(str1, str2);
    f1.close();
    /*ifstream f(ModelTest::emptyJson);
    stringstream ss;
    if (f.is_open()){
        ss << f.rdbuf();
    }
    string s = ss.str();
    EXPECT_EQ(s, "hello");
    f.close();
    ofstream fi(ModelTest::emptyJson);
    fi << "jop";
    fi.close();*/  
}

TEST_F(ViewTest, BudgetsListViewWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ViewTest::testJson);
    dataNS::BudgetsHolder budgets = model.get()->GetBudgetsHolder();
    unique_ptr<IView> view = make_unique<BudgetsListView>(budgets, model.get()->GetMessage());
    stringstream ss;
    view.get()->RenderTo(ss);
    string str = ss.str();
    compareFileAndString("expected_print_list.txt", str);
}
TEST_F(ViewTest, OperationResultViewWorks) {
    unique_ptr<IView> viewTrue = make_unique<OperationResultView>(true, "");
    stringstream ssTrue;
    viewTrue.get()->RenderTo(ssTrue);
    string strTrue = ssTrue.str();
    ASSERT_EQ(strTrue, "Operation Successful. \n");

    unique_ptr<IView> viewFalse = make_unique<OperationResultView>(false, "");
    stringstream ssFalse;
    viewFalse.get()->RenderTo(ssFalse);
    string strFalse = ssFalse.str();
    ASSERT_EQ(strFalse, "Operation unsuccessful, please repeat the operation. \n");
}
TEST_F(ViewTest, BudgetInfoViewWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ViewTest::testJson);
    dataNS::Budget budget = model.get()->GetBudget(vector<string>{"may22"});
    unique_ptr<IView> view = make_unique<BudgetInfoView>(budget, model.get()->GetMessage());
    stringstream ss;
    view.get()->RenderTo(ss);
    string str = ss.str();
    compareFileAndString("expected_print_budget.txt", str);
}
TEST_F(ViewTest, CategoryInfoViewWorks) {
    unique_ptr<IModel> model = make_unique<Model>(ViewTest::testJson);
    dataNS::Category category = model.get()->GetCategory(vector<string>{"food"});
    unique_ptr<IView> view = make_unique<CategoryInfoView>(category, model.get()->GetMessage());
    stringstream ss;
    view.get()->RenderTo(ss);
    string str = ss.str();
    compareFileAndString("expected_print_category.txt", str);
}
TEST_F(ViewTest, MessageViewWorks) {
    unique_ptr<IView> viewTrue = make_unique<MessageView>("message", "");
    stringstream ssTrue;
    viewTrue.get()->RenderTo(ssTrue);
    string strTrue = ssTrue.str();
    ASSERT_EQ(strTrue, "message\n");
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}