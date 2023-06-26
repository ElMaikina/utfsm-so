#ifndef _player_h
#define _player_h

#include "cartas.h"
#include <stdbool.h>

typedef struct Player {
    Deck* deck;         // Pointer to the player's deck of cards
    int numCards;       // Number of cards the player has
    int numPoints;      // Number of points the player has
    bool isTurn;        // Boolean variable to indicate if it's the player's turn
} Player;

// Constructor for the Player struct
Player* newPlayer(int numCards);

// Prints player info
void printPlayer(Player *player);

// Helper function to traverse the tree using an inorder traversal and add each card's index to an array
void inorderTraversal(TreeNode* node, int* cardsArray, int* index);

// Function to get an array of integers representing the cards in a player's deck
int* getCardsArray(Player* player);

#endif