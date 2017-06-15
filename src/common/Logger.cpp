//
// Created by artef on 03.05.2017.
//

#include <iostream>
#include "Logger.h"

std::ofstream Logger::logf;
std::ostream &Logger::log = std::cout;
bool Logger::log_info(true);
bool Logger::log_warnings(true);
bool Logger::log_errors(true);
