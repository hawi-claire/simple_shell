#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024
#include <stddef.h>
#include <errno.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char **argv, char **env);
#endif /* MAIN_H */
