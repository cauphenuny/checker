/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "command.h"
using namespace std;

void usage(int id) {
    puts("usage: ");
    puts("\nchecker [$problem_name] [-hscqvu] [--save=] [--branch=] [--mode=]\n");
    puts("-h: display this help and quit");
    puts("-s: slow mode");
    puts("-c: always continue when error occurs");
    puts("-q: always quit when error occurs");
    puts("-v: check version and quit");
    puts("-u: update\n");
    puts("--save=auto             save file only when error occurs (default)");
    puts("       always           always save input and output file");
    puts("       never            never save file\n");
    puts("--branch=master         default branch");
    puts("         dev            developing branch, new and experimental\n");
    puts("--mode=normal           normal mode(default)");
    puts("       data             data mode\n");
    puts("--config:$problem_name  change problem config directly by vim\n");
    puts("--clear                 delete all checker files(.config/, .data/)");
    if (branch != "master") printf(BOLD "\n%s" NONE " <%s>\n", version.c_str(), branch.c_str());
    else printf(BOLD "\n%s\n" NONE, version.c_str());
    printf("compiled at %s %s\n", __TIME__, __DATE__);
    start_update();
    exit(id);
}

void check_version() {
    if (branch != "master") printf(BOLD "%s" NONE " <%s>\n", version.c_str(), branch.c_str());
    else                    printf(BOLD "%s\n" NONE, version.c_str());
    printf("compiled at %s %s\n", __TIME__, __DATE__);
    start_update();
    exit(0);
}

bool isword(char c) {
    return isalpha(c) || isdigit(c) ||
        (c == '_') || (c == '.') || (c == '-') || c == ('+');
}

string getword(string s, int &pos) {
    string res = "";
    while (isword(s[pos]))
        res += s[pos], pos++;
    return res;
}

void edit_configure(string prob) {
    if (access(string(config_dir + prob).c_str(), F_OK) != 0) {
        puts(RED "No such problem!" NONE);
        exit(1);
    } else {
        exit(run("vim " + config_dir + prob));
    }
}

bool analysis_key_value(string src, string &key, string &value) {
    int pos = 0;
    key = getword(src, pos);
    while (!isword(src[pos]) && pos < (int)src.length() - 1) pos++;
    value = getword(src, pos);
    return 0;
}

bool analysis_key_value(string src, string &key, string &value, int &pos) {
    key = getword(src, pos);
    while (!isword(src[pos]) && pos < (int)src.length() - 1) pos++;
    value = getword(src, pos);
    return 0;
}

bool clear_all_file() {
    exit(run("rm -r ./" + config_dir) | run("rm -r ./" + data_dir));
}

void analysis_long_cmd(string s, int &pos) {
    pos++;
    string key, value;
    analysis_key_value(s, key, value, pos);
    if (key == "save") {
        if (value == "always") {
            save_mode = 1;
        } else if (value == "auto") {
            save_mode = 2;
        } else if (value == "never") {
            save_mode = 3;
        } else {
            printf("Invalid save mode " RED "%s" NONE " !\n", value.c_str());
            printf("Try 'checker -h' to learn more info.\n");
            start_update();
            exit(1);
        }
    } else if (key == "branch") {
        branch = value;
        printf("changed branch to <%s>.\n", branch.c_str());
        start_forced_update();
    } else if (key == "mode") {
        if (value == "normal") {
            general_mode = 1;
        } else if (value == "data") {
            general_mode = 2;
        } else {
            printf("Invalid mode " RED "%s" NONE " !\n", value.c_str());
            printf("Try 'checker -h' to learn more info.\n");
            start_update();
            exit(1);
        }
    } else if (key == "config") {
        edit_configure(value);
    } else if (key == "clear") {
        clear_all_file();
    } else {
        printf("Invalid option " RED "--%s" NONE " !\n", key.c_str());
        printf("Try 'checker -h' to learn more info.\n");
        start_update();
        exit(1);
    }
}

void analysis_cmd(string cmd)  {
    for (int i = 1; i < (int)cmd.length(); i++) {
        switch (cmd[i]) {
            case 'c': always_continue = 1, always_quit = 0; break;
            case 'q': always_continue = 0, always_quit = 1; break;
            case 'v': check_version(); break;
            case 's': fast_mode = 0; break;
            case 'u': start_forced_update(); break;
            case 'h': usage(0); break;
            case '-': analysis_long_cmd(cmd, i), i--; break;
            default:
                printf("Invalid option " RED "-%c" NONE " !\n", cmd[i]);
                printf("Try 'checker -h' to learn more info.\n");
                start_update();
                exit(1);
                break;
        }
    }
}
