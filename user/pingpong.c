#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
        //parent pipe 
        int pfd[2];
        //child [o[e
        int cfd[2];

        char buf[10];
        int pid;

        pipe(pfd);
        pipe(cfd);

        if((pid = fork()) < 0) {
                fprintf(2,"fork error\n");
        
        }else if(pid ==0) {
                close(pfd[1]);
                close(cfd[0]);
                read(pfd[0],buf,4);
                printf("%d:received %s\n", getpid(),buf);
                write(cfd[1],"pong",4);
		close(cfd[1]);

        }else {
		close(pfd[0]);
		close(cfd[1]);
		write(pfd[1],"ping",4);

		close(pfd[1]);
		read(cfd[0],buf,4);
		printf("%d: received %s\n",getpid(),buf);
	
	}
	exit(0);
	

}
