#include<cstdio>
#include<iostream>
#include<ctime>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
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

long long myclock() {
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

void bash_fail() {
    puts(L_RED"\nFailed");
    exit(0);
}

void store_data(int T, string data, string sc1, string sc2, string prob, int time) {
    string file = "config/" + prob + ".cfg";
    ofstream filestream(file.c_str());
    filestream << T << endl << data << endl << sc1 << endl << sc2 << endl << prob << endl << time << endl;
    filestream.close();
}

void load_data(int &T, string &data, string &sc1, string &sc2, string prob, int &time) {
    string infile = prob + ".cfg";
    ifstream filestream(infile.c_str());
    if (filestream.fail()) {
        printf("Failed!");
        exit(0);
    }
    time = 0;
    filestream >> T >> data >> sc1 >> sc2 >> prob >> time;
    if (time == 0) {
        time = 1000;
    }
    filestream.close();
}

bool check_file(string prob) {    
    string infile = prob + ".cfg";
    ifstream filestream(infile.c_str());
    if (filestream.fail()) {
        filestream.close();
        return 0;
    } else {
        filestream.close();
        return 1;
    }
}

char judge_pause() {
    puts(NONE GRAY"\n(press c to continue, r to rejudge, q to quit)" NONE);
    char c;
    while (c = getchar(), c != 'c' && c != 'q' && c != 'r');
    return c;
}

bool isdir(string filename) {
    struct stat s_buf;
    stat(filename.c_str(), &s_buf);
    return S_ISDIR(s_buf.st_mode);
}

int main() {
    if (access("data", F_OK) != 0 || !isdir("data"))
        if (system("mkdir data")) bash_fail();
    if (access("config", F_OK) != 0 || !isdir("config"))
        if (system("mkdir config")) bash_fail();
	system("clear");
    string dtm, sc1, sc2, prob, file;
    int T, timelimit;
    printf("name of the problem: ");
    cin >> prob;
    int flag = 1;
    getchar();
    string probcfg = "config/" + prob;
    if (check_file(probcfg)) {
        printf("\nFinded the problem file " GREEN"\"%s.cfg\"" NONE" . \nDo you want to load the file? " GRAY"[y/n] " NONE, prob.c_str());
        char c = getchar();
        if (c == 'y') {
            puts("\nloading...");
            load_data(T, dtm, sc1, sc2, probcfg, timelimit);
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
        printf("time limit (ms): ");
        cin >> timelimit;
        store_data(T, dtm, sc1, sc2, prob, timelimit);
        getchar();
        puts("");
    }
    judge:
    int totaltime1 = 0, totaltime2 = 0;
	file = "data/" + prob + "/";
    if (run("rm -rf ./" + file)) bash_fail();
    if (run("mkdir " + file)) bash_fail();
    string total_result = "";
    string dataprogram = file + "data";
    string outprogram = file + "out";
    string ansprogram = file + "ans";
    int gccret = 0;
    printf("compiling \"%s\" ...\n", dtm.c_str());
	gccret = run("g++ " + dtm + " -o " + dataprogram);
    if (WEXITSTATUS(gccret)) {
        puts(YELLOW"\nCompile Error." NONE);
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc1.c_str());
	gccret = run("g++ " + sc1 + " -o " + outprogram);
    if (WEXITSTATUS(gccret)) {
        puts(YELLOW"\nCompile Error." NONE);
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc2.c_str());
	gccret = run("g++ " + sc2 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        puts(YELLOW"\nCompile Error." NONE);
        return 0;
    }
	printf("preparing...\n");
	printf("\ntesting...\n\n");
	string outtot = file + "totalout.log";
	string anstot = file + "totalans.log";
	string res = file + "result.log";
	for (int i = 1; i <= T; i++) {
		system("clear");
		long long  a_time, b_time, s_time, t_time;
		printf("Test #%d\n", i);
		string in = file + tostring(i) + ".in";
		string out = file + tostring(i) + ".out";
		string ans = file + tostring(i) + ".ans";
		//string inbefore = file + tostring(i - 1) + ".in";
        //string in = file + "in.log";
        //string out = file + "out.log";
        //string ans = file + "ans.log";
		printf(GRAY"in: %s\n" NONE, in.c_str());
		printf(GRAY"out:%s\n" NONE, out.c_str());
		printf(GRAY"ans:%s\n" NONE, ans.c_str());
        printf(HIDE "\n");
        int errorflag = 0;
        int ret;
        s_time = myclock();
		ret = run("./" + dataprogram + " > " + in);
        if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE "Data Error!" NONE);
            if (total_result.length() == i - 1) {
                total_result += 'd';
            }
            char c = judge_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                return 0;
            } else {
                puts("\nrejudge...");
                goto judge;
            }
        }
		a_time = myclock();
        ret = run("./" + outprogram + " < " + in + " > " + out);
		b_time = myclock();
        int time1 = b_time - a_time;
		if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE "Runtime Error!" NONE);
            if (total_result.length() == i - 1) {
                total_result += 'r';
            }
            errorflag = 1;
        }
		if (errorflag == 1) printf(NONE"time1: %lldms (return %d)", b_time - a_time, ret);
        else printf(NONE"time1: %lldms\n", b_time - a_time);
        printf(HIDE"\n");
		a_time = myclock();
        ret = run("./" + ansprogram + " < " + in + " > " + ans);
		b_time = myclock();
		if (WEXITSTATUS(ret) != 0) {
            puts(NONE L_PURPLE"Runtime Error!" NONE);
            errorflag = 2;
            if (total_result.length() == i - 1) {
                total_result += 'r';
            }
        }
        int time2 = b_time - a_time;
		if (errorflag == 2) printf(NONE"time2: %lldms (return %d)\n", b_time - a_time, ret);
        else printf(NONE"time2: %lldms\n", b_time - a_time);
        if (errorflag) {
            char c = judge_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                return 0;
            } else {
                puts("\nrejudge...");
                goto judge;
            }
        }
        if (time1 > timelimit || time2 > timelimit) {
            puts(L_BLUE"\nTime Limit Exceeded!" NONE);
            errorflag = 1;
            if (total_result.length() == i - 1) {
                total_result += 't';
            }
        }
        if (errorflag) {
            char c = judge_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                return 0;
            } else {
                puts("\nrejudge...");
                goto judge;
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
            char c = judge_pause();
            if (c == 'c') {
                puts("continue...");
                continue;
            } else if (c == 'q'){
                puts("quit.");
                return 0;
            } else {
                puts("\nrejudge...");
                goto judge;
            }
        }
        printf(L_GREEN"\n#%d Accepted.\n" NONE, i);
        if (total_result.length() == i - 1) {
            total_result += 'a';
            totaltime1 += time1;
            totaltime2 += time2;
        }
        do {
            t_time = myclock();
        } while ((t_time - s_time < 1100) || (t_time - b_time < 300));
        //} while (t_time - b_time < 50);
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
            case 'd':
                printf("#%d " "Data Error\n" NONE, i + 1);
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
    printf("total time: %dms / %dms\n\n", totaltime1, totaltime2);
	return 0;
}
