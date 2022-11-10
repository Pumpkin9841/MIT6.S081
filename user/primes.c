#include<kernel/types.h>
#include<user/user.h>

int main(int argc, char* argv[]) {
    //设置管道
    int p[2];
    pipe(p);

    for(int i = 2; i <= 35; i++) {
        write(p[1], &i, sizeof(int));
    }

    if(fork() == 0) {
        int data;
        //在读管道前把 管道的 写端p[1] 关闭，则while读会在无数据读后返回0 
        //否则，在while读时 管道的写端p[1]没有关闭， 则while读会在无数据读后阻塞
        close(p[1]);
        while(read(p[0], &data, sizeof(int)) == sizeof(int)) {
            if(data == 2) {
                fprintf(1, "prime %d\n", data);
                continue;
            }
            int flag = 0;
            for(int j = 2; j < data; j++) {
                if(data % j == 0) {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) {
                fprintf(1, "prime %d\n", data);
            }
            
        }
        close(p[0]);
        exit(0);
    }
    else {
        close(p[0]);
        close(p[1]);
        wait(0);
    }

    exit(0);

}