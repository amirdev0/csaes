#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev;
    struct node *next;
};

struct list {
    struct node *head;
};

struct node* last_node(struct list *list) {
    if (list->head == NULL)
        return NULL;
    
    struct node *prev, *node = list->head;
    while (node) {
        prev = node;
        node = node->next;
    }
    
    return prev;
}

struct node* search(int value, struct list *list) {
    struct node *node = list->head;
    while (node) {
        if (node->value == value)
            return node;
        node = node->next;
    }
    
    return NULL;
}

int insert(int value, struct list *list) {
    struct node *last = last_node(list);
    if (last) {
        struct node *new = malloc(sizeof(struct node));
        new->value = value;
        new->prev = last;
        new->next = NULL;
        last->next = new;
    }
    
    if (list->head == NULL) {
        list->head = malloc(sizeof(struct node));
        list->head->value = value;
        list->head->next = NULL;
        list->head->prev = NULL;
    }
    
    return 0;
}

int delete(int value, struct list *list) {
    if (list->head == NULL)
        return -1;
    
    struct node *node = search(value, list);
    if (node == NULL)
        return -1;

    if (node->prev == NULL) {
        node->next->prev = NULL;
        list->head = node->next;
    }
    else if (node->next == NULL) {
        node->prev->next = NULL;
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);
    return 0;
}

void draw(struct list *list) {
    if (list == NULL)
        return;

    struct node *node = list->head;
    while (node) {
        printf("%d <-> ", node->value);
        node = node->next;
    }
    puts("x");
}

void test(struct list *list) {
    puts("Doubly Linked List test\n");
    
    printf("search 5: %s\n", search(5, list) != NULL ? "succeed" : "failed");
    
    printf("delete 5: %s\n", delete(5, list) == 0 ? "succed" : "failed");
    printf("insert 5: %s\n", insert(5, list) == 0 ? "succeed" : "failed");
    printf("insert 3: %s\n", insert(3, list) == 0 ? "succeed" : "failed");
    
    puts("\nList structure:");
    draw(list);
    
    printf("search 5: %s\n", search(5, list) != NULL ? "succeed" : "failed");
    printf("delete 5: %s\n", delete(5, list) == 0 ? "succed" : "failed");
    
    puts("\nList structure:");
    draw(list);
    
    printf("search 5: %s\n", search(5, list) != NULL ? "succeed" : "failed");
    printf("delete 3: %s\n", delete(3, list) == 0 ? "succed" : "failed");
    
    puts("\nList structure:");
    draw(list);
}

int main()
{
    struct list *list = malloc(sizeof(struct list));
    list->head = NULL;

    test(list);
    
    int choice = -1;
    while (choice) {
        puts("\n1. Insert value to doubly linked list");
        puts("2. Delete value from doubly linked list");
        puts("3. Search value in doubly linked list");
        puts("4. Draw graphically doubly linked list");
        puts("0. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        int value;
        switch (choice) {
            case 1:
                printf("Enter value to be inserted: ");
                scanf("%d", &value);
                if (insert(value, list) == 0)
                    puts("Suceed to insert node");
                else
                    puts("Failed to insert node");
                break;
            case 2:
                printf("Enter value to be deleted: ");
                scanf("%d", &value);
                if (delete(value, list) == 0)
                    puts("Suceed to delete node");
                else
                    puts("Failed to delete node");
                break;
            case 3:
                printf("Enter value to search for: ");
                scanf("%d", &value);
                if (search(value, list) != 0)
                    puts("Node was found");
                else
                    puts("Node was not found: ");
                break;
            case 4:
                puts("List structure");
                draw(list);
                break;
        }
    }
    
    free(list);
    return 0;
}

