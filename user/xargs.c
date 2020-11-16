#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"



#define MAXLINES 1024

int main(int argc, char *argv[]) {
	char line[MAXLINES];
	//MAXAGR decleared in "kernel/papam.h"
	char* params[MAXARG];

	int n;
	int args_index = 0;
	int i;

	char* cmd = argv[1];

	for( i = 1; i < argc; i += 1) {
		params[args_index] = argv[i];
		args_index ++;

	
	}

   while ((n = read(0, line, MAXLINES)) > 0)
    {
        if (fork() == 0) // child process
        {
            char *arg = (char*) malloc(sizeof(line));
            int index = 0;
            for (i = 0; i < n; i++)
            {
                if (line[i] == ' ' || line[i] == '\n')
                {
                    arg[index] = 0;
                    params[args_index++] = arg;
                    index = 0;
                    arg = (char*) malloc(sizeof(line));
                }
                else arg[index++] = line[i];
            }
            arg[index] = 0;
            params[args_index] = 0;
            exec(cmd, params);
        }
        else wait((int*)0);
    }
    exit(0);
}
