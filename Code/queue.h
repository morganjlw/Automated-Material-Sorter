// Linked List Queue Header File

#ifndef QUEUE_H
#define QUEUE_H
/* LinkedQueue.h */

/* Type definitions */
struct node {
	int item; 	/* stores a number describing the element */
	struct node *next;

	//char stage; 	/* 0: part is built, 1: part not built, 2: part is shipped */
};

struct Queue{
	struct node *head;
	int size;
};

// Global Structure
struct Queue q;

// Prototypes
void queueInit(struct Queue *q);
int front(struct Queue *q) ;
void pop (struct Queue *q);
void push (struct Queue *q, int data);
int queueSize(struct Queue *q);

#endif //QUEUE_H