#include<cstdio>
#include<iostream>
#include <time.h>   // clock_t
#include <unistd.h>  // sleep()
#include<cstring>
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

int main() {
	system("clear");
	system("rm -rf data");
	system("mkdir data");
	system("clear");
	printf("Test Cases: ");
	int T;
	scanf("%d", &T);
	printf("name of datamaker: ");
	string dtm; cin >> dtm;
	printf("name of source1: ");
	string sc1; cin >> sc1;
	printf("name of source2: ");
	string sc2; cin >> sc2;
    printf("name of problem: ");
    string prob;cin >> prob;
	printf("compiling...\n");
	run("g++ " + dtm + " -o makedata");
	run("g++ " + sc1 + " -o out");
	run("g++ " + sc2 + " -o ans");
	printf("preparing...\n");
	printf("\ntesting...\n\n");
	string file = "data/" + prob;
	string outtot = file + ".totalout1";
	string anstot = file + ".totalout2";
	string res = file + "-result.log";
	for (int i = 1; i <= T; i++) {
		system("clear");
		clock_t  a_time, b_time, c_time, s_time, t_time;
		printf("Test #%d\n", i);
		run("echo -----Test "  + tostring(i) +  " >> " + outtot);
		run("echo -----Test "  + tostring(i) +  " >> " + anstot);
		run("echo -----Test "  + tostring(i) +  " >> " + res);
		string in = file + "_" + tostring(i) + ".in";
		string out = file + "_" + tostring(i) + ".out1";
		string ans = file + "_" + tostring(i) + ".out2";
		string inbefore = file + tostring(i - 1) + ".in";
		printf("in: %s\n", in.c_str());
		printf("out:%s\n", out.c_str());
		printf("ans:%s\n", ans.c_str());
		run("./makedata > " + in);
        s_time = clock();
		a_time = clock();
		run("./out < " + in + " > " + out);
		b_time = clock();
        int time1 = b_time - a_time
		printf("time1: %ldms\n", b_time - a_time);
		a_time = clock();
		run("./ans < " + in + " > " + ans);
		b_time = clock();
        int time2 = b_time - a_time;
		printf("time2: %ldms\n", b_time - a_time);
		if (run("diff " + out + " " + ans + " >> " + res)) {
            puts("Wrong Answer!");
            while(1);
        }
        if (time1 > 1000 || time2 > 1000) {
            puts("Time Limit Exceeded!");
        }
        do {
            t_time = clock();
        } while (((double)(t_time - s_time) / CLOCKS_PER_SEC) < 1);
        cout << t_time << endl << s_time << endl;
	}
	system("clear");
	printf("%s\n", res.c_str());
	run("vim " + res);
	return 0;
}
