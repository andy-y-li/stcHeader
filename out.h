/*
 * =====================================================================================
 *
 *       Filename:  out.h
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

#ifndef __OUT_H
#define __OUT_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

class Out {
    int handle;
    bool noisy;

   public:
    Out(const char *filename);
    ~Out();
    void setHandle(int fd);
    int setHandle(const char *filename);
    int getHandle();
    void on();
    void off();
    int print(const char *str);
    int get(char *destr);
    Out &operator<<(const string &s);
    Out &operator<<(const char &c);
};

#endif  // #ifndef __OUT_H
