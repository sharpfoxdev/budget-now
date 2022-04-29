#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "controller.hpp"
#include "view.hpp"

using namespace std;


class CommandLineParser{
public:
    void ParseArgs();
    CommandLineParser(const vector<string> & args);
private:
    using MapType = std::map<string, std::function<void(CommandLineParser &)>>;

    vector<string> args;
    MapType commandMap;
    Controller controller;
    static void SignalUnknownCommand(const string & command);
    static void SignalIncorrectNumberOfArgs();
    static void ParseExpenseParams(CommandLineParser & self);
    static void ParseSetPrimaryParams(CommandLineParser & self);
    static void ParseAddBudgetParams(CommandLineParser & self);
    static void ParseAddCategoryParams(CommandLineParser & self);
    static void ParseAddIncomeParams(CommandLineParser & self);
    static void ParseCopyBudgetParams(CommandLineParser & self);
    static void ParseListParams(CommandLineParser & self);
    static void ParseInfoBudgetParams(CommandLineParser & self);
    static void ParseInfoCategoryParams(CommandLineParser & self);
    static void ParseHelp(CommandLineParser & self);
};

#endif