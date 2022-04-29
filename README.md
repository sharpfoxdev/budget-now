# Budget now

Project for NPRG041 Programming in C++ at faculty of Mathematics and Physics of Charles university. 

CLI budgeting application to track incomes and expenses.

# Build instructions

In the project folder, there is suplied CMakeLists.txt. To build the project simply run
```cmake CMakeLists.txt``` and then ```make```, which should build all source code files into executable budgetApp, which you can then run. 

# How to use

The program offers several commands, that can also be found in ```howToUse.txt``` file. You can also get a list of available commands by running ```./budgetApp --help```. 

## Examples


# Code architecture and design decisions

The code architecture is based on Model-View-Controller design pattern with commandLineParser, that parses initial commands from CLI. 

Firstly the arguments are sent from main.cpp into `CommandLineParser`. It contains map between available commands and respective member functions, that can handle them. There we get only command parameters from args and these parameter then get passed further into `Controller` in appropriate member function, that further handled them. 

Lots of member functions in `CommandLineParser` are static yet they take an instance of `CommandLineParser` as their parameter, which can look a bit odd. It is because the map between commands and member functions utilizes `std::function` which works better with static functions yet I needed to access members of the `CommandLineParser` instance, so in the end I decided to use static member functions with `CommandLineParser` instance as a function parameter to meet these two requirements. 