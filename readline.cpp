//#include <readline/history.h>
//#include <readline/readline.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
std::string readline(std::string prompt) {
    printf("%s", prompt.c_str());
    std::string res;
    std::cin >> res;
    return res;
}
