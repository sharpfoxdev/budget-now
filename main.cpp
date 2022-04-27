#include <string>
#include <vector>
#include <iostream>
#include "commandLineParser.hpp"

using namespace std;

int main(int argc, char * argv[]) {
    vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;
}