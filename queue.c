#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return 0;
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void q_free(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *current_ptr = q->head;
    while (current_ptr) {
        list_ele_t *tmp = current_ptr;
        current_ptr = current_ptr->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
    return;
}

bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int len = strlen(s);
    len = len + 1;
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(sizeof(char) * len);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, len);
    strncpy(newh->value, s, len - 1);
    newh->value[len] = '\0';
    //  Maintain queue structure
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0) {
        q->tail = newh;
    }
    q->size += 1;
    return true;
}

bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    int len = strlen(s);
    len += 1;
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(sizeof(char) * len);
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, len);
    strncpy(newh->value, s, len - 1);
    newh->value[len] = '\0';
    newh->next = NULL;
    if (q->size == 0) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    q->tail = newh;
    q->size += 1;
    return true;
}

bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->head)
        return false;
    list_ele_t *tmp = q->head;
    int len = strlen(q->head->value);
    if (sp) {
        memset(sp, 0, bufsize);
        strncpy(sp, tmp->value, len);
    }
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size -= 1;
    return true;
}

int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->size;
}

void q_reverse(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *next, *curr, *prev;
    prev = NULL;
    next = NULL;
    curr = q->head;
    q->tail = q->head;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = prev;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
