#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char buf[120];
    char* params[MAXARG];

    while ((gets(buf, 120) != 0)) {
        if (buf[0] == 0) { // THATS HOW WE ROLL EOF
            return 0;
        }
        buf[strlen(buf) - 1] = 0; // skip parsing

        if (fork() == 0) {
            int j = 0;
            for (int i = 1; i < argc; i++) {
                params[j++] = argv[i];
            }
            params[j++] = buf;
            params[j++] = 0;
            exec(params[0], params);
            fprintf(2, "exec failed\n");
        } else {
            wait(0);
        }
    }

    return 0;
}
