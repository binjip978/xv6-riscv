#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void primes(int inbox, int until) {
    char b[1];
    int create_next = 1;
    int first_ack = 0;
    int p[2];
    int first;
    pipe(p);

    while (1) {
        read(inbox, b, 1);
        int d = b[0];
        if (d == until && create_next) {
            return;
        }
        if (d == until) {
            b[0] = d;
            write(p[1], b, 1);
            close(p[1]);
            wait(0);
            return;
        }

        if (!first_ack) {
            printf("number: %d\n", d);
            first_ack = 1;
            first = d;
        }

        if (d % first == 0) {
            continue; // drop a number
        }

        if (create_next) {
            if (fork() == 0) {
                close(p[1]);
                primes(p[0], until);
                return;
            }
            create_next = 0;
            close(p[0]);
        }

        b[0] = d;
        write(p[1], b, 1);
    }
}

int main() {
    int p[2];
    pipe(p);
    int until = 35;

    if (fork() == 0) {
        close(p[1]);
        primes(p[0], until);
        return 0;
    } else {
        char b[1];
        close(p[0]);

        for (int i = 2; i <= until; i++) {
            b[0] = i;
            write(p[1], b, 1);
        }
        wait(0);
        return 0;
    }
}
