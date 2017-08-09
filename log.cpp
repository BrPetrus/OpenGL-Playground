#include "log.h"

#include <fstream>
#include <iostream>
#include <ctime>

namespace logTools {
    /**
     * @brief Prints message to log file
     * @param message This is printed to log
     */
    bool logError(std::string message) {
        std::ofstream file;
        file.open("error.log", std::ios::app);
        if(!file.is_open()) {
           std::cerr << "[LOG ERROR] Log file cannot be created.\n";
           return false;
        }
        
        time_t now = time(nullptr);
        std::string date = ctime(&now);
        date.erase(date.end() - 1);
        file << "(" << date << ") " << message <<  std::endl;
        
        file.close();
        return true;
    }
    
    bool logErrorPrint(std::string message) {
        time_t now = time(nullptr);
        std::string date = ctime(&now);
        date.erase(date.end() - 1);
        std::cerr << "(" << date << ") " << message <<  std::endl;
        return logError(message);
    }
    
    void glfwErrorCallback(int code, const char* description) {
        std::string d = "[GLFW ERROR] code: " + code;
        d += " msg: ";
        d += description;
        d += + "\n";
        logError(d);
    }
    
    void restartLog() {
        std::ofstream file;
        file.open("error.log");
        file.close();
    }
    
    /*bool generateLogFileHeader() {
        std::ofstream file;
        file.open(path);
        if(!file.is_open()) {
           std::cerr << "[LOG ERROR] Cannot generate header.\n";
           return false;
        }
    }*/
}