/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "main.h"
using namespace std;

string global_result = "";
int global_time1 = 0, global_time2 = 0;

void quit(int signum) {
    system("clear");
    int ac = 0, wa = 0, tle = 0, re = 0, eflag = 0;
    for (int i = 0, len = (int)global_result.length(); i < len; i++) {
        switch (global_result[i]) {
            case 'a':
                ac++; break;
            case 'w':
                wa++; printf("#%d "  "Wrong Answer\n" NONE, i + 1); eflag = 1; break;
            case 't':
                tle++; printf("#%d "  "Time Limit Exceeded\n" NONE, i + 1); eflag = 1; break;
            case 'r':
                re++; printf("#%d " "Runtime Error\n" NONE, i + 1); eflag = 1; break;
            case 'd':
                printf("#%d " "Data Error\n" NONE, i + 1); eflag = 1; break;
            case 'e':
                printf("#%d " "No Executable Program\n" NONE, i + 1); eflag = 1; break;
        }
    }
    if (eflag) puts("");
    printf("Total Result:\n");
    if (ac) printf(L_GREEN"Accepted" NONE" %d\n", ac);
    if (wa) printf(L_RED"Wrong Answer" NONE" %d\n", wa);
    if (tle)printf(L_BLUE"Time Limit Exceeded" NONE" %d\n", tle);
    if (re) printf(L_PURPLE"Runtime Error" NONE" %d\n", re);
    puts("");
    if (global_time1 != 0 && global_time2 != 0) {
        printf("total time: %dms / %dms (%.2lf%%)\n\n", global_time1, global_time2, (double)global_time1 / global_time2 * 100);
    }
    if (branch != "master") printf("%s <%s>\n\n", version.c_str(), branch.c_str());
    else                    printf("%s\n\n", version.c_str());
    //printf(", compiled at %s %s\n", __TIME__, __DATE__);
    start_update();
    exit(0);
}

void register_signal() {
    for (int i = 1; i <= 64; i++) {
        if (i != 17) signal(i, quit);
    }
}

bool always_load = 0, always_continue = 0, always_quit = 0, fast_mode = 1, loaded = 0;
int save_mode = 2; //1=always, 2=auto, 3=never
int general_mode = 1; //1=normal, 2=data

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

void normal_judge();
void create_data();

int T, timelimit;
string dtm, sc1, sc2, prob, file, dtm_exc, sc1_exc, sc2_exc;

int main(int argc, char *argv[]) {
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
    if (access(data_dir.c_str(), F_OK) != 0 || !isdir(data_dir.c_str()))
        if (run("mkdir " + data_dir)) bash_fail();
    if (access(config_dir.c_str(), F_OK) != 0 || !isdir(config_dir.c_str()))
        if (run("mkdir " + config_dir)) bash_fail();
    chdir(config_dir.c_str());
    if (prob == "") {
        while (prob == "") prob = readline("name of the problem: ");
        getchar();
    }
    chdir("..");
    while (prob[(int)prob.length() - 1] == ' ') prob.pop_back();
    //system("clear");
    int flag = 1;
    string probcfg = config_dir + prob;
    if (check_file(probcfg)) {
        if (!always_load) {
            //clear_buffer();
            printf("\nFinded the problem file " GREEN"\"%s\"" NONE" . \nDo you want to load the file? " GRAY"[y/n] " NONE, prob.c_str());
            char c = getchar();
            if (c == 'y') {
                puts("\nloading...");
                load_data(T, dtm, sc1, sc2, probcfg, timelimit);
                loaded = true;
                flag = 0;
            }
        } else {
            printf("loading problem " GREEN "%s" NONE " ...\n\n", prob.c_str());
            load_data(T, dtm, sc1, sc2, probcfg, timelimit);
            loaded = true;
            flag = 0;
        }
    }
    if (flag) {
        //system("clear");
        printf("amount of detection: ");
        scanf("%d", &T);
        if (general_mode == 1) {
            do dtm = readline("name of generator: "); while (dtm == "");
            do sc1 = readline("name of source1: "); while (sc1 == "");
            do sc2 = readline("name of source2: "); while (sc2 == "");
        } else {
            do dtm = readline("name of generator: "); while (dtm == "");
            do sc1 = readline("name of std: "); while (sc1 == "");
            sc2 = sc1;
        }
        printf("time limit (ms): ");
        cin >> timelimit;
        store_data(T, dtm, sc1, sc2, prob, timelimit);
        getchar();
        puts("");
    }
    if (general_mode == 1) {
        normal_judge();
    } else {
        create_data();
    }
    return 0;
}

void create_data() {
    create_judge:
    if (loaded == true) {
        printf("amount of detection: ");
        scanf("%d", &T);
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
    printf("compiling \"%s\" ...\n", dtm.c_str());
    gccret = run("g++ -DLOCAL_JUDGE " + dtm + " -o " + dataprogram);
    int compile_error = 0;
    if (WEXITSTATUS(gccret)) {
        compile_error += 1;
    }
    printf("compiling \"%s\" ...\n", sc1.c_str());
    gccret = run("g++ -DLOCAL_JUDGE" + sc1 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        compile_error += 2;
    }
    if (compile_error) {
        printf("\n");
        if (compile_error & 1) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, dtm.c_str());
        if (compile_error & 2) printf(YELLOW"Compile Error at \"%s\" .\n" NONE, sc1.c_str());
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
    for (int i = 1; i <= T; i++) {
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
