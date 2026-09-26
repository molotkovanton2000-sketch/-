#include <stdio.h>
#include <stdlib.h>

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
void PrintList(const List *list);

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

void PrintList(const List *list){
    if (list == NULL){
        printf("List: NULL\n");
        return;
    }
    printf("List: %p  Head: %p  Tail: %p\n",
           (void*)list, (void*)list->head, (void*)list->tail);
    printf("#\tp\tprev\tnext\n");
    Item *p = list->head;
    int i = 0;
    while (p != NULL){
        printf("%d\t%p\t%p\t%p\n", i++, (void*)p,
               (void*)p->prev, (void*)p->next);
        p = p->next;
    }
}

int main(void){
    List list;
    list.head = NULL;
    list.tail = NULL;

    int choice = -1;
    while (choice != 0){
        printf("\n=== MENU ===\n");
        printf("1. Add\n");
        printf("2. Count\n");
        printf("3. PrintList\n");
        printf("4. GetItem\n");
        printf("5. Remove\n");
        printf("6. Delete\n");
        printf("7. Insert\n");
        printf("8. Clear\n");
        printf("9. GetIndex\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1){
            Item *it = (Item*)malloc(sizeof(Item));
            if (it == NULL){ printf("malloc failed\n"); continue; }
            it->prev = NULL;
            it->next = NULL;
            Add(&list, it);
            printf("Added. Count = %d\n", Count(&list));
        }
        else if (choice == 2){
            printf("Count = %d\n", Count(&list));
        }
        else if (choice == 3){
            PrintList(&list);
        }
        else if (choice == 4){
            int idx;
            printf("index: ");
            scanf("%d", &idx);
            Item *p = GetItem(&list, idx);
            printf("GetItem(%d) = %p\n", idx, (void*)p);
        }
        else if (choice == 5){
            int idx;
            printf("index: ");
            scanf("%d", &idx);
            Item *p = Remove(&list, idx);
            printf("Removed = %p\n", (void*)p);
            if (p != NULL){
                free(p);
            }
        }
        else if (choice == 6){
            int idx;
            printf("index: ");
            scanf("%d", &idx);
            Delete(&list, idx);
            printf("Deleted. Count = %d\n", Count(&list));
        }
        else if (choice == 7){
            int idx;
            printf("index: ");
            scanf("%d", &idx);
            Item *it = (Item*)malloc(sizeof(Item));
            if (it == NULL){ printf("malloc failed\n"); continue; }
            it->prev = NULL;
            it->next = NULL;
            Insert(&list, it, idx);
            printf("Inserted. Count = %d\n", Count(&list));
        }
        else if (choice == 8){
            Clear(&list);
            printf("Cleared. Count = %d\n", Count(&list));
        }
        else if (choice == 9){
            Item *p;
            printf("pointer (hex, like 0x...): ");
            scanf("%p", (void**)&p);
            printf("GetIndex = %d\n", GetIndex(&list, p));
        }
    }

    Clear(&list);
    return 0;
}
