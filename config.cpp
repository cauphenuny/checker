#include "config.h"
using namespace std;

void store_data(int T, std::string data, std::string sc1, std::string sc2, std::string prob, int time) {
    std::string file = config_dir + prob;
    //std::string file = config_dir + prob + ".cfg";
    ofstream filestream(file.c_str());
    filestream << T << endl << data << endl << sc1 << endl << sc2 << endl << prob << endl << time << endl;
    filestream.close();
}

void load_data(int &T, std::string &data, std::string &sc1, std::string &sc2, std::string prob, int &time) {
    std::string infile_old = prob + ".cfg";
    std::string infile = prob;
    if (access(infile_old.c_str(), F_OK) == 0) {
        run("mv " + infile_old + " " + infile);
    }
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
