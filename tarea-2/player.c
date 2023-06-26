#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cartas.h"
#include "player.h"

// Constructor for the Player struct
Player* newPlayer(int numCards) {
    // Allocate memory for the new player struct
    Player* player = malloc(sizeof(Player));

    // Generate a new deck of cards for the player
    player->deck = newRandomDeck(numCards);

    // Initialize the other struct fields
    player->numCards = numCards;
    player->numPoints = 0;
    player->isTurn = false;

    return player;
}

// Prints player information
void printPlayer(Player *player) {
    printf("Tus cartas actuales: ");
    printDeck(player->deck->root);
    printf("(Elige tu carta por su indice)\n");
}

// Helper function to traverse the tree using an inorder traversal and add each card's index to an array
void inorderTraversal(TreeNode* node, int* cardsArray, int* index) {
    if (node == NULL) {
        return;
    }

    inorderTraversal(node->left, cardsArray, index);

    cardsArray[*index] = node->card.value;
    (*index)++;

    inorderTraversal(node->right, cardsArray, index);
}

// Function to get an array of integers representing the cards in a player's deck
int* getCardsArray(Player* player) {
    int numCards = player->numCards;
    int* cardsArray = (int*)malloc(numCards * sizeof(int));

    // Traverse the tree using an inorder traversal and add each card's index to the array
    int index = 0;
    inorderTraversal(player->deck->root, cardsArray, &index);

    return cardsArray;
}

