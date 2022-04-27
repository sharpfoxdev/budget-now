#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "controller.hpp"

using namespace std;

using MapType = std::map<string, std::function<void()>>;

class CommandLineParser{
public:
    void ParseArgs();
    CommandLineParser(const vector<string> & args);
private:
    vector<string> args;
    MapType commandMap;
    Controller controller;
    static void SignalUnknownCommand(const string & command);
    static void SignalIncorrectNumberOfArgs();
    static void ParseExpenseParams();
    static void ParseSetPrimaryParams();
    static void ParseAddBudgetParams();
    static void ParseAddCategoryParams();
    static void ParseAddIncomeParams();
    static void ParseCopyBudgetParams();
    static void ParseListParams();
    static void ParseInfoBudgetParams();
    static void ParseInfoCategoryParams();
    static void ParseHelp();
};

#endif