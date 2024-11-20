#include <iostream>
#include <boost/program_options.hpp>
#include "include/order_manager.h"

namespace po = boost::program_options;

void startMainProgram() {
    // create order book manager
    OrderManager orderManager;
    // read from input file
    orderManager.readFromInputFile("./tests/sample_input.txt");

}

int main(int argc, char* argv[]) {
    // Define the options
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "Show help message")
            ("start, s", "Start the program");

    // Variable map to store the parsed options
    po::variables_map vm;

    try {
        // Parse the command-line arguments
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm); // Notify to enforce required options and defaults

        // Display help if the "help" option is present
        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 0;
        }

        // Access the "compression" option
        if (vm.count("start")) {
            std::cout << "====== Match Engine =====\n\n";
            startMainProgram();
        }

    } catch (const po::error& e) {
        // Handle errors in parsing
        std::cerr << "Error: " << e.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }
}
