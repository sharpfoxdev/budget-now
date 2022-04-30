#include <string>
#include <vector>
#include "commandLineParser.hpp"

using namespace std;

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