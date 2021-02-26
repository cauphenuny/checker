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

void run(string s) {
	system(s.c_str());
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
	printf("compiling...\n");
	run("g++ " + dtm + " -o makedata");
	run("g++ " + sc1 + " -o out");
	run("g++ " + sc2 + " -o ans");
	printf("preparing...\n");
	printf("\ntesting...\n\n");
	string file = "data/b";
	string outtot = file + ".totalout";
	string anstot = file + ".totalans";
	string res = file + "-result.log";
	for (int i = 1; i <= T; i++) {
		system("clear");
		clock_t  a_time, b_time, c_time;
		printf("Test #%d\n", i);
		run("echo -----Test "  + tostring(i) +  " >> " + outtot);
		run("echo -----Test "  + tostring(i) +  " >> " + anstot);
		run("echo -----Test "  + tostring(i) +  " >> " + res);
		string in = file + tostring(i) + ".in";
		string out = file + tostring(i) + ".out";
		string ans = file + tostring(i) + ".ans";
		string inbefore = file + tostring(i - 1) + ".in";
		printf("in: %s\n", in.c_str());
		printf("out:%s\n", out.c_str());
		printf("ans:%s\n", ans.c_str());
		run("./makedata > " + in);
		a_time = clock();
		run("./out < " + in + " > " + out);
		b_time = clock();
		printf("time1: %ldms\n", b_time - a_time);
		a_time = clock();
		run("./ans < " + in + " > " + ans);
		b_time = clock();
		printf("time2: %ldms\n", b_time - a_time);
		run("diff " + out + " " + ans + " >> " + res);
	}
	system("clear");
	printf("%s\n", res.c_str());
	run("vim " + res);
	return 0;
}
