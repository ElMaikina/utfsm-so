#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cartas.h"
#include "player.h"

#define JUGADORES 4
#define TURNOS 10
#define CARTAS 10

int main() {
    // Array to hold process IDs of child players
    Player* jugadores[JUGADORES];

    int turns = 10;
    
    for (int i = 0; i<JUGADORES; i++) {
        jugadores[i] = newPlayer(CARTAS);
    }
    pid_t player_pids[JUGADORES];

    while (turns > 0){
        pid_t parent_pid = -1;

        // Loop to create child processes for each player
        for (int i = 0; i < JUGADORES; i++) {
            pid_t pid = fork();
            
            if (pid < 0) {
                // Error handling
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid > 0 && parent_pid == -1) {
                parent_pid = getpid();
                int num;
                printf("\nTurno del Jugador 1 (Tu)... ");
                printPlayer(jugadores[0]);
                scanf("%d", &num);
            }
            else if (pid == 0) {
                int status;
                if (i != 0)
                    printf("Turno del Jugador %d...\n", i+1);
                    
                waitpid(player_pids[0], &status, 0);
                exit(EXIT_SUCCESS);
            } 
            else {
                // Parent process (game manager)
                player_pids[i] = pid;
            }
        }

        // Wait for all child processes to exit
        int status;
        for (int i = 0; i < JUGADORES; i++) {
            waitpid(player_pids[i], &status, 0);
        }
        turns--;
    }
    return 0;
}
