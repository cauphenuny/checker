#include<cstdio>
#include<iostream>
#include <time.h>   // clock_t
#include <unistd.h>  // sleep()
#include<cstring>
#include<fstream>
#include<cstdlib>
using namespace std;

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

int main() {
	system("clear");
    string dtm, sc1, sc2, prob;
    int T;
    printf("name of the problem: ");
    cin >> prob;
    int flag = 1;
    getchar();
    if (check_file(prob)) {
        printf("\nFinded the problem file \"%s.cfg\" . \nDo you want to load the file? [y/n] ", prob.c_str());
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
        puts("\nFailed.");
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc1.c_str());
	gccret = run("g++ " + sc1 + " -o " + outprogram);
    if (WEXITSTATUS(gccret)) {
        puts("\nFailed.");
        return 0;
    }
    printf("compiling \"%s\" ...\n", sc2.c_str());
	gccret = run("g++ " + sc2 + " -o " + ansprogram);
    if (WEXITSTATUS(gccret)) {
        puts("\nFailed.");
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
		printf("in: %s\n", in.c_str());
		printf("out:%s\n", out.c_str());
		printf("ans:%s\n\n", ans.c_str());
        int errorflag = 0;
        s_time = clock();
		run("./" + dataprogram + " > " + in);
		a_time = clock();
        int ret = run("./" + outprogram + " < " + in + " > " + out);
		b_time = clock();
        int time1 = b_time - a_time;
		if (WEXITSTATUS(ret) != 0) {
            puts("Runtime Error!");
            errorflag = 1;
        }
		if (errorflag == 1) printf("time1: %ldms (return %d)\n\n", b_time - a_time, ret);
        else printf("time1: %ldms\n\n", b_time - a_time);
		a_time = clock();
        ret = run("./" + ansprogram + " < " + in + " > " + ans);
		if (WEXITSTATUS(ret) != 0) {
            puts("Runtime Error!");
            errorflag = 2;
        }
		b_time = clock();
        int time2 = b_time - a_time;
		if (errorflag == 2) printf("time2: %ldms (return %d)\n", b_time - a_time, ret);
        else printf("time2: %ldms\n", b_time - a_time);
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
            puts("\nWrong Answer!");
            errorflag = 1;
        }
        if (time1 > 1000 || time2 > 1000) {
            puts("\nTime Limit Exceeded!");
            errorflag = 1;
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
        do {
            t_time = clock();
        } while (((t_time - s_time) / CLOCKS_PER_SEC) < 1);
	}
	system("clear");
	printf("result: %s\n", res.c_str());
	return 0;
}
