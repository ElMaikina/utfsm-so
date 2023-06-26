#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int num_players = 4;

    int i, pid;
    for (i = 0; i < num_players; i++) {
        pid = fork();
        if (pid == 0) 
        {
            printf("Player %d: I am the child process with pid %d\n", i+1, getpid());
            exit(0);
        }
        else if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        }
    }
    for (i = 0; i < num_players; i++) {
        wait(NULL);
    }

    return 0;
}