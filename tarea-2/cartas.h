#ifndef _cartas_h
#define _cartas_h

// Define a struct for each card in the deck
typedef struct Card {
    int value;
} Card;

// Define a struct for a tree node that holds a card
typedef struct TreeNode {
    Card card;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Define a struct for the deck of cards that holds the root of the tree
typedef struct Deck {
    TreeNode *root;
} Deck;


// Function to create a new tree node for a card
TreeNode* newTreeNode(Card card);

// Function to insert a card into the tree
void insertCard(TreeNode** node, Card card);

// Function to create a new deck of cards
Deck* newDeck();

// Function to add a card to the deck
void addCard(Deck* deck, Card card);

// Function to print the cards in the deck using in-order traversal of the tree
void printDeck(TreeNode* node);

// Function to create a new card with a random suit and value
Card newRandomCard();

// Function to create a new deck of L cards
Deck* newRandomDeck(int L);

// Function to get the size of a binary search tree
int getSize(TreeNode* root);

// Function to find a card in a binary search tree by its index
TreeNode* findCard(TreeNode* root, int cardIndex);

// Gets the successor of a node
TreeNode* getSuccessor(TreeNode* node);

// Deletes a card by its value
void deleteCard(TreeNode** root, int value);

#endif