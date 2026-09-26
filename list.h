#ifndef LIST_H
#define LIST_H

typedef struct Item{
    struct Item *prev;
    struct Item *next;
}Item;

typedef struct List{
    Item *head;
    Item *tail;
}List;

void Add(List *list, Item *item);
int Count(const List *list);
Item* GetItem(const List *list, int index);
Item* Remove(List *list, int index);
void Delete(List *list, int index);
void Insert(List *list, Item *item, int index);
void Clear(List *list);
int GetIndex(const List *list, const Item *item);

#endif
