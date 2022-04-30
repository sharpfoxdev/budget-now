# Budget now

Project for NPRG041 Programming in C++ at faculty of Mathematics and Physics of Charles university. 

CLI budgeting application to track incomes and expenses.

# Build instructions

In the project folder, there is suplied CMakeLists.txt. To build the project simply run
```cmake CMakeLists.txt``` and then ```make```, which should build all source code files into executable budgetApp, which you can then run. 

# How to use

The program offers several commands, that can also be found in ```howToUse.txt``` file, further description is bellow in Examples. You can also get a list of available commands by running ```./budgetApp --help```. 

Incomes and expenses cannot be removed but you can add negative income or expense, to nullify incorrectly entered value. 

Life hack: if you don't want to type every command and want to use autocompletion, you can move files from `commands` folder into the `budget-now` folder where is the `budgetApp` executeble. These files have the same names as the CLI commands used by the app, so you can use tab autocompletion that most terminals offer (as it detects file with the given name and fills it for you). 

## Examples
### Adding new budgets
First start with adding new budgets:

```
./budgetApp add_budget jan22
./budgetApp add_budget feb22
```
This will create the two budgets with names `jan22` and `feb22` and the first one becomes primary budget. Note that the names has to be unique.  

```
./budgetApp set_primary feb22
```
### Changing primary budget
If you want to change primary budget from `jan22` to `feb22`, run:

### Listing all budgets
To list all available budgets, run:
```
./budgetApp list
```
This will also tell you, which budget is primary. 

### Adding income into primary budget
To add income to the primary budget run:
```
./budgetApp add_income 20000 paycheck
./budgetApp add_income 5000 gift
```
This will add two incomes into the primary budget. The `paycheck` and `gift` comments are not mandatory. 

### Adding category to the primary budget
To add category to the primary budget run:
```
./budgetApp add_category food 5000
./budgetApp add_category accomodation 6000
```
This will create category `food` and budgest 5000 to it (amount we want to spend in this category). The name of category has to be unique within budget. 

### Adding expense to category
To add expense in given category in primary budget run:
```
./budgetApp expense food 200 tesco
```
This will add expense of 200 in `food` category with comment `tesco`. Comment is not mandatory. 

### Printing information about budget
To print basic information and statistics about given budget, run:
```
./budgetApp info_budget feb22
```
This will print all the categories within budget, spent, budgeted and left to spend amounts within them and total income, expenses, budgeted and left to budget amounts within the whole budget. 

If you omit name of budget, it will print information about primary budget. 

### Print information about category in primary budget
If you want to see what expenses you had within category, run:
```
./budgetApp info_category food
```
This will print information about category and all expenses within.

### Create copy of budget
If you spend same amount of money every budget and don't want to create new budget and new categories every time, you can run 
```
./budgetApp copy_budget march22 feb22
```
This will create new budget march22 and copy all categories and budgeted amounts within them into the new budget. All you have to do now is switch primary budget from `feb22` to `march22`, add income and you are ready to add expenses when you need to. 

# Code architecture and design decisions

The code architecture is based on Model-View-Controller design pattern with commandLineParser, that parses initial commands from CLI. 

Firstly the arguments are sent from main.cpp into `CommandLineParser`. It contains map between available commands and respective member functions, that can handle them. There we get only command parameters from args and these parameters then get passed further into `Controller` in appropriate member function, that further handles them. 

Lots of member functions in `CommandLineParser` are static yet they take an instance of `CommandLineParser` as their parameter, which can look a bit odd. It is because the map between commands and member functions utilizes `std::function` which works better with static functions, yet I needed to access members of the `CommandLineParser` instance, so in the end I decided to use static member functions with `CommandLineParser` instance as a function parameter to meet these two requirements. 

After arguments are parser into just command parameters, they are passed into appropriate function in `Controller`. Controller holds instances of `View` and `Model`. Firstly it calls `Model` to store/retrieve data and passes command arguments to it and then calls `View` to display results to the user on CLI. 

`Model` is the core of the application as it handles logic of data, its storing and retrieving. It utilizes json.hpp https://github.com/nlohmann/json library and structures from `dataNS` namespace, that encapsulates structures `Expense`, `Income`, `Category`, `Budget` and `BudgetsHolder` as well as respective functions, to convert these structures to and from json. These functions get called by the json.hpp library and thats the reason, they have to be in a namespace together with the structures, otherwise there is a naming overlap. 

`Budget` structure holds vector of `Incomes` (these are unnamed) and a map between name of category and `Category` object.

`Category` structure holds vector of `Expenses`, that are unnamed (same like `Incomes`). 

`BudgetsHolder` holds map between names of budgets and respective `Budget` object. It also separately holds name and object of primary budget. That is because the aim of the application is to make the CLI commands as short as possible for the user (because who likes typing long commands), so the user sets one primary budget (for example a budget for a month) and then uses it without really switching to other budgets. So he sets up one primary budget, that is accessed a lot, so I wanted to make even the access on code level simple, so I took it out of the name-budget map in `BudgetsHolder` and gave it it's own variables. 

So from the data structures, only `Budget` and `Category` can be accessed by names, that also act as keys, so they should be unique.  

`View` then offers various member functions to display results on CLI from `Model` and it can print help text. 