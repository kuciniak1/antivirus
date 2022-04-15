#pragma once
#include <linux/limits.h>

typedef struct queue_node queue_node;

typedef struct queue queue;

struct queue_node {
  char file_path[PATH_MAX];
  struct queue_node *next_queue_node;
};

struct queue {
  int amount_of_queue_nodes;
  queue_node *front;
  queue_node *tail;
};

queue *init(queue *q);

int is_empty(queue **q);

void enqueue(queue **q, char path[]);

void dequeue(queue **q, char path[]);

void print_q(queue_node *head);

