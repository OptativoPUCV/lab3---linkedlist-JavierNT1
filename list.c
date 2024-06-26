#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* L = (List*)malloc(sizeof(List));
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  return L;
}

void * firstList(List * list) {
  if(!list->head) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(!list->head || !list->current || !list->current->next)       return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(!list || !list->head) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if(!list || !list->head || !list->current || !list->current->prev) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * new = createNode(data);
  if(list->head == NULL){
    list->tail = new;
  }
  else{
    new->next = list->head;
    list->head->prev = new;
  }
  list->head = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * new = createNode(data);
  if(list->current->next)
    new->next = list->current->next;
  new->prev = list->current;

  if(list->current->next)
    list->current->next->prev = new;
  list->current->next = new;

  if(list->current == list->tail)
    list->tail = new;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if(list->current == NULL) return NULL;

  Node * aux = list->current;

  if(aux->next != NULL)
    aux->next->prev = aux->prev;

  if(aux->prev != NULL)
    aux->prev->next = aux->next;

  void * data = (void *)aux->data;

  if(list->current == list->tail)
    list->tail = list->current->prev;

  if(list->current == list->head)
    list->head = list->current->next;

  list->current = aux->prev;
  
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}