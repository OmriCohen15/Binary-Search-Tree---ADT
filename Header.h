#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef Header
#define Header


/* Some necessary type definitions */
typedef struct Tree* PTree;
typedef enum BOOL { FALSE, TRUE }BOOL;

/* Function Pointers */
typedef int(*Compare) (void* a, void* b);
typedef void(*Print)(void* key, FILE* out);
typedef void(*inorderPF)(PTree root, FILE* out, Print pf);
typedef void(*preorderPF)(PTree root, FILE* out, Print pf);
typedef int(*printSmallFunc)(PTree root, FILE* out, Print pf, int k);
typedef void(*freeElem)(void* key);

/* Interface functions */
void create_tree_node(void* key, PTree* root, PTree* original_head, FILE* out, Print pf, freeElem specific_free);
BOOL AddTreeNode(PTree* root, PTree* original_head, void* key, FILE* out, Compare cmp, Print pf, freeElem specific_free);
void printSearch(PTree root, char ch, FILE* out, Print pf, inorderPF in, preorderPF pre);
void inorderPrint(PTree root, FILE* out, Print pf);
void preorderPrint(PTree root, FILE* out, Print pf);
int treeHight(PTree root);
void findMin(PTree root, FILE* out, Print pf);
void checkK(int k, PTree root, printSmallFunc printsmall, int countNodes, FILE* out, Print pf);
int printSmallKeys(PTree root, FILE* out, Print pf, int k);
void empty_tree(PTree root, freeElem specific_free);
#endif