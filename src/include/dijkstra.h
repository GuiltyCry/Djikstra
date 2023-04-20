/*!
 * \file       dijkstra.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Header file for Dijkstra algorithm
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
/*! \defgroup dijkstra Dijkstra algorithm
 *
 *  \brief The module implements Dijkstra's alghorithm is used to find the shortest path between one
 * point and all others. The distances between points we're storing in array (structure \ref
 * tDijkstra), which needs to be initialized. Every distance in our array has to be set to 'INF'
 * (Which is defined as maximum value of unsigned) except one which is our starting point ->
 * distance between starting point and itself is 0, we don't need special algorithm to know that.
 *
 * The city is described in the \ref Data_t structure.
 *
 * Every city has its own \ref Data_t.id, \ref Data_t.name, array \ref Data_t.roadLength - each city
 * can have up to 8 roads, the road is connected to a city if the road length is greater than 0. If
 * the road length is greater than 0, then it is connected to a city, which we find in an array \ref
 * Data_t.roadCityIndex at the same index as the roadLength. distance is used as a value, by which
 * we sort our heap and we store here the calculated distance of from the starting city, so before
 * you insert city into heap, do not forget to change the distance value.
 *
 *  \{
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"

#include <limits.h>
#include <stdbool.h>

/* Exported types --------------------------------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------------------------*/
#define INF UINT_MAX

/*! \struct tDijkstra
 * Here is defined structure that stores informations about each city
 */
typedef struct {
  /*! Heap that stores what city was already visited and which wasn't. */
  bool *visited;

  /*! Heap that stores distance between source city and city on each index */
  unsigned *distances;
} tDijkstra;

/* Exported variables ----------------------------------------------------------------------------*/
/* Exported functions declarations ---------------------------------------------------------------*/
/*! Initializes the Dijkstra structure, sets the bool array to false for each city, and distance to
 * 'INF', for the sourceCityID city set distance to 0.
 *
 * \param[in] dijkstra      Pointer at tDijkstra structure.
 * \param[in] cityCount     The number of cities that our map is loaded with.
 * \param[in] sourceCityID  Index of starting city.
 *
 * \return  Return true if initialization was successful, return false otherwise.
 */
bool Dijkstra_Init(tDijkstra *dijkstra, unsigned cityCount, unsigned sourceCityID);

/*! Erases the content of a tDijkstra, allocated memory is freed and set to NULL.
 *
 * \param[in] dijkstra  Pointer at \ref tDijkstra structure.
 */
void Dijkstra_Destruct(tDijkstra *dijkstra);

/*! Counts the distance between sourceCityID city and every other one.
 *
 * \param[in] mapHeap       Heap, that stores each city and it's details.
 * \param[in] dijkstra      \ref tDijkstra structure, where are the shortest paths stored and
 * informations if cities were visited already.
 * \param[in] sourceCityID  Index of starting city.
 * \param[in] destination   Index of our destination.
 *
 * \return  Returns true if the destination is reachable and the value was found, return false
 * otherwise.
 */
bool Dijkstra_Dist(Data_t *mapHeap,
                   tDijkstra *dijkstra,
                   unsigned sourceCityID,
                   unsigned destination);

#endif  // DIJKSTRA_H
