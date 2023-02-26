#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "errs.h"

#define COMMAND_LEN 3

int get_command(char *command);

int main(void)
{
    int rc = OK;
    char cmd[COMMAND_LEN + 3];

    rc = get_command(cmd);
    if (rc || (strcmp(cmd, "val") && strcmp(cmd, "ddx") && strcmp(cmd, "sum") && strcmp(cmd, "dvd")))
        return ARGS_ERROR;

    node_t *head = list_create();
    if (!head)
        return ALLOC_ERROR;
    
    if (!strcmp(cmd, "val"))
    {
        int a;
        if (scanf("%d", &a) != 1)
            rc = INPUT_ERROR;
        else
            printf("%d\n", calc(head, a));

        list_free(head);
    }
    else if (!strcmp(cmd, "ddx"))
    {
        head = derive(head);
        if (head == NULL)
            rc = EMPTY_LIST_ERROR;
        else
            list_print(head);

        list_free(head);
    }
    else if (!strcmp(cmd, "sum"))
    {
        node_t *head2 = list_create();
        if (head2 != NULL)
        {
            node_t *res = summation(head, head2);
            if (res != NULL)
            {
                list_print(res);
                list_free(res);
            }
            list_free(head2);
        }
        else
            rc = EMPTY_LIST_ERROR;
        
        list_free(head);
    }
    else if (!strcmp(cmd, "dvd"))
    {
        node_t *head_even = NULL, *head_odd = NULL;
        separation(head, &head_even, &head_odd);
        
        if (head_even == NULL || head_odd == NULL)
            rc = EMPTY_LIST_ERROR;
        else
        {
            list_print(head_even);
            list_print(head_odd);
        }

        list_free(head_odd);
        list_free(head_even);
    }

    return rc;
}

int get_command(char *command)
{
    size_t len;

    if (!fgets(command, sizeof(char) * (COMMAND_LEN + 3), stdin))
        return INPUT_ERROR;
    
    len = strlen(command);
    if (len && command[len - 1] == '\n')
    {
        command[len - 1] = '\0';
        len--;
    }
    if (!len || len > COMMAND_LEN)
        return INPUT_ERROR;
    
    return OK;
}