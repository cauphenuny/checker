#include "quit.h"

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
