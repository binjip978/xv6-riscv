#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(int argc, char *argv[]) {
    printf("mytest program\n");
    int size = 8000;
    int *arr = (int *)malloc(sizeof(int) * size);

    uint64 res;
    int r;

    r = pgaccess((uint64)arr, 10, &res);
    if (r != 0) {
        printf("pgaccess error\n");
    }
    printf("mask: %x\n", res);

    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    r = pgaccess((uint64)arr, 10, &res);
    if (r != 0) {
        printf("pgaccess error\n");
    }
    printf("mask: %x\n", res);

    r = pgaccess((uint64)arr, 10, &res);
    if (r != 0) {
        printf("pgaccess error\n");
    }
    printf("mask: %x\n", res);

    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }

    r = pgaccess((uint64)arr, 10, &res);
    if (r != 0) {
        printf("pgaccess error\n");
    }
    printf("mask: %x\n", res);

    return 0;
}
