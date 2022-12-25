#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(int argc, char *argv[]) {
    printf("mytest program\n");
    struct sysinfo info;
    if (sysinfo(&info) < 0) {
        return -1;
    }

    printf("nproc: %d, memfree: %d\n", info.nproc, info.freemem);
    return 0;
}
