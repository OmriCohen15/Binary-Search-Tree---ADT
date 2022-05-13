#include "Header.h"

void printFloat(void* key, FILE* out) {
	fprintf(out, "%g ", *(float*)key);
}

int cmp_flt(void* a, void* b) {
	if (*(float*)a > *(float*)b) return 1;
	else {
		if (*(float*)a == *(float*)b) return 0;
		else return -1;
	}
}

void free_flt(void* key) {
	free(key);
}

void main() {
	FILE* instruc, * out;
	int choise = 0, counter_Nodes = 0, k;
	float* key;
	char ch;
	PTree root = NULL;
	instruc = fopen("Instructions.txt", "r");
	if (instruc == NULL)
		exit(1);
	out = fopen("output.txt", "w");
	if (out == NULL)
		exit(1);

	while (fscanf(instruc, "%d", &choise) != -1) {
		switch (choise)
		{
		case 1:
			if ((key = (float*)malloc(sizeof(float))) == NULL) {
				fprintf(out, "Allocation Error");
				empty_tree(root, free_flt);
				exit(1);
			}
			fscanf(instruc, "%f", key);
			//we need to dynamic allocate key pointer because we want to send to each node a different address of keys and not the same one
			if (AddTreeNode(&root, &root, key, out, cmp_flt, printFloat, free_flt)) counter_Nodes++;
			break;
		case 2:
			fscanf(instruc, " %c", &ch);
			printSearch(root, ch, out, printFloat, inorderPrint, preorderPrint);
			break;
		case 3:
			fprintf(out, "\nThe height of your tree is: %d", treeHight(root));
			break;
		case 4:
			findMin(root, out, printFloat);
			break;
		case 5:
			fscanf(instruc, "%d", &k);
			checkK(k, root, printSmallKeys, counter_Nodes, out, printFloat);
			break;
		default:
			fprintf(out, "\nWrong number of function to excute");
			break;
		}
	}
	empty_tree(root, free_flt);
	fclose(instruc);
	fclose(out);
}
