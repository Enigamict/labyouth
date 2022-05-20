#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct linklist {
    int data;
    struct linklist *next;
};

int main() {
    struct linklist *p;
    struct linklist n1;
    struct linklist n2;
    struct linklist n3;
    
    n1.data = 1;
    n1.next = &n2;
    n2.data = 2;
    n2.next = &n3;
    n3.data = 3;
    n3.next = NULL;
    
    p = &n1;
    printf("%d\n", p -> data);

    p = p -> next;
    printf("%d\n", p -> data);
    
    p = p -> next;
    printf("%d\n", p -> data);
}