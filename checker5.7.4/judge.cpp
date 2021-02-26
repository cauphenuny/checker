/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "judge.h"

char judge_pause() {
    puts(NONE GRAY"\n(press [c] to continue, [r] to rejudge, [q] to quit)" NONE);
    char c;
    if (always_continue) return 'c';
    if (always_quit) return 'q';
    while (c = getchar(), c != 'c' && c != 'q' && c != 'r');
    return c;
}

char answer_pause() {
    puts(NONE GRAY"\n(press [c] to continue, [r] to rejudge, [q] to quit)" NONE);
    puts(NONE GRAY"(press [i] to check input file, [d] to use vim to diff output file)" NONE);
    char c;
    if (always_continue) return 'c';
    if (always_quit) return 'q';
    while (c = getchar(), c != 'c' && c != 'q' && c != 'r' && c != 'i' && c != 'd');
    return c;
}

void normal_judge() {
    judge:
    file = data_dir + prob + "/";
    if (run("rm -rf ./" + file)) bash_fail();
    if (run("mkdir " + file)) bash_fail();
    string dataprogram = file + "data";
    string outprogram = file + "out";
    string ansprogram = file + "ans";
    int gccret = 0;
    printf("compiling \"%s\" ...\n", dtm.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + dtm + " -o " + dataprogram);
    int compile_error = 0;
    if (WEXITSTATUS(gccret)) {
        compile_error += 1;
    }
    printf("compiling \"%s\" ...\n", sc1.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + sc1 + " -o " + outprogram);
    if (WEXITSTATUS(gccret)) {
        compile_error += 2;
    }
    printf("compiling \"%s\" ...\n", sc2.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + sc2 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        compile_error += 4;
    }
    if (compile_error) {
        printf("\n");
        if (compile_error & 1) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, dtm.c_str());
        if (compile_error & 2) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, sc1.c_str());
        if (compile_error & 4) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, sc2.c_str());
        char c = judge_pause();
        if (c == 'q') {
            exit(0);
        } else if (c == 'r') {
            goto judge;
        }
    }
    while (access(dataprogram.c_str(), F_OK) != 0) {
        printf(NONE L_RED"\nError: no executable generator.\n" NONE);
        do dataprogram = readline("input generator: "); while (dataprogram == "");
    }
    while (access(outprogram.c_str(), F_OK) != 0) {
        printf(NONE L_RED"\nError: no executable testprogram.\n" NONE);
        do outprogram = readline("input testprogram: "); while (outprogram == "");
    }
    while (access(ansprogram.c_str(), F_OK) != 0) {
        printf(NONE L_RED"\nError: no executable stdprogram.\n" NONE);
        do ansprogram = readline("input std: "); while (ansprogram == "");
    }
    printf("preparing...\n");
    printf("\ntesting...\n\n");
    string outtot = file + "totalout.log";
    string anstot = file + "totalans.log";
    string res = file + "result.log";
    register_signal();
    for (int i = 1; i <= T; i++) {
        system("clear");
        long long  a_time, b_time, s_time, t_time;
        printf(NONE"Test #%d\n", i);
        string in_with_id = file + tostring(i) + ".in ";
        string out_with_id = file + tostring(i) + ".out ";
        string ans_with_id = file + tostring(i) + ".ans ";
        string in, out, ans;
        if (save_mode != 1) {
            in = file + "in.log ";
            out = file + "out.log ";
            ans = file + "ans.log ";
        } else {
            in = in_with_id;
            out = out_with_id;
            ans = ans_with_id;
        }
        printf(GRAY"in:  %s\n" NONE, in.c_str());
        printf(GRAY"out: %s\n" NONE, out.c_str());
        printf(GRAY"ans: %s\n" NONE, ans.c_str());
        printf(HIDE"\n");
        int errorflag = 0;
        int ret;
        if (access(dataprogram.c_str(), F_OK) != 0) {
            printf(NONE L_RED"Error: no executable generator.\n" NONE);
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
                goto judge;
            }
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
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                quit(0);
            } else {
                puts("\nrejudge...");
                goto judge;
            }
        }
        if (access(outprogram.c_str(), F_OK) != 0) {
            printf(NONE L_RED"Error: no executable program.\n" NONE);
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
            } else if (c == 'r'){
                puts("\nrejudge..." NONE);
                goto judge;
            }
        }
        a_time = myclock();
        ret = run("./" + outprogram + " < " + in + " 1> " + out + " 2> /dev/null");
        b_time = myclock();
        int time1 = b_time - a_time;
        if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE "Runtime Error!" NONE);
            if ((int)global_result.length() == i - 1) {
                global_result += 'r';
            }
            errorflag = 1;
        }
        if (errorflag == 1) printf(NONE"time1: %lldms (return %d)", b_time - a_time, WEXITSTATUS(ret));
        else printf(NONE"time1: %lldms", b_time - a_time);
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
                goto judge;
            }
        }
        printf(HIDE"\n");
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
        int time2 = b_time - a_time;
        if (errorflag == 2) printf(NONE"time2: %lldms (return %d)\n", b_time - a_time, WEXITSTATUS(ret));
        else printf(NONE"\n" NONE"time2: %lldms\n", b_time - a_time);
        if (errorflag) {
            if (save_mode == 2) {
                run("cp " + in + in_with_id);
                printf(GREEN "Saved data to [ %s]\n" NONE, in_with_id.c_str());
            }
            err342:
            char c = answer_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q') {
                puts("quit.");
                quit(0);
            } else if (c == 'r') {
                puts("\nrejudge...");
                goto judge;
            } else if (c == 'i') {
                puts("open file...");
                if (run("vim " + in)) {
                    puts(L_RED"\nFailed. Install vim and try again.\n");
                }
                goto err342;
            } else if (c == 'd') {
                puts(RED "No output file!" NONE);
                //puts("open file...");
                //if (run("vim -d " + out + ans)) {
                //    puts(L_RED"\nFailed. Install vim and try again.\n");
                //}
                goto err342;
            }
        }
        if (time1 > timelimit || time2 > timelimit) {
            puts(L_BLUE"\nTime Limit Exceeded!" NONE);
            errorflag = 1;
            if ((int)global_result.length() == i - 1) {
                global_result += 't';
            }
        }
        if (errorflag) {
            if (save_mode == 2) {
                run("cp " + in + in_with_id);
                printf(GREEN "Saved data to [ %s]\n" NONE, in_with_id.c_str());
            }
            err370:
            char c = answer_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                quit(0);
            } else if (c == 'r'){
                puts("\nrejudge...");
                goto judge;
            } else if (c == 'i') {
                puts("open file...");
                if (run("vim " + in)) {
                    puts(L_RED"\nFailed. Install vim and try again.\n");
                }
                goto err370;
            } else if (c == 'd') {
                puts(RED "No output file!" NONE);
                //puts("open file...");
                //if (run("vim -d " + out + ans)) {
                //    puts(L_RED"\nFailed. Install vim and try again.\n");
                //}
                goto err370;
            }
        }
        if (run("diff " + out + " " + ans + " > " + res)) {
            puts(L_RED"\nWrong Answer!" NONE);
            errorflag = 1;
            if ((int)global_result.length() == i - 1) {
                global_result += 'w';
            }
        }
        if (errorflag) {
            if (save_mode == 2) {
                run("cp " + in + in_with_id);
                printf(GREEN "Saved data to [ %s]\n" NONE, in_with_id.c_str());
            }
            err395:
            char c = answer_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                quit(0);
            } else if (c == 'r'){
                puts("\nrejudge...");
                goto judge;
            } else if (c == 'i') {
                puts("open file...");
                if (run("vim " + in)) {
                    puts(L_RED"\nFailed. Install vim and try again.\n");
                }
                goto err395;
            } else if (c == 'd') {
                puts("open file...");
                if (run("vim -d " + out + ans)) {
                    puts(L_RED"\nFailed. Install vim and try again.\n");
                }
                goto err395;
            }
        }
        printf(L_GREEN"\n#%d Accepted.\n" NONE, i);
        if ((int)global_result.length() == i - 1) {
            global_result += 'a';
            global_time1 += time1;
            global_time2 += time2;
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
