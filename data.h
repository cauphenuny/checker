#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include "color.h"

using std::string;

//constants
extern string version;
extern string branch;
extern const string config_dir;
extern const string data_dir;

//variable
extern string global_result;
extern int global_time1, global_time2;
extern int T, timelimit;
extern string dtm, sc1, sc2, prob, file, dtm_exc, sc1_exc, sc2_exc;
extern bool always_load, always_continue, always_quit, fast_mode, loaded;
extern int save_mode;
extern int general_mode;

//config.cpp
void store_data(int, string, string, string, string, int);
void load_data(int &T, string &data, string &sc1, string &sc2, string prob, int &time);
bool check_file(string prob);
int limited_run(string name, int time_limit, int memory_limit);

//func.cpp
void clear_buffer();
long long myclock();
string tostring(int a);
int run(string s);
bool isdir(string filename);
void delline();
void bash_fail();

//myreadline.cpp
string readline(string prompt);

//judge.cpp
char judge_pause();
char answer_pause();

//quit.cpp
void quit(int signum);
void register_signal();
