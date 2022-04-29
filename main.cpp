#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include "commandLineParser.hpp"
#include "date.h"
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace date;
using namespace std::chrono;

/**
 * @brief 
 * Entry point of the program, passes CLI args into CommandLineParser. 
 * @param argc Number of arguments
 * @param argv CLI arguments
 * @return int 
 */
int main(int argc, char * argv[]) {
    /*int x = 2012;
    //auto x = year{x}/1/24;
    int y = 2015;
    int m = 3;
    string d = 20;
    auto today = year_month_day{floor<days>(system_clock::now())};
    cout << today;
    auto x1 = year{y}/m/d;
    if(!x1.ok()){
        cout << "wtf";
        return 0;
    }
    cout <<x1;*/
    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;
}