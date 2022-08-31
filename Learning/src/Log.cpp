#include <iostream>

void log(const char* message) {
	std::cout << message << std::endl;
}

void log(int message) {
	std::cout << message << std::endl;
}