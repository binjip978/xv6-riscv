#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    char message[1];
    int counter = 0;

    if (fork() == 0) {
        // child ping
        int child_pid = getpid();
        close(p1[1]);
        close(p2[0]);

        while (1) {
            write(p2[1], "C", 1);
            int n = read(p1[0], message, 1);
            if (n == 0) {
                exit(0); 
            }
            printf("%d: received pong\n", child_pid);
        }
    } else {
        // parent pong
        int parent_pid = getpid();
        close(p1[0]);
        close(p2[1]);
        while (1) {
            read(p2[0], message, 1);
            printf("%d: received ping\n", parent_pid);
            counter++;
            if (counter == 10) {
                exit(0);
            } 
            write(p1[1], "C", 1);
        }
    }

    exit(0);
}
