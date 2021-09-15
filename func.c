#include "Header.h"
#define Max(a,b) ((a) > (b)? (a): (b)) 

typedef struct Tree {
	struct Tree* right;
	struct Tree* left;
	void* key;
}*PTree;

/*The function gets pointer to the head of the root of a given tree and void* pointer to key and frees them*/
void empty_tree(PTree root, freeElem specific_free) {
	if (root == NULL) return;
	empty_tree(root->left, specific_free);
	empty_tree(root->right, specific_free);
	specific_free(root->key);
	free(root);
}

void create_tree_node(void* key, PTree *root, PTree* original_head, FILE* out, Print pf, freeElem specific_free) {
	*root = (PTree)malloc(sizeof(struct Tree));
	if (root != NULL) {
		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->key = key;
		fprintf(out, "\n");
		pf(key, out);
		fprintf(out, " was added to the tree");
	}
	else {
		fprintf(out, "Allocation Error");
		empty_tree(*original_head, specific_free);                    /*deleting the whole tree,since root_original is a pointer to the whole tree*/
		exit(1);
	}
}
				//   &head
/*The function get root to tree we want to append element for and the key we want to add, pointer to specific function that compares between 2 element, and print function
  The function addes the element by the rules of binary search tree and return TRUE in case of SUCCESS and FALSE if FAILOUR*/
BOOL AddTreeNode(PTree* root, PTree* original_head, void* key, FILE* out, Compare cmp, Print pf, freeElem specific_free) {
	static int times;	
	if (*root == NULL) {								//if the tree is empty
		create_tree_node(key, root, original_head, out, pf, specific_free);			//get new node for tree
		if (times == 0) {
			*original_head = *root;
		}
	}
	else
	{
		if (cmp((*root)->key, key) == 0) {
			fprintf(out, "\nError");
			return FALSE;
		}
		else {
			if (cmp((*root)->key, key) == 1) 						//if the new node's key is smaller			
				AddTreeNode(&((*root)->left), original_head, key, out, cmp, pf, specific_free); 	//call insert_node with the left child
			else
				AddTreeNode(&((*root)->right), original_head, key, out, cmp, pf, specific_free);
		}
	}
	times++;
	return TRUE;
}


/*The function get char to print the tree - 'i' inorder traverse or 'p' preorder traverse and spesific print funtcion and pointer to file to print it in it*/
void printSearch(PTree root, char ch, FILE* out, Print pf, inorderPF in, preorderPF pre) {
	if (ch == 'i') {
		fprintf(out, "\nInorder: ");
		in(root, out, pf);
	}
	else {
		if (ch == 'p') {
			fprintf(out, "\nPreorder: ");
			pre(root, out, pf);
		}
		else fprintf(out, "\nError");
	}
}
/*The function gets pointer to root of tree, pointer to file and pointer to spesific print funtcion and prints the tree i 'inorder' traverse*/
void inorderPrint(PTree root, FILE* out, Print pf) {
	if (root == NULL) {
		return;
	}
	inorderPrint(root->left, out, pf);
	pf(root->key, out);
	inorderPrint(root->right, out, pf);
}

/*The function gets pointer to root of tree, pointer to file and pointer to spesific print funtcion and prints the tree i 'preorder' traverse*/
void preorderPrint(PTree root, FILE* out, Print pf) {
	if (root == NULL) {
		return;
	}
	pf(root->key, out);
	preorderPrint(root->left, out, pf);
	preorderPrint(root->right, out, pf);
}

int treeHight(PTree root) // returns the hight of a given tree
{
	if (root == NULL)
		return -1;
	return 1 + Max(treeHight(root->left), treeHight(root->right));
}

/*The function gets pointer to root of tree, pointer to file and pointer to spesific print funtcion and prints the minimal key inside the tree*/
void findMin(PTree root, FILE* out, Print pf) {
	while (root->left != NULL) {
		root = root->left;
	}
	fprintf(out, "\nThe minimum is ");
	pf(root->key, out);
}
/*The function gets root of tree, 'k' as the number of smallest values we want to print, counterNodes to check if 'k' is valid and no bigger than the exciting number of node inside the tree to print
  pointer to file to print those numbers and 2 pointer to function - one specific print function and the other pointer 'printsmall' to search inside the tree for the smallest values*/
void checkK(int k, PTree root, printSmallFunc printsmall, int countNodes, FILE* out, Print pf) {
	if (k <= 0) fprintf(out, "\nError");
	else {
		if (countNodes >= k) {
			fprintf(out, "\nThere are %d small elements in this tree: ", k);
			printsmall(root, out, pf, k);
		}
		else
			fprintf(out, "\nThere are no %d elements in this tree", k);
	}
}


/*The function gets pointer to root of tree, pointer to file and pointer to spesific print funtcion and prints the 'k' small keys inside the tree by increasing order*/
int printSmallKeys(PTree root, FILE* out, Print pf, int k) {
	if (root == NULL) {
		return k;
	}
	if (k == 0) return 0;
	else {
		if (k > 0) {
			k = printSmallKeys(root->left, out, pf, k);
		}
		if (k > 0) {
			pf(root->key, out);
			k--;
		}
		if (k > 0) {
			k = printSmallKeys(root->right, out, pf, k);
		}
		return k;
	}
}