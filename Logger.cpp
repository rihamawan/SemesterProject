#include "Logger.h"
#include "GameException.h"    
#include <ctime>
using namespace std;
Logger::Logger(const MyString& logFilePath) : out(logFilePath.returnArray(), std::ios::app)
{
    if (!out) {
        throw FileIOException(MyString("Unable to open log file: ").concat( logFilePath));
    }
}

Logger::~Logger() {
    if (out.is_open()) out.close();
}

//MyString Logger::currentTimestamp() const {
//   time_t t = time(nullptr);
//   tm* tm = localtime(&t);
//    char arr[20];
//    strftime(arr, sizeof(arr), "%Y-%m-%d %H:%M:%S", tm);
//    return MyString(arr);
//}

MyString Logger::currentTimestamp() const {
   time_t t = time(nullptr);

    tm timeInfo;
    localtime_s(&timeInfo, &t);

    char buf[20];
   strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return MyString(buf);
}


void Logger::logEvent(const MyString& msg) {
    out << "[" << currentTimestamp() << "] [INFO]  " << msg << "\n";
    out.flush();
}

void Logger::logError(const MyString& msg) {
    out << "[" << currentTimestamp() << "] [ERROR] " << msg << "\n";
    out.flush();
}
