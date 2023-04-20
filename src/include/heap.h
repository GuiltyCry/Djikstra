/*!
 * \file       heap.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Header file of heap module.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#ifndef HEAP_H
#define HEAP_H

/*! \defgroup heap Heap
 *
 *  \brief Module that implements the min-heap data structure. It defines basic
 * set of the functions that shall be used for manipulating with the \ref tHeap
 * structure.
 *
 *  \{
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"

#include <stdbool.h>
#include <stdio.h>

/* Exported macros -------------------------------------------------------------------------------*/
/*! Maximum items in heap that can be stored when initializing heap */
#define MAX_ITEMS_START 4

/* Exported types --------------------------------------------------------------------------------*/
/*! Heap structure */
typedef struct {
  /*! Array, where are the items being stored */
  Data_t *array;

  /*! Keeps track of how many items are in heap */
  size_t count;

  /*! Count how many items can be stored in heap */
  size_t maxItems;
} tHeap;

typedef void (*heapProcessCB)(size_t index, const Data_t *);

/* Exported constants ----------------------------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------------------------*/
/* Exported functions declarations ---------------------------------------------------------------*/

/*! Initializes the \a heap, sets \ref tHeap.count to 0, allocates memory for
 * data with space for \ref MAX_ITEMS_START elements, and saves the pointer into
 * the \ref tHeap.array, and sets \ref tHeap.maxItems to that value.
 *
 * \param[out] heap[in] Heap which we want to initialize.
 *
 * \return Returns true if heap was initialized, return false otherwise.
 */
bool Heap_Init(tHeap *heap);

/*! Inserts the value into the \a heap according to the rules for the min-heap
 * version. If the count of items in the \a heap is higher than maximum capacity
 * (\ref tHeap.maxItems), function reallocates the memory of heap to the double
 * size.
 *
 * \param[in] heap        Heap where the data are being stored.
 * \param[in] insertData  Data that are being stored in heap.
 *
 * \return Returns true if the data were inserted, return false otherwise.
 */
bool Heap_Insert(tHeap *heap, Data_t insertData);

/*! Destruct the \a heap. Free the internal array and sets the \ref tHeap.array
 * pointer to the NULL. \ref tHeap.count and \ref tHeap.maxItems are set to
 * zero.
 *
 * \param[in] table Pointer at heap we want to destruct.
 */
void Heap_Destruct(tHeap *heap);

/*! Returns the minimum value in \a heap to the argument \a value.
 *
 * \param[in]   heap  Heap where we want to find the minimum value.
 * \param[out]  value Pointer to a value to be returned.
 *
 * \return TRUE if the item is in the heap, else returns FALSE if
 * there are no data in heap.
 */
bool Heap_FindMin(tHeap heap, Data_t *value);

/*! Deletes the minimum value that is stored in \a heap. Deleted data can be
 * stored in \a deletedValue if pointer is passed.
 *
 * \param[in]   heap          Pointer at our heap.
 * \param[out]  deletedValue  Pointer to the data that are being deleted.
 * (optional, can be NULL).
 *
 * \return TRUE if the item is be deleted, else returns FALSE if
 * there are no data in heap.
 */
bool Heap_DeleteMin(tHeap *heap, Data_t *deletedValue);

/*! Check if \a heap is empty.
 *
 * \param[in] heap Heap which we want to check.
 *
 * \return Returns true if the \a heap is empty, false otherwise.
 */
bool Heap_Empty(tHeap heap);

/*! Returns the size of the \a heap.
 *
 * \param[in] heap Heap that we want size of.
 *
 * \return Returns the number of items stored in the heap.
 */
unsigned int Heap_Count(tHeap heap);

/*! Process the \a heap by calling \a cb with each item in it.
 *
 * \param[in] heap  Heap that we want to process.
 * \param[in] cb    Callback to call with the item.
 */
void Heap_Process(tHeap heap, heapProcessCB cb);

#endif  // HEAP_H

/*! \} */