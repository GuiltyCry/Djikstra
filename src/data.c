/*!
 * \file       data.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Definition of the data module.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"

#include <stdio.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
int Data_Cmp(const Data_t *d1, const Data_t *d2)
{
  return d1->distanceToCity - d2->distanceToCity;
}

void Data_Print(Data_t *data)
{
  printf("ID=%d, name=%s\n", data->id, data->name);
}

/* Private function definitions ------------------------------------------------------------------*/