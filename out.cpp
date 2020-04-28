/*
 * =====================================================================================
 *
 *       Filename:  out.cpp
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

#include "out.h"

Out::Out(const char *filename) {
    if (filename == NULL || strlen(filename) == 0) {
        handle = STDOUT_FILENO;
        noisy = true;
        return;
    }
    handle = open(filename, O_CREAT | O_RDWR | O_APPEND, FILE_MODE);
    noisy = true;
}

Out::~Out() { close(handle); }

void Out::setHandle(int fd) { handle = fd; }

int Out::setHandle(const char *filename) {
    if ((handle = open(filename, O_CREAT | O_RDWR | O_APPEND, FILE_MODE)) < 0) {
        perror(filename);
        return errno;
    }
    return 0;
}

int Out::getHandle() { return handle; }

void Out::on() { noisy = true; }

void Out::off() { noisy = false; }

int Out::print(const char *str) {
    if (noisy == false) {
        return 0;
    }

    if (handle < 0) {
        return -1;
    }

    if ((write(handle, str, strlen(str))) != (int)strlen(str)) {
        return errno;
    }

    return 0;
}

int Out::get(char *destr) {
    if (handle < 0) {
        return -1;
    }

    lseek(handle, 0, SEEK_SET);
    if ((read(handle, destr, 1024)) < 0) {
        return errno;
    }

    return 0;
}

Out &Out::operator<<(const string &s) {
    this->print(s.c_str());
    return *this;
}

Out &Out::operator<<(const char &c) {
    char s[2];
    sprintf(s, "%c", c);
    this->print(s);
    return *this;
}

