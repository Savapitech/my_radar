/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "lib.h"

static
void mini_swap(char *a, char *b, size_t size)
{
    char swap;

    for (size_t i = 0; i < size; i++) {
        swap = a[i];
        a[i] = b[i];
        b[i] = swap;
    }
}

static
size_t mini_qsort2(miniqsort_t *mq, size_t cp_index, void *pivot)
{
    for (size_t i = 0; i < mq->size; i++) {
        if (mq->compare(IDX_OF(mq->arr, i, mq->mem_s), pivot,
            mq->params) < 0) {
            mini_swap(IDX_OF(mq->arr, i, mq->mem_s),
                IDX_OF(mq->arr, cp_index, mq->mem_s), mq->mem_s);
            cp_index++;
        }
    }
    return cp_index;
}

void mini_qsort(miniqsort_t *mq)
{
    void *pivot = IDX_OF(mq->arr, mq->size - 1, mq->mem_s);
    size_t cp_index = 0;
    size_t old_size;
    miniqsort_t cpy;

    if (mq->size < 2)
        return;
    cp_index = mini_qsort2(mq, cp_index, pivot);
    mini_swap(IDX_OF(mq->arr, cp_index, mq->mem_s), pivot, mq->mem_s);
    old_size = mq->size;
    mq->size = cp_index;
    cpy = *mq;
    mini_qsort(&cpy);
    mq->arr = IDX_OF(mq->arr, cp_index + 1, mq->mem_s);
    mq->size = old_size - (cp_index + 1);
    mini_qsort(mq);
}
