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
    Item *next1 = GetItem(list, index);
    if (next1 == NULL){
        Add(list, item);
        return;
    }

    if (next1 == list->head){
        item->prev = NULL;
        item->next = list->head;
        list->head->prev = item;
        list->head = item;
        return;
    }

    Item *prev1 = next1->prev;
    item->prev = prev1;
    item->next = next1;
    next1->prev = item;
    prev1->next = item;
}

void Clear(List *list){
    if (list == NULL) return;
    while (list->head)
        Delete(list, 0);
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
