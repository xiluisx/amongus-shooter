struct node {
	int key;
	int value;
	struct node *next;
};

typedef struct node Node;

void printList(struct node *node);

int findLastIndex(struct node *node);
