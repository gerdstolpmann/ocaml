#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

extern void caml_startup(char **argv);


void init(void) {
    char *progname;
#ifdef __linux__
    char buf[PATH_MAX];
#endif
    char *argv[2];
    progname = NULL;
#ifdef __APPLE__
    progname = (char *) getprogname();
#endif
#ifdef __linux__
    if (readlink("/proc/self/exe", buf, PATH_MAX) >= 0) {
        progname = buf;
    }
#endif
    if (progname == NULL) progname = "/unknown/program/name";
    argv[0] = progname;
    argv[1] = NULL;
    caml_startup(argv);
}
