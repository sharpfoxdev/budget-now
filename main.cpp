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

    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;
}