#ifndef LOG_H
#define LOG_H

#include <string>

namespace log {
    const std::string path = "errors.log";
    bool logError(std::string);
    bool logErrorPrint(std::string);
    
    void glfwErrorCallback(int, const char*);
   
    
    void restartLog();
    
    //void generateLogFileHeader();
    
    // Maybe some day
    //void changePath();
}

#endif