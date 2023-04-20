/*!
 * \file       map.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Header file for map
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef MAP_H
#define MAP_H

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Exported types --------------------------------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------------------------*/
/* Exported functions declarations ---------------------------------------------------------------*/
/*! Initializes 2D map array, sets the roads and indexes of cities to 0.
 *
 * \param[out]  map     Map that we want to initialize.
 * \param[in]   mapSize Size of map.
 * \param[in]   cities  Heap that contains names of cities loaded from file.
 */
void Map_Road_Init(Data_t **map, unsigned mapSize, char **cities);

/*! Generates roads for each city.
 *
 * \param[out]  map           2D array of our map.
 * \param[in]   mapSize       Size of map.
 * \param[in]   roadLimit     Maximum number of road that is allowed to generate for each city.
 * \param[in]   oneWay        boolean that turn on or off rule that each road is one-way only or no.
 * \param[in]   maxRoadLength Maximum length of road.
 * \param[in]   minRoadLength Minimum length of road.
 */
void Map_Generate_Roads(Data_t **map,
                        unsigned mapSize,
                        unsigned roadLimit,
                        bool oneWay,
                        unsigned maxRoadLength,
                        unsigned minRoadLength);

/*! Creates a file that contains information about map for future loading.
 *
 * \param[in] map     2D array of cities.
 * \param[in] mapSize Size of map.
 * \param[in] path    Path where to write the data.
 */
void Map_Write_Map(Data_t **map, unsigned mapSize, char *path);

/*! Stores the data about each city from file into an array
 *
 * \param[out] map   Heap where are data being stored
 * \param[in] file  File from which we read our data
 */
unsigned Map_Read_Map(Data_t *map, FILE *file);

/*!
 * \brief Map_Print_Cities Prints to the console list of city and index of city.
 * \param[in] map   2D array of cities
 * \param[in] mapSize   Size of map
 */
void Map_Print_Cities(Data_t *map, unsigned mapSize);

/*!
 * \brief Map_Print Prints to the console map that was generated
 * \param[out] map   2D array of generated map
 * \param[in] mapSize   Size of map
 */
void Map_Print(Data_t **map, unsigned mapSize);

/*!
 * \brief Map_Generate_DOT_File Generates .DOT file for graphviz software
 * \param[in] map   2D array of our map
 * \param[in] mapSize   Size of map
 * \param[in] path  Path where to store our data
 * \param[in] cities    Heap that contains names of each city
 */
void Map_Generate_DOT_File(Data_t *map, unsigned mapSize, char *path, char **cities);
#endif  // MAP_H
