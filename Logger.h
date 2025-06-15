#ifndef LOGGER_H
#define LOGGER_H
#include "MyString.h"
#include <fstream>
using namespace std;
class Logger {
public:
     Logger(const MyString& logFilePath);

    ~Logger();
    void logEvent(const MyString& msg);

    void logError(const MyString& msg);

private:
    ofstream out;
    MyString currentTimestamp() const;
};

#endif