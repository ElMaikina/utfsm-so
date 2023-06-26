#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include "cartas.h"

// Function to create a new tree node for a card
TreeNode* newTreeNode(Card card) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->card = card;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a card into the tree
void insertCard(TreeNode** node, Card card) {
    if (*node == NULL) {
        *node = newTreeNode(card);
        return;
    }
    if (card.value < (*node)->card.value) {
        insertCard(&(*node)->left, card);
    } else {
        insertCard(&(*node)->right, card);
    }
}

// Function to create a new deck of cards
Deck* newDeck() {
    Deck* deck = (Deck*)malloc(sizeof(Deck));
    deck->root = NULL;
    return deck;
}

// Function to add a card to the deck
void addCard(Deck* deck, Card card) {
    insertCard(&deck->root, card);
}

// Function to print the cards in the deck using in-order traversal of the tree
void printDeck(TreeNode* node) {
    if (node != NULL) {
        printDeck(node->left);
        printf("%d ", node->card.value);
        printDeck(node->right);
    }
}

// Function to create a new card with a random suit and value
Card newRandomCard() {
    Card card;
    card.value = rand() % 44 + 1;
    return card;
}

// Function to create a new deck of L cards
Deck* newRandomDeck(int L) {
    Deck* deck = newDeck();
    for (int i = 0; i < L; i++) {
        Card newcard = newRandomCard();
        addCard(deck, newcard);
    }
    return deck;
}

// Function to get the size of a binary search tree
int getSize(TreeNode* root) {
    if (root == NULL) {
        // If the root is NULL, the size of the subtree is 0
        return 0;
    } else {
        // Otherwise, the size of the subtree is the sum of the sizes of the left and right subtrees,
        // plus one for the root node
        return getSize(root->left) + getSize(root->right) + 1;
    }
}

// Function to find a card in a binary search tree by its index
TreeNode* findCard(TreeNode* root, int cardIndex) {
    // Initialize a counter to keep track of the index of each card in the tree
    int count = 0;

    // Traverse the tree until we find the card with the specified index
    while (root != NULL) {
        // Calculate the index of the current node's card
        int currentCardIndex = count + getSize(root->left);

        // Compare the current node's card index with the target index
        if (cardIndex == currentCardIndex) {
            // We've found the node with the target index, so return it
            return root;
        } else if (cardIndex < currentCardIndex) {
            // The target index is less than the current node's card index,
            // so search the left subtree
            root = root->left;
        } else {
            // The target index is greater than the current node's card index,
            // so search the right subtree
            count = currentCardIndex + 1;
            root = root->right;
        }
    }

    // If we reach this point, the target index was not found in the tree
    return NULL;
}

// Gets the successor of a node
TreeNode* getSuccessor(TreeNode* node) {
    TreeNode* current = node->right;
    while (current != NULL && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Deletes a card by its value
void deleteCard(TreeNode** root, int value) {
    // Find the node containing the card
    TreeNode* node = findCard(*root, value);

    // If the card is not in the deck, return
    if (node == NULL) {
        return;
    }

    // If the node has no children, simply delete it
    if (node->left == NULL && node->right == NULL) {
        free(node);
        *root = NULL;
    }

    // If the node has only one child, replace it with that child
    else if (node->left == NULL) {
        TreeNode* temp = node->right;
        free(node);
        *root = temp;
    }
    else if (node->right == NULL) {
        TreeNode* temp = node->left;
        free(node);
        *root = temp;
    }

    // If the node has two children, replace it with its successor
    else {
        TreeNode* successor = getSuccessor(node);
        node->card = successor->card;
        deleteCard(&(node->right), successor->card.value);
    }
}

