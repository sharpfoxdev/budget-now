# Budget now

Project for NPRG041 Programming in C++ at faculty of Mathematics and Physics of Charles university. 

CLI budgeting application to track incomes and expenses.

# Build instructions

In the project folder, there is suplied CMakeLists.txt. To build the project simply run
```cmake CMakeLists.txt``` and then ```make```, which should build all source code files into executable budgetApp, which you can then run. 

# How to use

The program offers several commands, that can also be found in ```howToUse.txt``` file. You can also get a list of available commands by running ```./budgetApp --help```. 

Incomes and expenses cannot be removed but you can add negative income or expense, to nullify incorrectly entered value. 

## Examples


# Code architecture and design decisions

The code architecture is based on Model-View-Controller design pattern with commandLineParser, that parses initial commands from CLI. 

Firstly the arguments are sent from main.cpp into `CommandLineParser`. It contains map between available commands and respective member functions, that can handle them. There we get only command parameters from args and these parameter then get passed further into `Controller` in appropriate member function, that further handled them. 

Lots of member functions in `CommandLineParser` are static yet they take an instance of `CommandLineParser` as their parameter, which can look a bit odd. It is because the map between commands and member functions utilizes `std::function` which works better with static functions yet I needed to access members of the `CommandLineParser` instance, so in the end I decided to use static member functions with `CommandLineParser` instance as a function parameter to meet these two requirements. 

After arguments are parser into just command parameters, they are parsed into appropriate function on `Controller`. Controller holds instances of `View` and `Model`. Firstly it calls `Model` to store/retrieve data and passes command arguments to it and then calls `View` to display results to the user on CLI. 

`Model` is the core of the application as it handles logic of data. It utilizes json.hpp https://github.com/nlohmann/json library and structures from `dataNS` namespace, that encapsulates structures `Expense`, `Income`, `Category`, `Budget` and `BudgetsHolder` as well as respective functions, to convert these structures to and from json. These functions get called by the json.hpp library and thats the reason, they have to be in a namespace together with the structures, otherwise there is a naming overlap. 

`Budget` structure holds vector of `Incomes` (these are unnamed) and a map between name of category and `Category` object.

`Category` structure holds vector of `Expenses`, that are unnamed (same like `Incomes`). 

`BudgetsHolder` holds map between names of budgets and respective `Budget` object. It also separately holds name and object of primary budget. That is because the aim of the application is to make the CLI commands as short as possible for the user (because who likes typing long commands), so the user sets one primary budget (for example a budget for a month) and then uses it without really switching to other budgets. So he sets up one primary budget, that is accessed a lot, so I wanted to make even the access on code level simple, so I took it out of the name-budget map in `BudgetsHolder` and gave it it's own variables. 

So from the data structures, only `Budget` and `Category` can be accessed by names, that also act as keys, so they should be unique.  

`Model` TODO

`View` then offers various member functions to display results on CLI from `Model` and it can print help text. 