//
// Created by artef on 03.05.2017.
//

#ifndef PLAYIN_LOGGER_H
#define PLAYIN_LOGGER_H

#include <string>
#include <stack>
#include <fstream>
#include <time.h>
#include <utils/glutUtils.h>

class Logger {
private:
    static bool log_info;
    static bool log_warnings;
    static bool log_errors;

    static std::ostream &log;
    static std::ofstream logf;


    static void print(std::ostream &s) {
        s << std::endl;
    }

    template<typename T, typename ...TAIL>
    static void print(std::ostream &s, const T &t, TAIL... tail) {
        s << t << ' ';
        print(s, tail...);
    }

public:

    Logger() {

    }

    template<typename ...TAIL>
    static void warning(TAIL... tail) {

        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);

        log << "WARNING " << buffer << ": ";
        print(log, tail...);

        logf << "WARNING " << buffer << ": ";
        print(logf, tail...);
    }

    template<typename ...TAIL>
    static void error(TAIL... tail) {

        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);

        log << "ERROR " << buffer << ": ";
        print(log, tail...);

        logf << "ERROR " << buffer << ": ";
        print(logf, tail...);
    }

    template<typename ...TAIL>
    static void info(TAIL... tail) {

        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);

        log << "INFO " << buffer << ": ";
        print(log, tail...);

        logf << "INFO " << buffer << ": ";
        print(logf, tail...);
    }


    static void setLogStream(std::ostream &stream) {

    }

    static void logFile(std::string filename) {
        if (logf.is_open()) {
            logf.close();
        }
        logf.open(filename.c_str(), std::ios::out);
    }

    static void setLogInfo(bool should_log_info) {
        log_info = should_log_info;
    }

    static void setLogWarnings(bool should_log_warnings) {
        log_warnings = should_log_warnings;
    }

    static void setLogErrors(bool should_log_errors) {
        log_errors = should_log_errors;
    }

    ~Logger() {
        if (logf.is_open()) {
            logf.close();
        }
    }
};


#endif //PLAYIN_LOGGER_H
