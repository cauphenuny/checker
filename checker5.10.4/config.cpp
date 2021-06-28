/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "config.h"
using namespace std;

static string config_version = "v1";

void store_data(map<string, string> config) {
    std::string file = config_dir + config["prob"];
    //std::string file = config_dir + prob + ".cfg";
    ofstream filestream(file.c_str());
    filestream << "config_version" << ": " << config_version << endl;
    for (auto it : config) {
        filestream << it.first << " = " << it.second << endl;
    }
    filestream.close();
}

void load_data(map<string, string> &config, string prob) {
    std::string infile = config_dir + prob;
    //cerr << infile << endl;
    try {
        ifstream filestream(infile.c_str());
        if (filestream.fail()) {
            throw RED "\033[Ano such problem!" NONE;
        }
        std::string str, key, value;
        while (getline(filestream, str)) {
            //fprintf(stderr, "load %s\n", str.c_str());
            analysis_key_value(str, key, value);
            //fprintf(stderr, "analysised: %s - %s\n", key.c_str(), value.c_str());
            config[key] = value;
        }
        filestream.close();
        if (config["config_version"] != config_version) {
            throw "\033[Aconfig version not matched, please run " RED "checker --clear" NONE " !";
        }
    } catch (const char *msg) {
        cout << msg << endl;
        exit(1);
    }
}

bool check_file(std::string prob) {
    std::string infile_old = prob + ".cfg";
    std::string infile = prob;
    if (access(infile_old.c_str(), F_OK) == 0) {
        run("mv " + infile_old + " " + infile);
    }
    ifstream filestream(infile.c_str());
    if (filestream.fail()) {
        filestream.close();
        return 0;
    } else {
        filestream.close();
        return 1;
    }
}
