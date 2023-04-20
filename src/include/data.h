/*!
 * \file       data.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Declaration of the data module.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef DATA_H_
#define DATA_H_

/*! \defgroup data Data
 *
 *  \brief Base data structure that is used in project.
 *
 *  \{
 */

/* Includes --------------------------------------------------------------------------------------*/
#include <stdbool.h>

/* Exported types --------------------------------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------------------------*/
/* Exported functions declarations ---------------------------------------------------------------*/
/*! Structure that stores information about each city that is stored in map array. */
typedef struct {
  /*! Id of a city, used as an index in array's. */
  unsigned id;

  /*! Name of city. */
  char name[256];

  /*! Roads that is city connected to (Road with index 3 is connected to city with index 3). */
  unsigned roadLength[8];

  /*! ID of city that is road connected to. */
  unsigned roadCityIndex[8];

  /*! Calculated distance from source city, used in heap as a sorting value. */
  unsigned distanceToCity;
} Data_t;

/*! Prints data to stdout.
 *
 * \param[in] data  Data to print.
 */
void Data_Print(Data_t *data);

/*! Compares two structures and returns which one is first.
 *
 * \param[in] d1  LHS value to compare.
 * \param[in] d2  RHS value to compare.
 *
 * \return Returns zero if LHS is equal to RHS, less than zero if LHS is smaller
 * than RHS, more than zero otherwise.
 */
int Data_Cmp(const Data_t *d1, const Data_t *d2);

#endif /* DATA_H_ */

/*! \} */