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
    string T, gen, src1, src2, prob, file, timelimit;
    int amount, time_limit;
#define getconfig(x) x = config[#x]
    getconfig(T), amount = stoi(T);
    getconfig(gen);
    getconfig(src1);
    getconfig(src2);
    getconfig(prob);
    getconfig(timelimit), time_limit = stoi(timelimit);
#undef  getconfig
    judge:
    file = data_dir + prob + "/";
    if (run("rm -rf ./" + file)) bash_fail();
    if (run("mkdir " + file)) bash_fail();
    string gen_name = "gen";
    string out_name = "out";
    string ans_name = "ans";
    string gen_exec = file + gen_name;
    string out_exec = file + out_name;
    string ans_exec = file + ans_name;
    int gccret = 0;
    printf("compiling \"%s\" ...\n", gen.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + gen + " -o " + gen_exec);
    int compile_error = 0;
    if (WEXITSTATUS(gccret)) {
        compile_error += 1;
    }
    printf("compiling \"%s\" ...\n", src1.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + src1 + " -o " + out_exec);
    if (WEXITSTATUS(gccret)) {
        compile_error += 2;
    }
    printf("compiling \"%s\" ...\n", src2.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + src2 + " -o " + ans_exec);
    if (WEXITSTATUS(gccret)) {
        compile_error += 4;
    }
    if (compile_error) {
        printf("\n");
        if (compile_error & 1) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, gen.c_str());
        if (compile_error & 2) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, src1.c_str());
        if (compile_error & 4) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, src2.c_str());
        char c = judge_pause();
        if (c == 'q') {
            exit(0);
        } else if (c == 'r') {
            goto judge;
        }
    }
    if (access(gen_exec.c_str(), F_OK) != 0) {
        while (access(gen_exec.c_str(), F_OK) != 0) {
            printf(NONE L_RED"\nError: no executable generator.\n" NONE);
            do gen_exec = readline("input generator: "); while (gen_exec == "");
        }
        run("cp " + gen_exec + " " + file + gen_name);
    }
    if (access(out_exec.c_str(), F_OK) != 0) {
        while (access(out_exec.c_str(), F_OK) != 0) {
            printf(NONE L_RED"\nError: no executable testprogram.\n" NONE);
            do out_exec = readline("input testprogram: "); while (out_exec == "");
        }
        run("cp " + out_exec + " " + file + out_name);
    }
    if (access(ans_exec.c_str(), F_OK) != 0) {
        while (access(ans_exec.c_str(), F_OK) != 0) {
            printf(NONE L_RED"\nError: no executable stdprogram.\n" NONE);
            do ans_exec = readline("input std: "); while (ans_exec == "");
        }
        run("cp " + ans_exec + " " + file + ans_name);
    }
    printf("preparing...\n");
    printf("\ntesting...\n\n");
    string outtot = file + "totalout.log";
    string anstot = file + "totalans.log";
    string res = file + "result.log";
    register_signal();
    for (int i = 1; i <= amount; i++) {
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
        string runtime_in = prob + ".in ";
        string runtime_out = prob + ".out ";
        printf(GRAY"in:  %s  (%s.in)\n" NONE, in.c_str(), prob.c_str());
        printf(GRAY"out: %s (%s.out)\n" NONE, out.c_str(), prob.c_str());
        printf(GRAY"ans: %s (%s.out)\n" NONE, ans.c_str(), prob.c_str());
        run("echo \"\" > " + out);
        run("echo \"\" > " + ans);
        int errorflag = 0;
        int ret, tle_flag1 = 0, tle_flag2 = 0, tle_flag;
        if (access(gen_exec.c_str(), F_OK) != 0) {
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
        ret = run("cd " + file + " && ./" + gen_name + " > " + runtime_in + "cd ../../");
        run("cp " + file + runtime_in + in);
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
        if (access(out_exec.c_str(), F_OK) != 0) {
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
        run("cp " + in + file + runtime_in);
        printf(HIDE "\n");
        a_time = myclock();
        ret = run("cd " + file + " && timeout " + to_string((double)time_limit / 1000) + " ./" + out_name + " < " + runtime_in + " > " + runtime_out + "cd ../../");
        b_time = myclock();
        run("cp " + file + runtime_out + out);
        int time1 = b_time - a_time;
        if (WEXITSTATUS(ret) == 124) tle_flag1 = 1;
        else if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE "Runtime Error!" NONE);
            if ((int)global_result.length() == i - 1) {
                global_result += 'r';
            }
            errorflag = 1;
        }
        if (time1 > time_limit) tle_flag1 = 1;
        if (errorflag == 1) printf(NONE"time1: %dms (return %d)", time1, WEXITSTATUS(ret));
        else printf(NONE"time1: %dms", time1);
        if (access(ans_exec.c_str(), F_OK) != 0) {
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
        run("cp " + in + file + runtime_in);
        printf(HIDE "\n");
        a_time = myclock();
        ret = run("cd " + file + " && timeout " + to_string((double)time_limit / 1000) + " ./" + ans_name + " < " + runtime_in + " > " + runtime_out + "cd ../../");
        b_time = myclock();
        run("cp " + file + runtime_out + ans);
        tle_flag2 = 0;
        if (WEXITSTATUS(ret) == 124) tle_flag2 = 1;
        else if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE"Runtime Error!" NONE);
            errorflag = 2;
            if ((int)global_result.length() == i - 1) {
                global_result += 'r';
            }
        }
        int time2 = b_time - a_time;
        if (time2 > time_limit) tle_flag2 = 1;
        if (errorflag == 2) printf(NONE"time2: %dms (return %d)\n", time2, WEXITSTATUS(ret));
        else printf(NONE"\n" NONE"time2: %dms\n", time2);
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
                    puts(L_RED"\nFailed.\n");
                }
                goto err342;
            } else if (c == 'd') {
                puts("open file...");
                if (run("vim -d " + out + ans)) {
                    puts(L_RED"\nFailed.\n");
                }
                goto err342;
            }
        }
        tle_flag = tle_flag1 | tle_flag2;
        if (tle_flag) {
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

