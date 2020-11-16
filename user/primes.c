#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define STDDER_FILENO 2

#define READEND 0
#define WRITEEND 1


int main(void) {
	int numbers[36];
	int fd[2];
	int i;
	int index = 0;

	int pid;

	for(i = 2; i <= 35; i +=1) {
		numbers[index] = i;
		index += 1;

	
	}

	while(index > 0) {

		pipe(fd);

		if((pid = fork()) < 0) {
			fprintf(2,"fork error\n");
			exit(0);
		}
		else if (pid > 0) {
			//parent progress
			close(fd[0]);
			for( i = 0; i < index; i ++) {
				write(fd[1], &numbers[i], sizeof(numbers[i]));

			
			}
			close(fd[1]);
			wait((int *)0);
			exit(0);

		
		}
		
		
		else {
		

			close(fd[1]);
			int prime = 0;
			int temp = 0;
		       	index = -1;
		       	while((read(fd[0], &temp, sizeof(temp))) != 0) {
		
				if(index < 0) {
					index ++;
					prime = temp; 
				} else {
					if(temp % prime != 0) {
						numbers[index++] = temp;
					
					}
				
				}
			}
			printf("primes %d\n", prime);
			close(fd[0]);
			


		}



	}
	exit(0);

}





