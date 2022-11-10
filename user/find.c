#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char* path, char* fileName) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    strcpy(buf, path);
    p = buf + strlen(buf);
    //加/ 表示是目录
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
        //fprintf(2, "path %s\n", buf);
        if(de.inum == 0) {
            continue;
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        
        if(stat(buf, &st) < 0) {
            fprintf(2, "find: cannot stat %s\n", buf);
            continue;
        }


         //不在.和..文件夹中递归
        if(st.type == T_DIR && strcmp("." , de.name) != 0 && strcmp("..", de.name) != 0 ) {
          //  fprintf(2, "Dir: %s\n", buf);
            find(buf, fileName);
        }
        else if(strcmp(fileName, de.name) == 0) {
            printf("%s\n", buf);
        }
    }
    close(fd);
    
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("wrong arguments\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}