#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

queue *init(queue *q) {
  q = malloc(sizeof(queue));
  q->amount_of_queue_nodes = 0;
  q->front = NULL;
  q->tail = NULL;
  return q;
}

int is_empty(queue **q) {
  if ((*q)->front == NULL) {
    return 1;
  } else {
    return 0;
  }
}

void enqueue(queue **q, char path[PATH_MAX]) {
  queue_node *tmp;
  tmp = (queue_node *)malloc(sizeof(queue_node));
  memcpy(tmp->file_path, path, PATH_MAX);
  tmp->next_queue_node = NULL;
  if (is_empty(q) == 0) {
    (*q)->tail->next_queue_node = tmp;
    (*q)->tail = tmp;
  } else {
    (*q)->front = tmp;
    (*q)->tail = tmp;
  }
  (*q)->amount_of_queue_nodes++;
}

void dequeue(queue **q, char path[PATH_MAX]) {
  queue_node *tmp;
  memcpy(path, (*q)->front->file_path, PATH_MAX);
  tmp = (*q)->front;
  (*q)->front = ((*q)->front->next_queue_node);
  (*q)->amount_of_queue_nodes--;
  free(tmp);
}

