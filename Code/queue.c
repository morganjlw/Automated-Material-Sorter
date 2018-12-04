/* Queue method file */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void queueInit(struct Queue *q) {
	q->head = NULL;
	q->size = 0;
}

int front(struct Queue *q)
{
	return q->head->item;
}

int queueSize(struct Queue *q)
{
	
	return q->size;
}

void pop(struct Queue *q) {
	// Decrement size...
	if (q->size == 0)
	{
		q->size = 0;
		return;
	}
	
	q->size--;
	struct node *tmp = q->head;
	q->head = q->head->next;
	free(tmp);
}

void push(struct Queue *q, int data) {
	// Increment queue size
	q->size++;

	// Element used to traverse queue
	struct node *current = q->head;

	if (q->head == NULL) {
		q->head = (struct node *) malloc(sizeof(struct node));
		q->head->item = data;
		q->head->next = NULL;
		//q->tail = q->front;
	}
	else {
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = (struct node *) malloc(sizeof(struct node));
		current->next->item = data;
		current->next->next = NULL;
	}
}