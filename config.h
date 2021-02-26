#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "color.h"

using std::string;

//config.cpp
void store_data(int, std::string, std::string, std::string, std::string, int);
void load_data(int &T, std::string &data, std::string &sc1, std::string &sc2, std::string prob, int &time);
bool check_file(std::string prob);
int limited_run(std::string name, int time_limit, int memory_limit);

//func.cpp
void clear_buffer();
long long myclock();
std::string tostring(int a);
int run(std::string s);
bool isdir(std::string filename);
void delline();
void bash_fail();

//myreadline.cpp
std::string readline(std::string prompt);

//update.cpp
void start_update();
void start_forced_update();
void forced_update();
void auto_update();
void normal_exit(int signum);

//constants
extern std::string version;
extern std::string branch;
extern const std::string config_dir;
extern const std::string data_dir;
