/*
 * =====================================================================================
 *
 *       Filename:  convertHeader.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/28/2020 10:04:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andy (), andy_y_li@163.com
 *        Company:
 *
 * =====================================================================================
 */

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "out.h"

using namespace std;

#define _BITSET(x) ((1) << (x))
#define OPT_SET_SRC_FILE _BITSET(0)

#define MAX_PATH_LENGTH 256

int main(int argc, char* argv[]) {
    int flag = 0;
    int opt;
    char filename[MAX_PATH_LENGTH];
    char destfilename[MAX_PATH_LENGTH];
    destfilename[0] = '\0';
    while ((opt = getopt(argc, argv, "s:d:h")) != -1) {
        switch (opt) {
            case 's':
                sprintf(filename, "%s", optarg);
                flag |= OPT_SET_SRC_FILE;
                break;
            case 'd':
                sprintf(destfilename, "%s", optarg);
                break;
            case 'h':
                printf(
                    "version: stcHeader/1.0.0\n"
                    "Usage: stcHeader [-h] [ -s source_header] [ -d "
                    "dest_header] \n"
                    "-h\t\t\t: this help\n"
                    "-s\t\t\t: source header\n"
                    "-d\t\t\t: dest header(default: stdout)\n"
                    "github:https://github.com/andy-y-li/stcHeader.git"
                    "\n\n");
                return 0;
            case '?':
                printf("invalid option: %c\n", optopt);
                return -1;
        }
    }

    if (!(flag & OPT_SET_SRC_FILE)) {
        fprintf(stderr, "no source header file\n");
        exit(1);
    }

    ifstream file_in(filename);
    Out outfile = Out(destfilename);

    string s;
    string previous_addr;
    bool isComment = false;
    while (getline(file_in, s)) {
        if (s[0] == '/' || s[0] == '#'){
            if (s == "/*") {
                isComment = true;
            }
            outfile << s << "\n";
            continue;
        }
        else if (s == "*/") {
            outfile << s << "\n";
            isComment = false;
            continue;
        }
        else if (isComment) {
            outfile << s << "\n";
            continue;
        }
        else if (s.length() > 4) {
            string::size_type type_end = s.find_first_of(' ');
            string type = s.substr(0, type_end);

            string::size_type name_begin = s.find_first_not_of(' ', type_end);
            string::size_type name_end = s.find_first_of(' ', name_begin);
            string name = s.substr(name_begin, name_end - name_begin);

            string::size_type addr_begin = s.find_first_not_of(" =", name_end);
            string::size_type addr_end = s.find_first_of(" ;", addr_begin);
            string addr = s.substr(addr_begin, addr_end - addr_begin);

            string comment;
            bool haveComment = true;
            if (addr_end == s.length() - 1) {
                haveComment = false;
            }

            if (haveComment) {
                string::size_type comment_begin =
                    s.find_first_not_of("; ", addr_end);
                comment = s.substr(comment_begin);
            }

            if (type == "sfr") {
                outfile << "SFR(" << name << ", " << addr << ");";
                if (haveComment) outfile << comment;
                outfile << "\n";
                previous_addr = addr;
            } else if (type == "sbit") {
                string bit_offset = addr.substr(addr.length() - 1);

                outfile << "SBIT(" << name << ", " << previous_addr << ", "
                        << bit_offset << ");";
                if (haveComment) outfile << comment;
                outfile << "\n";
            }
        }
    }
    return 0;
}

