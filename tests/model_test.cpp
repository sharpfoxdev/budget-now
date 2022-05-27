#include <gtest/gtest.h>
#include "model.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <stdio.h>

using namespace std;

class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        //we make copies that we edit with Model
        std::filesystem::copy_file(sourceTestJson, testJson);
        std::filesystem::copy_file(sourceEmptyJson, emptyJson);
    }
    string emptyJson = "empty.json";
    string testJson = "test.json";
    void TearDown(){
        remove("empty.json");
        remove("test.json");
    }
  // void TearDown() override {}
private:
    const string sourceTestJson = "source_test.json";
    const string sourceEmptyJson = "source_empty.json";
};

TEST_F(ModelTest, CopyBudgetWorks) {
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
TEST_F(ModelTest, SetPrimaryBudgetWorks) {
  
}
TEST_F(ModelTest, AddBudgetWorks) {

}
TEST_F(ModelTest, AddExpenseWorks) {

}
TEST_F(ModelTest, AddCategoryWorks) {

}
TEST_F(ModelTest, AddIncomeWorks) {

}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}