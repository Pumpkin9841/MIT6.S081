#include<kernel/types.h>
#include<user/user.h>

int main(int argc, char* argv[]) {
    int c2p[2];
    int p2c[2];
    char buf[512];
    // char buf2[512];
 
    //开启两个管道(child->parent, parent->child)
    pipe(c2p);
    pipe(p2c);
    //创建子进程
    int pid = fork();
    //如果当前为子进程
    if(pid == 0) {
        int currChildPid = getpid();
        read(p2c[0], buf, sizeof(buf));
        fprintf(1, "%d: %s", currChildPid, buf);
        write(c2p[1], "received ping\n", 14);
        
        close(p2c[0]);
        close(p2c[1]);
        close(c2p[0]);
        close(c2p[1]);
        
        exit(0);
    }
    //如果当前进程是父进程
    else {
        int currParentPid = getpid();
        write(p2c[1], "received pong\n", 14);
        //read(c2p[0], buf2, sizeof(buf2));
        read(c2p[0], buf, sizeof(buf));
        fprintf(1, "%d: %s", currParentPid, buf);
    
        close(p2c[0]);
        close(p2c[1]);
        close(c2p[0]);
        close(c2p[1]);
        
        exit(0);
    }
    
}