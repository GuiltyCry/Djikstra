/*!
 * \file       dijkstra.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of function for Dijkstra algorithm
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "dijkstra.h"
#include "mymalloc.h"
#include "heap.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
bool Dijkstra_Init(tDijkstra *dijkstra, unsigned cityCount, unsigned sourceCityID)
{
  if(dijkstra == NULL || cityCount == 0) {
    return false;
  }
  dijkstra->distances = myMalloc(sizeof (unsigned int) * cityCount);
  if(dijkstra->distances == 0) {
    return false;
  }
  dijkstra->visited = myMalloc(sizeof (bool) * cityCount);
  if(dijkstra->visited == NULL) {
    myFree(dijkstra->distances);
    return false;
  }
  for(unsigned int i=0; i<cityCount; i++) {
    dijkstra->visited[i] = false;
    dijkstra->distances[i] = INF;
  }
  dijkstra->distances[sourceCityID] = 0;
  return true;
}

void Dijkstra_Destruct(tDijkstra *dijkstra)
{
  if (dijkstra != NULL) {
    myFree(dijkstra->visited);
    myFree(dijkstra->distances);

    dijkstra->visited = NULL;
    dijkstra->distances = NULL;
  }
}

bool Dijkstra_Dist(Data_t *mapHeap,
                   tDijkstra *dijkstra,
                   unsigned sourceCityID,
                   unsigned destination)
{
  tHeap heap;
  if (Heap_Init(&heap)) {
    return false;
  }

  // Initialize distances and visited arrays
  if (!Dijkstra_Init(dijkstra, heap.maxItems, sourceCityID)) {
    Heap_Destruct(&heap);
    return false;
  }

  // Insert source city into the heap
  mapHeap[sourceCityID].distanceToCity = 0;
  Heap_Insert(&heap, mapHeap[sourceCityID]);

  while (heap.count > 0) {
    // Extract the city with the shortest distance from the heap
    Data_t cityMin;
    Heap_DeleteMin(&heap, &cityMin);
    if (cityMin.id == destination) {
      Heap_Destruct(&heap);
      return true;
    }

    // Mark the city as visited
    dijkstra->visited[cityMin.id] = true;

    // Check all the roads of the current city and update the distances
    for (unsigned i = 0; i < 8; i++) {
      unsigned roadCityIndex = cityMin.roadCityIndex[i];
      if (roadCityIndex == cityMin.id) {
        continue; // Ignore self-loops
      }
      unsigned roadLength = cityMin.roadLength[i];
      if (roadCityIndex != 0 && !dijkstra->visited[roadCityIndex]) {
        unsigned newDistance = cityMin.distanceToCity + roadLength;
        if (newDistance < dijkstra->distances[roadCityIndex]) {
          // Update the distance and insert the city into the heap
          dijkstra->distances[roadCityIndex] = newDistance;
          mapHeap[roadCityIndex].distanceToCity = newDistance;
          Heap_Insert(&heap, mapHeap[roadCityIndex]);
        }
      }
    }
  }

  Heap_Destruct(&heap);
  return false;
}
/* Private function definitions ------------------------------------------------------------------*/
