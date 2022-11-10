#include<kernel/types.h>
#include<user/user.h>

int 
main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(1,"sleep command argc must equal 1");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}

