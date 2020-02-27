#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"
#include "strnatcmp.h"

queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
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
    list_ele_t *tmp = NULL;
    while (current_ptr) {
        tmp = current_ptr->next;
        free(current_ptr->value);
        free(current_ptr);
        current_ptr = tmp;
    }
    free(q);
    return;
}

bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    int len = strlen(s);
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(sizeof(char) * (len + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, len);
    strncpy(newh->value, s, len);
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
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = malloc(sizeof(char) * (len + 1));
    if (!newh->value) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, len);
    strncpy(newh->value, s, len);
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
    if (sp) {
        memset(sp, 0, bufsize);
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
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


list_ele_t *sort(list_ele_t *start)
{
    if (!start || !start->next)
        return start;
    list_ele_t *left = start;
    list_ele_t *right = start->next;
    left->next = NULL;

    left = sort(left);
    right = sort(right);

    for (list_ele_t *merge = NULL; left || right;) {
        if (!right || (left && strcmp((left->value), (right->value)) < 0)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}

void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;
    q->head = sort(q->head);
    //  Find new q->tail after sort
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}
