#include<cstdio>
#include<iostream>
#include <time.h>   // clock_t
#include <unistd.h>  // sleep()
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<sys/time.h>
#define NONE                 "\e[0m"
#define BLACK                "\e[0;30m"
#define L_BLACK              "\e[1;30m"
#define RED                  "\e[0;31m"
#define L_RED                "\e[1;31m"
#define GREEN                "\e[0;32m"
#define L_GREEN              "\e[1;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"
#define BLUE                 "\e[0;34m"
#define L_BLUE               "\e[1;34m"
#define PURPLE               "\e[0;35m"
#define L_PURPLE             "\e[1;35m"
#define CYAN                 "\e[0;36m"
#define L_CYAN               "\e[1;36m"
#define GRAY                 "\e[0;37m"
#define WHITE                "\e[1;37m"
#define BOLD                 "\e[1m"
#define UNDERLINE            "\e[4m"
#define BLINK                "\e[5m"
#define REVERSE              "\e[7m"
#define HIDE                 "\e[8m"
#define CLEAR                "\e[2J" 
#define CLRLINE              "\r\e[K"
using namespace std;

int myclock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

string tostring(int a) {
	char s[256];
	memset(s, 0, sizeof(s));
	int tot = 0;
	while (a > 0) {
		s[tot] = (a % 10) + '0';
		tot++;
		a /= 10;
	}
	for (int i = 0; i < (tot / 2); i++) {
		swap(s[i], s[tot - 1 - i]);
	}
	return s;
}

int run(string s) {
	return system(s.c_str());
}

void store_data(int T, string data, string sc1, string sc2, string prob) {
    string file = prob + ".cfg";
    ofstream filestream(file.c_str());
    filestream << T << endl << data << endl << sc1 << endl << sc2 << endl << prob << endl;
}

void load_data(int &T, string &data, string &sc1, string &sc2, string prob) {
    string infile = prob + ".cfg";
    ifstream filestream(infile.c_str());
    if (filestream.fail()) {
        printf("Failed!");
        exit(0);
    }
    filestream >> T >> data >> sc1 >> sc2 >> prob;
}

bool check_file(string prob) {    
    string infile = prob + ".cfg";
    ifstream filestream(infile.c_str());
    if (filestream.fail()) {
        return 0;
    } else {
        return 1;
    }
}

string total_result;

