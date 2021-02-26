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

//constants
extern string version;
extern string branch;
extern const string config_dir;
extern const string data_dir;

//config.cpp
void store_data(int, string, string, string, string, int);
void load_data(int &T, string &data, string &sc1, string &sc2, string prob, int &time);
bool check_file(string prob);
int limited_run(string name, int time_limit, int memory_limit);

//tools.cpp
void clear_buffer();
long long myclock();
string tostring(int a);
int run(string s);
bool isdir(string filename);
void delline();
void bash_fail();

//myreadline.cpp
string readline(string prompt);

//update.cpp
void start_update();
void start_forced_update();
void forced_update();
void auto_update();
void normal_exit(int signum);

//analysis.cpp
void analysis_cmd(string cmd);
void analysis_long_cmd(string s, int &pos);
string getword(string s, int &pos);
void check_version();
void usage(int id);


