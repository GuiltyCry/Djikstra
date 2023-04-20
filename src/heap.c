/*!
 * \file       heap.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of the heap module in version min-heap.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "heap.h"
#include "mymalloc.h"
#include <stdlib.h>
#include <string.h>

/* Private macro ---------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private types ---------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
bool Heap_Init(tHeap *heap)
{
  if(heap == NULL) {
    return false;
  }
  heap->count = 0;
  heap->maxItems = MAX_ITEMS_START;
  heap->array = myMalloc(MAX_ITEMS_START * sizeof (Data_t));
  if(heap->array == NULL) {
    return false;
  }
  return true;
}

bool Heap_Insert(tHeap *heap, Data_t insertData)
{
  if (heap == NULL) {
    return false;
  }

  if (heap->count == heap->maxItems) {
    size_t newMaxItems = heap->maxItems * 2;
    Data_t *newArray = myMalloc(newMaxItems * sizeof(Data_t));
    if (newArray == NULL) {
      return false;
    }
    memcpy(newArray, heap->array, heap->count * sizeof(Data_t));
    myFree(heap->array);
    heap->array = newArray;
    heap->maxItems = newMaxItems;
  }

  heap->array[heap->count] = insertData;
  heap->count++;

  size_t i = heap->count - 1;
  while (i > 0 && heap->array[(i - 1) / 2].distanceToCity > heap->array[i].distanceToCity) {
    Data_t tmp = heap->array[(i - 1) / 2];
    heap->array[(i - 1) / 2] = heap->array[i];
    heap->array[i] = tmp;
    i = (i - 1) / 2;
  }
  return true;
}

void Heap_Destruct(tHeap *heap)
{
  myFree(heap->array);
  heap->array = NULL;
  heap->maxItems = 0;
}

bool Heap_FindMin(tHeap heap, Data_t *value)
{
  if(value == NULL || heap.count == 0) {
    return false;
  }
  *value = heap.array[0];
  return true;
}

bool Heap_DeleteMin(tHeap *heap, Data_t *deletedValue)
{
  if (heap == NULL || deletedValue == NULL || heap->count == 0) {
    return false;
  }

  *deletedValue = heap->array[0];
  heap->array[0] = heap->array[heap->count - 1];
  heap->count--;

  size_t i = 0;
  while (true) {
    size_t leva = 2 * i + 1;
    size_t prava = 2 * i + 2;
    size_t nejmensi = i;

    if (leva < heap->count && heap->array[leva].distanceToCity < heap->array[nejmensi].distanceToCity) {
      nejmensi = leva;
    }

    if (prava < heap->count && heap->array[prava].distanceToCity < heap->array[nejmensi].distanceToCity) {
      nejmensi = prava;
    }

    if (nejmensi == i) {
      break;
    }

    Data_t tmp = heap->array[i];
    heap->array[i] = heap->array[nejmensi];
    heap->array[nejmensi] = tmp;
    i = nejmensi;
  }

  return true;
}

void Heap_Process(tHeap heap, heapProcessCB cb)
{
  if(cb == NULL) {
    return;
  }
  for(size_t i=0; i<heap.count; i++) {
    cb(i, &heap.array[i]);
  }
}

bool Heap_Empty(tHeap heap)
{
  return (heap.count == 0);
}

unsigned Heap_Count(tHeap heap)
{
  return heap.count;
}
/* Private function definitions ------------------------------------------------------------------*/
