#include <stdio.h>
#include "utils/LinkedList.h"

int main(int argc, char *argv[])
{
	Node head;	
	Node node1;
	Node node2;

	head.value = 0;
	node1.value = 1;
	node2.value = 2;

	head.next = &node1;
	node1.next = &node2;

	printList(&head);

	printf("Fin");

	return 0;
}
