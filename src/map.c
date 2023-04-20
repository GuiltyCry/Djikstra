/*!
 * \file       map.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementing of map module.
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "map.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
void Map_Road_Init(Data_t **map, unsigned mapSize, char **cities)
{
  unsigned id = 0;
  for (unsigned i = 0; i < mapSize; i++) {
    for (unsigned j = 0; j < mapSize; j++) {
      map[i][j].id = id;
      strcpy(map[i][j].name, cities[id]);
      ++id;

      for (int k = 0; k < 8; k++) {
        map[i][j].roadLength[k] = 0;
        map[i][j].roadCityIndex[k] = 0;
      }
    }
  }
}

void Map_Generate_Roads(Data_t **map,
                        unsigned mapSize,
                        unsigned roadLimit,
                        bool oneWay,
                        unsigned maxRoadLength,
                        unsigned minRoadLength)
{
  srand((unsigned int)time(NULL));

  for (unsigned i = 0; i < mapSize; i++) {
    for (unsigned j = 0; j < mapSize; j++) {
      unsigned roadCount = 0;

      for (unsigned k = 0; k < 8; k++) {
        if (map[i][j].roadLength[k] != 0)
          roadCount += 1;
      }

      for (unsigned k = 0; k < 8; k++) {
        int c = rand() % 100 + 1;
        if (k >= 7 && c > 50)
          c = 50;
        if (c <= 50 && map[i][j].roadLength[k] == 0 && roadCount < roadLimit) {
          unsigned tempK = k;
          if (j >= mapSize - 1) {
            if (k >= 3 && k <= 5) {
              tempK = 0;
            }
          } else if (j == 0) {
            if (k == 0 || k == 1 || k == 7) {
              tempK = 4;
            }
          } else if (i >= mapSize - 1) {
            if (k == 1 || k == 2 || k == 3) {
              tempK = 6;
            }
          } else if (i == 0) {
            if (k == 5 || k == 6 || k == 7) {
              tempK = 2;
            }
          }
          if (roadLimit >= roadCount) {
            unsigned roadLength = rand() % maxRoadLength + minRoadLength;
            switch (tempK) {
              case 0:
                if (j > 0) {
                  map[i][j].roadLength[0] = roadLength;
                  map[i][j].roadCityIndex[0] = map[i][j - 1].id;
                  if (!oneWay) {
                    map[i][j - 1].roadCityIndex[4] = map[i][j].id;
                    map[i][j - 1].roadLength[4] = roadLength;
                  }
                  roadCount++;
                }
                break;
              case 1:
                if (i < mapSize - 1 && j > 0) {
                  map[i][j].roadLength[1] = roadLength;
                  map[i][j].roadCityIndex[1] = map[i + 1][j - 1].id;
                  if (!oneWay) {
                    map[i + 1][j - 1].roadLength[5] = roadLength;
                    map[i + 1][j - 1].roadCityIndex[5] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 2:
                if (i < mapSize - 1) {
                  map[i][j].roadLength[2] = roadLength;
                  map[i][j].roadCityIndex[2] = map[i + 1][j].id;
                  if (!oneWay) {
                    map[i + 1][j].roadLength[6] = roadLength;
                    map[i + 1][j].roadCityIndex[6] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 3:
                if (i < mapSize - 1 && j < mapSize) {
                  map[i][j].roadLength[3] = roadLength;
                  map[i][j].roadCityIndex[3] = map[i + 1][j + 1].id;
                  if (!oneWay) {
                    map[i + 1][j + 1].roadLength[7] = roadLength;
                    map[i + 1][j + 1].roadCityIndex[7] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 4:
                if (j < mapSize - 1) {
                  map[i][j].roadLength[4] = roadLength;
                  map[i][j].roadCityIndex[4] = map[i][j + 1].id;
                  if (!oneWay) {
                    map[i][j + 1].roadLength[0] = roadLength;
                    map[i][j + 1].roadCityIndex[0] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 5:
                if (i > 0 && j < mapSize - 1) {
                  map[i][j].roadLength[5] = roadLength;
                  map[i][j].roadCityIndex[5] = map[i - 1][j + 1].id;
                  if (!oneWay) {
                    map[i - 1][j + 1].roadLength[1] = roadLength;
                    map[i - 1][j + 1].roadCityIndex[1] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 6:
                if (i > 0) {
                  map[i][j].roadLength[6] = roadLength;
                  map[i][j].roadCityIndex[6] = map[i - 1][j].id;
                  if (!oneWay) {
                    map[i - 1][j].roadLength[2] = roadLength;
                    map[i - 1][j].roadCityIndex[2] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
              case 7:
                if (i > 0 && j > 0) {
                  map[i][j].roadLength[7] = roadLength;
                  map[i][j].roadCityIndex[7] = map[i - 1][j - 1].id;
                  if (!oneWay) {
                    map[i - 1][j - 1].roadLength[3] = roadLength;
                    map[i - 1][j - 1].roadCityIndex[3] = map[i][j].id;
                  }
                  roadCount++;
                }
                break;
            }
          }
        }
      }
    }
  }
}

void Map_Write_Map(Data_t **map, unsigned mapSize, char *path)
{
  FILE *file;

  file = fopen(path, "w");
  for (unsigned i = 0; i < mapSize; i++) {
    for (unsigned j = 0; j < mapSize; j++) {
      fprintf(file, "%d;%s;", map[i][j].id, map[i][j].name);
      for (unsigned k = 0; k < 8; k++) {
        fprintf(file, "%d;%d;", map[i][j].roadLength[k], map[i][j].roadCityIndex[k]);
      }
      fprintf(file, "\n");
    }
  }
  fclose(file);
}

unsigned Map_Read_Map(Data_t *map, FILE *file)
{
  char buffer[2048];
  int ok;
  unsigned count = 0;
  if (file) {
    while (fgets(buffer, sizeof(buffer), file)) {
      ok = sscanf(buffer,
                  "%u;%[^;];%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;",
                  &map[count].id,
                  map[count].name,
                  &map[count].roadLength[0],
                  &map[count].roadCityIndex[0],
                  &map[count].roadLength[1],
                  &map[count].roadCityIndex[1],
                  &map[count].roadLength[2],
                  &map[count].roadCityIndex[2],
                  &map[count].roadLength[3],
                  &map[count].roadCityIndex[3],
                  &map[count].roadLength[4],
                  &map[count].roadCityIndex[4],
                  &map[count].roadLength[5],
                  &map[count].roadCityIndex[5],
                  &map[count].roadLength[6],
                  &map[count].roadCityIndex[6],
                  &map[count].roadLength[7],
                  &map[count].roadCityIndex[7]);
      if (ok == 18) {
        count++;
      }
    }
  }
  return count;
}

void Map_Print_Cities(Data_t *map, unsigned mapSize)
{
  if (map == NULL) {
    return;
  }
  printf("\nLoaded cities:\n");
  printf("Index\t-\tcity\n");
  for (unsigned i = 0; i < mapSize; i++) {
    printf("%d\t-\t%s\n", map[i].id, map[i].name);
  }
}

void Map_Print(Data_t **map, unsigned mapSize)
{
  for (unsigned i = 0; i < mapSize; i++) {
    for (unsigned j = 0; j < mapSize; j++) {
      if (map[i][j].roadLength[7] > 0 && i > 0 && j > 0)
        printf("\\");
      else
        printf(" ");
      if (map[i][j].roadLength[6] > 0 && i > 0)
        printf("|");
      else
        printf(" ");
      if (map[i][j].roadLength[5] > 0 && i > 0 && j < mapSize - 1)
        printf("/");
      else
        printf(" ");
    }
    printf("\n");

    for (unsigned j = 0; j < mapSize; j++) {
      if (map[i][j].roadLength[0] > 0 && j > 0)
        printf("-");
      else
        printf(" ");
      printf("C");
      if (map[i][j].roadLength[4] > 0 && j < mapSize - 1)
        printf("-");
      else
        printf(" ");
    }
    printf("\n");

    for (unsigned j = 0; j < mapSize; j++) {
      if (map[i][j].roadLength[1] > 0 && i < mapSize - 1 && j > 0)
        printf("/");
      else
        printf(" ");
      if (map[i][j].roadLength[2] > 0 && i < mapSize - 1)
        printf("|");
      else
        printf(" ");
      if (map[i][j].roadLength[3] > 0 && i < mapSize - 1 && j < mapSize - 1)
        printf("\\");
      else
        printf(" ");
    }
    printf("\n");
  }
}

void Map_Generate_DOT_File(Data_t *map, unsigned mapSize, char *path, char **cities)
{
  FILE *file = fopen(path, "w");
  fprintf(file, "graph {\n");
  for (unsigned i = 0; i < (mapSize * mapSize); i++) {
    for (unsigned k = 0; k < 8; k++) {
      if (map[i].roadLength[k] > 0)
        fprintf(file,
                "\"%s\" -- \"%s\" [label=\"%d km\"];\n",
                map[i].name,
                cities[map[i].roadCityIndex[k]],
                map[i].roadLength[k]);
    }
  }

  fprintf(file, "}");
  fclose(file);
}

/* Private function definitions ------------------------------------------------------------------*/