int main() {
	system("clear");
    string dtm, sc1, sc2, prob;
    int T;
    printf("name of the problem: ");
    cin >> prob;
    int flag = 1;
    getchar();
    if (check_file(prob)) {
        printf("\nFinded the problem file " GREEN"\"%s.cfg\"" NONE" . \nDo you want to load the file? " GRAY"[y/n] " NONE, prob.c_str());
        char c = getchar();
        if (c == 'y') {
            puts("\nloading...");
            load_data(T, dtm, sc1, sc2, prob);
            flag = 0;
        }
    }
    if (flag) {
        system("clear");
    	printf("Test Cases: ");
    	scanf("%d", &T);
    	printf("name of datamaker: ");
    	cin >> dtm;
    	printf("name of source1: ");
    	cin >> sc1;
    	printf("name of source2: ");
    	cin >> sc2;
        store_data(T, dtm, sc1, sc2, prob);
        getchar();
    }
    run("rm -rf ./" + prob);
    run("mkdir " + prob);
	string file = prob + "/";
    string dataprogram = file + "data";
    string outprogram = file + "out";
    string ansprogram = file + "ans";
    int gccret = 0;
    printf("compiling \"%s\" ...\n", dtm.c_str());
	gccret = run("g++ " + dtm + " -o " + dataprogram);
    if (WEXITSTATUS(gccret)) {
        puts(L_RED"\nFailed." NONE);
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc1.c_str());
	gccret = run("g++ " + sc1 + " -o " + outprogram);
    if (WEXITSTATUS(gccret)) {
        puts(L_RED"\nFailed." NONE);
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc2.c_str());
	gccret = run("g++ " + sc2 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        puts(L_RED"\nFailed." NONE);
        return 0;
    }
	printf("preparing...\n");
	printf("\ntesting...\n\n");
	string outtot = file + "totalout.log";
	string anstot = file + "totalans.log";
	string res = file + "result.log";
	for (int i = 1; i <= T; i++) {
		system("clear");
		clock_t  a_time, b_time, s_time, t_time;
		printf("Test #%d\n", i);
		string in = file + tostring(i) + ".in";
		string out = file + tostring(i) + ".out";
		string ans = file + tostring(i) + ".ans";
		string inbefore = file + tostring(i - 1) + ".in";
		printf(GRAY"in: %s\n", in.c_str());
		printf("out:%s\n", out.c_str());
		printf("ans:%s\n\n" NONE, ans.c_str());
        int errorflag = 0;
        s_time = myclock();
		run("./" + dataprogram + " > " + in);
		a_time = myclock();
        int ret = run("./" + outprogram + " < " + in + " > " + out);
		b_time = myclock();
        int time1 = b_time - a_time;
		if (WEXITSTATUS(ret) != 0) {
            puts(L_PURPLE "Runtime Error!" NONE);
            if (total_result.length() == i - 1) {
                total_result += 'r';
            }
            errorflag = 1;
        }
		if (errorflag == 1) printf("time1: %ldms (return %d)\n", b_time - a_time, ret);
        else printf("time1: %ldms\n\n", b_time - a_time);
		a_time = myclock();
        ret = run("./" + ansprogram + " < " + in + " > " + ans);
		b_time = myclock();
		if (WEXITSTATUS(ret) != 0) {
            puts(L_PURPLE"Runtime Error!" NONE);
            errorflag = 2;
            if (total_result.length() == i - 1) {
                total_result += 'r';
            }
        }
        int time2 = b_time - a_time;
		if (errorflag == 2) printf("time2: %ldms (return %d)\n", b_time - a_time, ret);
        else printf("time2: %ldms\n", b_time - a_time);
        if (errorflag) {
            puts(GRAY"\n(press c to continue, press q to quit)" NONE);
            char c;
            while (c = getchar(), c != 'c' && c != 'q');
            if (c == 'c') {
                puts("continue...");
                continue;
            } else {
                puts("quit.");
                return 0;
            }
        }
        if (time1 > 1000 || time2 > 1000) {
            puts(L_BLUE"\nTime Limit Exceeded!" NONE);
            errorflag = 1;
            if (total_result.length() == i - 1) {
                total_result += 't';
            }
        }
        if (errorflag) {
            puts("\n(press c to continue, press q to quit)");
            char c;
            while (c = getchar(), c != 'c' && c != 'q');
            if (c == 'c') {
                puts("continue...");
                continue;
            } else {
                puts("quit.");
                return 0;
            }
        }
		if (run("diff " + out + " " + ans + " >> " + res)) {
            puts(L_RED"\nWrong Answer!" NONE);
            errorflag = 1;
            if (total_result.length() == i - 1) {
                total_result += 'w';
            }
        }
        if (errorflag) {
            puts("\n(press c to continue, press q to quit)");
            char c;
            while (c = getchar(), c != 'c' && c != 'q');
            if (c == 'c') {
                puts("continue...");
                continue;
            } else {
                puts("quit.");
                return 0;
            }
        }
        printf(L_GREEN"\n#%d Accepted.\n" NONE, i);
        if (total_result.length() == i - 1) {
            total_result += 'a';
        }
        do {
            t_time = myclock();
        } while (((t_time - s_time) / 1000) < 1);
	}
	system("clear");
    int ac = 0, wa = 0, tle = 0, re = 0, eflag = 0;
    for (int i = 0, len = total_result.length(); i < len; i++) {
        switch (total_result[i]) {
            case 'a':
                ac++;
                break;
            case 'w':
                wa++;
                printf("#%d "  "Wrong Answer\n" NONE, i + 1);
                eflag = 1;
                break;
            case 't':
                tle++;
                printf("#%d "  "Time Limit Exceeded\n" NONE, i + 1);
                eflag = 1;
                break;
            case 'r':
                re++;
                printf("#%d " "Runtime Error\n" NONE, i + 1);
                eflag = 1;
                break;
        }
    }
    if (eflag) puts("");
    printf("Total Result:\n");
    printf(L_GREEN"Accepted" NONE" %d\n", ac);
    printf(L_RED"Wrong Answer" NONE" %d\n", wa);
    printf(L_BLUE"Time Limit Exceeded" NONE" %d\n", tle);
    printf(L_PURPLE"Runtime Error" NONE" %d\n\n", re);
	return 0;
}
