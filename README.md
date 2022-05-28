# Budget now

Project for NPRG041 Programming in C++ at faculty of Mathematics and Physics of Charles university. 

CLI budgeting application to track incomes and expenses within categories. 

# Build instructions

In the project folder, there is suplied CMakeLists.txt. To build the project simply run
```cmake CMakeLists.txt``` and then ```make```, which should build all source code files into executable budgetApp, which you can then run. I recommend using at least C++17 to build successfully. 

## Tests
To run tests build the project (see above) and then use following commands. 
```
cd tests
./testmodel 
./testcontroller
./testview
```

# How to use

The program offers several commands, that can also be found in ```howToUse.txt``` file, further description is bellow in Examples. You can also get a list of available commands by running ```./budgetApp --help```. 

Incomes and expenses cannot be removed but you can add negative income or expense, to nullify incorrectly entered value. 

Life hack: if you don't want to type every command and want to use autocompletion, you can move files from `commands` folder into the `budget-now` folder where is the `budgetApp` executeble. These files have the same names as the CLI commands used by the app, so you can use tab autocompletion that most terminals offer (as it detects file with the given name and fills it for you). 

## Examples
### Adding new budgets
First start with adding new budgets:

```
./budgetApp add_budget april22 1.4.2022 30.04.2022
./budgetApp add_budget may22 1.5.2022 31.05.2022
```
This will create the two budgets with names `april22` and `may22` and the first one becomes primary budget. Note that the names has to be unique. Start and end dates can be in both formats `dd.mm.yyyy` and `d.m.yyyy`. 

```
./budgetApp set_primary may22
```
### Changing primary budget
If you want to change primary budget from `april22` to `may22`, run:

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
This will create category `food` and budget 5000 to it (amount we want to spend in this category). The name of category has to be unique within budget. 

### Adding expense to category
To add expense in given category in primary budget run:
```
./budgetApp expense food 200 tesco 2.5.2022
```
This will add expense of 200 in `food` category with comment `tesco`. If date is not specified, todays date will be assumed. But be aware, that the date has to be within budget date range. The app will also inform you, how fast or slow you are spending your budget. 

### Printing information about budget
To print basic information and statistics about given budget, run:
```
./budgetApp info_budget may22
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
./budgetApp copy_budget may22 june22 1.6.2022 30.6.2022
```
This will create new budget june22 and copy all categories and budgeted amounts within them into the new budget. All you have to do now is switch primary budget from `may22` to `june22`, add income and you are ready to add expenses when you need to. 

# Code architecture and design decisions

The code architecture is based on Model-View-Controller design pattern with helper `DateManager` class, that handles dates. 

## Code flow
Firstly the arguments are sent from `main.cpp` into `MasterController`. It contains map between available commands and controllers (instances implementing `IController`), that handle them. Based on the command recieved on the CLI, `MasterController` then calls appropriate controler, who handles the command by updating/retrieving data from the model. After the request is executed, controller returns appropriate instance of `IView`, that can display result of the operation on the model or the retrieved data. This view instance is then propagated up through `MasterController` to the `main.cpp`, where there is called method on the view, that renders the result to the user. 

## Info about classes
`Model` is the core of the application as it handles logic of data, its storing and retrieving. It utilizes json.hpp https://github.com/nlohmann/json library and structures from `dataNS` namespace, that encapsulates structures `DateStruct`, `Expense`, `Income`, `Category`, `Budget` and `BudgetsHolder` as well as respective functions, to convert these structures to and from json. These functions get called by the json.hpp library and thats the reason, they have to be in a namespace together with the structures, otherwise there is a naming overlap. 

`Budget` structure holds vector of `Incomes` (these are unnamed) and a map between name of category and `Category` object.

`Category` structure holds vector of `Expenses`, that are unnamed (same like `Incomes`). 

`BudgetsHolder` holds map between names of budgets and respective `Budget` object. It also separately holds name and object of primary budget. That is because the aim of the application is to make the CLI commands as short as possible for the user (because who likes typing long commands), so the user sets one primary budget (for example a budget for a month) and then uses it without really switching to other budgets. So he sets up one primary budget, that is accessed a lot, so I wanted to make even the access on code level simple, so I took it out of the name-budget map in `BudgetsHolder` and gave it it's own variables. 

So from the data structures, only `Budget` and `Category` can be accessed by names, that also act as keys, so they should be unique.  

`Model` closely works with `DateManager`. This class handles anything that has to do with dates - parsing dates, getting current dates, more complex comparing. One of the functions also can take start and end of the budget, expense date and its category and compute how fast the user is spending their budget and advide them to slow down, if they spend too quickly. 

`DateManager` works primarily with two types of objects: `DataStruct` from `dataNS` namespace, which is used for storing in json and passing around in the program, and year_month_day class from `date.h` library (https://github.com/HowardHinnant/date), which is used for computations over dates. `DateManager` can also freely tansfer between these types.  

## Interfaces
All three, model, views and controllers are wrapped into interfaces (IModel, IView, IController). This allows for better code division into specialised views and controllers and forces these classes to interact with each other through these interfaces (which have very few methods for IView and IController) without worrying, what exact implementation will handle the request. Using interfaces also helped with testing, as I could swap instances for mock instances for checking, that modules interact correctly. 