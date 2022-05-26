#include <string>
#include <vector>
#include <memory>
#include "commandLineParser.hpp"

#include "view.hpp"

using namespace std;

/**
 * @brief 
 * Entry point of the program, passes CLI args into CommandLineParser. 
 * @param argc Number of arguments
 * @param argv CLI arguments
 * @return int 
 */
int main(int argc, char * argv[]) {
    std::ifstream f("howToUse.txt");
    std::unique_ptr<IView> ptr = std::make_unique<HelpView>(f);
    ptr.get()->RenderTo(std::cout);
    std::stringstream sstream;
    ptr.get()->RenderTo(sstream);
    std::cout<<sstream.str();
    f.close();
	return 0;
    /*vector<string> args (argv + 1, argv + argc);
    CommandLineParser parser(args);
    parser.ParseArgs();
    return 0;*/
}