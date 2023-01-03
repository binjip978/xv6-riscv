#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(int argc, char *argv[]) {
    printf("mytest program\n");
    int my_pid = ugetpid();
    printf("my_pid: %d\n", my_pid);
    return 0;
}
