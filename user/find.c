#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char *path, char *pattern) {
    int fd;
    char buf[512];
    struct stat st;
    struct dirent de;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    int path_len = strlen(path);
    char *p;
    for (p = path + path_len; p >= path && *p != '/'; p--)
        ;
    p++;

    if (strcmp(p, pattern) == 0) {
        printf("%s\n", path);
    }

    switch (st.type) {
    case T_DEVICE:
        break;
    case T_FILE:
        break;
    case T_DIR:
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0) {
                continue;
            }
            if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                /* printf("skip: %s\n", de.name); */
                continue;
            }
            strcpy(buf, path);
            char *p = buf + path_len;
            *p++ = '/';
            memmove(p, de.name, DIRSIZ);
            /* printf("recurse on %s\n", buf); */
            find(buf, pattern);
        }
    }
    
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "usage: find dir pattern\n");
        exit(1);
    }

    find(argv[1], argv[2]);
    return 0;
}


