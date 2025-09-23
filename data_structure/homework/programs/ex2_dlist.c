#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

/*
    Print List
*/
static void print_list(const DList *list) {
    DListNode *node;
    int *data, i;

    fprintf(stdout, "DList size is %d\n", dlist_size(list));

    i = 0;
    node = dlist_head(list);

    if (dlist_size(list) == 0) {
        return;
    }

    while (1) {
        data = dlist_data(node);
        fprintf(stdout, "dlist.node[%03d]=%03d, %14p <- %p -> %p \n", i, *data, node->prev, node, node->next);

        i++;

        if (dlist_is_tail(node))
            break;
        else
            node = dlist_next(node);
    }

    return;
}

int main(int argc, char **argv) {
    DList list;
    int *data;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <value1> <value2> <value3> ...\n", argv[0]);
        return 1;
    }

    dlist_init(&list, free);

    for (i = 1; i < argc; i++) {

        if ((data = (int *)malloc(sizeof(int))) == NULL) {
            fprintf(stderr, "Error: Could not allocate memory.\n");
            return 1;
        }

        *data = atoi(argv[i]);

        if (dlist_ins_next(&list, dlist_tail(&list), data) != 0) {
            fprintf(stderr, "Error: Could not insert element.\n");
            free(data); 
            return 1;
        }
    }
    
    fprintf(stdout, "List created from command-line arguments:\n");
    print_list(&list);

    fprintf(stdout, "\nDestroying the list\n");
    dlist_destroy(&list);

    return 0;
}
