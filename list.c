#include <stdlib.h>
#include "list.h"

void Add(List *list, Item *item){
    if (list == NULL || item == NULL){
        return;
    }
    item->prev = list->tail;
    item->next = NULL;
    if (list->head == NULL){
        list->head = item;
    } else {
        list->tail->next = item;
    }
    list->tail = item;
}

int Count(const List *list){
    if (list == NULL) return 0;

    int counter = 0;
    Item *p = list->head;
    while (p != NULL) {
        counter = counter + 1;
        p = p->next;
    }
    return counter;
}

Item* GetItem(const List *list, int index){
    if (list == NULL || index < 0){
        return NULL;
    }
    Item *p = list->head;
    int i = 0;
    while (p != NULL && i < index){
        p = p->next;
        i = i + 1;
    }
    return p;
}

Item* Remove(List *list, int index){
    if (list == NULL){
        return NULL;
    }
    Item *victim = GetItem(list, index);
    if (victim == NULL){
        return NULL;
    }
    if (victim->prev != NULL){
        victim->prev->next = victim->next;
    } else {
        list->head = victim->next;
    }
    if (victim->next != NULL){
        victim->next->prev = victim->prev;
    } else {
        list->tail = victim->prev;
    }
    victim->prev = NULL;
    victim->next = NULL;
    return victim;
}

void Delete(List *list, int index){
    Item *victim = Remove(list, index);
    if (victim != NULL){
        free(victim);
    }
}

void Insert(List *list, Item *item, int index){
    if (list == NULL || item == NULL){
        return;
    }
    if (list->head == NULL || index >= Count(list)){
        Add(list, item);
        return;
    }
    if (index <= 0){
        item->prev = NULL;
        item->next = list->head;
        list->head->prev = item;
        list->head = item;
        return;
    }
    Item *prev = GetItem(list, index - 1);
    Item *next = prev->next;
    item->prev = prev;
    item->next = next;
    prev->next = item;
    next->prev = item;
}

void Clear(List *list){
    if (list == NULL) return;
    Item *p = list->head;
    while (p != NULL){
        Item *next = p->next;
        free(p);
        p = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

int GetIndex(const List *list, const Item *item){
    if (list == NULL || item == NULL){
        return -1;
    }
    Item *p = list->head;
    int i = 0;
    while (p != NULL){
        if (p == item){
            return i;
        }
        p = p->next;
        i = i + 1;
    }
    return -1;
}
