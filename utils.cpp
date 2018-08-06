#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class Utils {
    public:

    void save_to_file(std::string fileName, std::string content) {
        std::ofstream outfile;
        outfile.open(fileName, std::ios_base::app);
        outfile << content;
    }

    std::string create_log_format(std::string message) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S ");
        auto str = oss.str() + message + "\n";
        return str;
    }
};