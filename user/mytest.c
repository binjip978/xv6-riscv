#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    printf("mytest program\n");
    int res = noop();
    printf("noop: %d\n", res);
    return 0;
}
