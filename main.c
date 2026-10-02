#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void PrintList(const List *list);

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
        printf("5. Delete\n");
        printf("6. Insert\n");
        printf("7. Clear\n");
        printf("8. GetIndex\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Неверный ввод. Введите число.\n");
            continue;
        }

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
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Неверный ввод.\n");
                continue;
            }
            if (idx < 0){
                printf("Индекс не может быть отрицательным.\n");
                continue;
            }
            Item *p = GetItem(&list, idx);
            printf("GetItem(%d) = %p\n", idx, (void*)p);
        }
        else if (choice == 5){
            int idx;
            printf("index: ");
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Неверный ввод.\n");
                continue;
            }
            if (idx < 0){
                printf("Индекс не может быть отрицательным.\n");
                continue;
            }
            Delete(&list, idx);
            printf("Deleted. Count = %d\n", Count(&list));
        }
        else if (choice == 6){
            int idx;
            printf("index: ");
            if (scanf("%d", &idx) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Неверный ввод.\n");
                continue;
            }
            if (idx < 0){
                printf("Индекс не может быть отрицательным.\n");
                continue;
            }
            Item *it = (Item*)malloc(sizeof(Item));
            if (it == NULL){ printf("malloc failed\n"); continue; }
            it->prev = NULL;
            it->next = NULL;
            Insert(&list, it, idx);
            printf("Inserted. Count = %d\n", Count(&list));
        }
        else if (choice == 7){
            Clear(&list);
            printf("Cleared. Count = %d\n", Count(&list));
        }
        else if (choice == 8){
            Item *p;
            printf("pointer (hex, like 0x...): ");
            if (scanf("%p", (void**)&p) != 1){
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Неверный указатель.\n");
                continue;
            }
            printf("GetIndex = %d\n", GetIndex(&list, p));
        }
    }

    Clear(&list);
    return 0;
}
