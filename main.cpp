/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "main.h"
using namespace std;

string version = UNDERLINE "checker v5.11.1" NONE;
string branch = "master";
const string config_dir = ".config/";
const string data_dir = ".data/";

string global_result = "";
int global_time1 = 0, global_time2 = 0;

bool always_load = 0, always_continue = 0, always_quit = 0, fast_mode = 1, loaded = 0;
int save_mode = 2; //1=always, 2=auto, 3=never
int general_mode = 1; //1=normal, 2=data
string T, timelimit, gen, src1, src2, prob, file;
string probcfg;

map<string, string> config;

int main(int argc, char *argv[]) {
// analysis command
    if (argc >= 2) {
        for (int i = 1, prof = 0; i < argc; i++) {
            if (argv[i][0] != '-') {
                if (!prof) prob = argv[i], prof = 1, always_load = 1;
                else usage(1);
            } else {
                analysis_cmd(argv[i]);
            }
        }
    }

// mkdir
    if (access(data_dir.c_str(), F_OK) != 0 || !isdir(data_dir.c_str()))
        if (run("mkdir " + data_dir)) bash_fail();
    if (access(config_dir.c_str(), F_OK) != 0 || !isdir(config_dir.c_str()))
        if (run("mkdir " + config_dir)) bash_fail();
    chdir(config_dir.c_str());
    if (prob == "") {
        while (prob == "") prob = readline("name of the problem: ");
    }
    chdir("..");
    while (prob[(int)prob.length() - 1] == ' ') prob.pop_back();

// load problem
    int flag = 1;
    probcfg = config_dir + prob;
    if (check_file(probcfg)) {
        if (!always_load) {
            //clear_buffer();
            printf("\nFinded the problem file " GREEN"\"%s\"" NONE" . \nDo you want to load the file? " GRAY"[y/n] " NONE, prob.c_str());
            char c = getchar();
            if (c == 'y') {
                puts("\nloading...");
                load_data(config, prob);
                loaded = true;
                flag = 0;
            }
        } else {
            printf("loading problem " GREEN "%s" NONE " ...\n\n", prob.c_str());
            load_data(config, prob);
            loaded = true;
            flag = 0;
        }
    }
    if (flag) {
        //system("clear");
        T = "1000000";
        if (general_mode == 1) {
            do gen = readline("generator (*.cpp): "); while (gen == "");
            do src1 = readline("source1 (*.cpp): "); while (src1 == "");
            do src2 = readline("source2 (*.cpp): "); while (src2 == "");
        } else {
            do gen = readline("generator (*.cpp): "); while (gen == "");
            do src1 = readline("std (*.cpp): "); while (src1 == "");
            src2 = src1;
        }
        printf("time limit (ms): ");
        cin >> timelimit;
#define setconfig(x) config[#x] = x
        setconfig(T);
        setconfig(gen);
        setconfig(src1);
        setconfig(src2);
        setconfig(prob);
        setconfig(timelimit);
#undef  setconfig
        store_data(config);
        getchar();
        puts("");
    }

// start main function
    if (general_mode == 1) {
        normal_judge();
    } else {
        create_data();
    }
    return 0;
}

