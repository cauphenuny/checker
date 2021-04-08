/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "data.h"
using namespace std;

void create_data() {
    string T, gen, src1, src2, prob, file;
    int amount;
#define getconfig(x) x = config[#x]
    getconfig(T), amount = stoi(T);
    getconfig(gen);
    getconfig(src1);
    getconfig(src2);
    getconfig(prob);
    getconfig(file);
#undef  getconfig
    create_judge:
    if (loaded == true) {
        printf("amount of detection: ");
        scanf("%d", &amount);
    }
    file = data_dir + prob + "/";
    if (access(file.c_str(), F_OK) == 0) {
        printf("clear data? " GRAY "[y/n] " NONE);
        char c; cin >> c;
        if (c == 'y') {
            if (run("rm -rf ./" + file)) bash_fail();
            if (run("mkdir " + file)) bash_fail();
            puts("cleared.");
        }
        putchar('\n');
    } else {
        if (run("mkdir -p " + file)) bash_fail();
    }
    string dataprogram = file + "data";
    string ansprogram = file + "std";
    int gccret = 0;
    printf("compiling \"%s\" ...\n", gen.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + gen + " -o " + dataprogram);
    int compile_error = 0;
    if (WEXITSTATUS(gccret)) {
        compile_error += 1;
    }
    printf("compiling \"%s\" ...\n", src1.c_str());
    gccret = run("g++ -DLOCAL_JUDGE" + src1 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        compile_error += 2;
    }
    if (compile_error) {
        printf("\n");
        if (compile_error & 1) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, gen.c_str());
        if (compile_error & 2) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, src1.c_str());
        char c = judge_pause();
        if (c == 'q') {
            exit(0);
        } else if (c == 'r') {
            goto create_judge;
        }
    }
    while (access(dataprogram.c_str(), F_OK) != 0) {
        printf(NONE L_RED"\nError: no executable generator.\n" NONE);
        do dataprogram = readline("input generator: "); while (dataprogram == "");
    }
    while (access(ansprogram.c_str(), F_OK) != 0) {
        printf(NONE L_RED"\nError: no executable stdprogram.\n" NONE);
        do ansprogram = readline("input std: "); while (ansprogram == "");
    }
    printf("preparing...\n");
    printf("\ntesting...\n\n");
    register_signal();
    for (int i = 1; i <= amount; i++) {
        system("clear");
        long long  a_time, b_time, s_time, t_time;
        printf(NONE"Test #%d\n", i);
        string in = file + tostring(i) + ".in";
        string ans = file + tostring(i) + ".out";
        if (access(in.c_str(), F_OK) == 0) {
            printf("\n" L_GREEN "Skiped.\n" NONE);
            run("sleep 0.1");
            continue;
        }
        printf(GRAY"in:  %s\n" NONE, in.c_str());
        printf(GRAY"ans: %s\n" NONE, ans.c_str());
        int errorflag = 0;
        int ret;
        if (access(dataprogram.c_str(), F_OK) != 0) {
            printf(NONE L_RED"Error: no executable generator.\n" NONE);
            if ((int)global_result.length() == i - 1) {
                global_result += 'e';
            }
            char c = judge_pause();
            if (c == 'c') { puts("continue..."); continue; }
            else if (c == 'q'){ puts("quit."); quit(0); }
            else { puts("\nrejudge..." NONE); goto create_judge; }
        }
        s_time = myclock();
        ret = run("./" + dataprogram + " 1> " + in + " 2> /dev/null");
        if (WEXITSTATUS(ret) != 0) {
            delline();
            puts(NONE L_PURPLE "Error: generator failed." NONE);
            if ((int)global_result.length() == i - 1) {
                global_result += 'd';
            }
            char c = judge_pause();
            if (c == 'c') { puts("continue..."); continue; }
            else if (c == 'q'){ puts("quit."); quit(0); }
            else { puts("\nrejudge..." NONE); goto create_judge; }
        }
        if (access(ansprogram.c_str(), F_OK) != 0) {
            printf(NONE L_RED"\n\nError: no executable program.\n" NONE);
            if ((int)global_result.length() == i - 1) {
                global_result += 'e';
            }
            char c = judge_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                quit(0);
            } else {
                puts("\nrejudge..." NONE);
                goto create_judge;
            }
        }
        a_time = myclock();
        ret = run("./" + ansprogram + " < " + in + " 1> " + ans + " 2> /dev/null");
        b_time = myclock();
        if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE"Runtime Error!" NONE);
            errorflag = 2;
            if ((int)global_result.length() == i - 1) {
                global_result += 'r';
            }
        }
        if (errorflag == 2) printf(NONE"time: %lldms (return %d)\n", b_time - a_time, WEXITSTATUS(ret));
        else printf(NONE"\n" NONE"time: %lldms\n", b_time - a_time);
        if (errorflag) {
            create_err342:
            char c = answer_pause();
            if (c == 'c') { puts("continue..."); continue; }
            else if (c == 'q') { puts("quit."); quit(0); }
            else if (c == 'r') { puts("\nrejudge..."); goto create_judge; }
            else if (c == 'i') {
                puts("open file...");
                if (run("vim " + in)) {
                    puts(L_RED"\nFailed. Install vim and try again.\n");
                }
                goto create_err342;
            } else if (c == 'd') {
                puts(RED "No output file!" NONE);
                goto create_err342;
            }
        }
        printf(L_GREEN"\n#%d Created.\n" NONE, i);
        if ((int)global_result.length() == i - 1) {
            global_result += 'a';
        }
        if (fast_mode) {
            do {
                t_time = myclock();
            } while (t_time - b_time < 30);
        } else {
            do {
                t_time = myclock();
            } while ((t_time - s_time < 1100) || (t_time - b_time < 300));
        }
    }
    quit(0);
}
