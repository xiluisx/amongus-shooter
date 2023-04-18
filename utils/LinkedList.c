#include <stdio.h>

struct node {
	int key;
	int value;
	struct node *next;
};

typedef struct node Node;

void printList(Node *head) {
	Node *curNode = head;
	while(curNode != NULL){
		printf("%i\n", curNode->value);
		curNode = curNode->next;
	}
}

int findLastIndex(struct node *node) {
	int curIdx = 0;
	struct node *curNode = node;
	printf("%i", curNode->value);
	while(curNode -> next != NULL) {
		curNode = node -> next;
		curIdx++;
	}
	return curIdx;
}
