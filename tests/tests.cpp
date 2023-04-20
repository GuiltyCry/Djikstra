/*!
 * \file       tests.cpp
 * \author     Sevcik, Jurena
 * \date       15. 2. 2022
 * \brief      Unit tests for dijkstra module.
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/

#include "gmock/gmock.h"

#include "gtest/gtest.h"
#include <limits>
#include <vector>

extern "C" {
#include "dijkstra.h"
#include "map.h"
}

/* Private types ---------------------------------------------------------------------------------*/
class DijkstraTestParam :
  public ::testing::TestWithParam<std::tuple<std::string, std::vector<unsigned>, bool>>
{
  // Test interface
protected:
  virtual void TearDown() override { Dijkstra_Destruct(&testDijkstra); }

  tDijkstra testDijkstra;
  Data_t mapHeap[1024];
};

/* Private function definitions ------------------------------------------------------------------*/
TEST(dijkstra, init)
{
  tDijkstra testDijkstra;

  ASSERT_TRUE(Dijkstra_Init(&testDijkstra, 9, 0));

  ASSERT_EQ(testDijkstra.distances[0], 0);
  for (int i = 1; i < 9; i++) {
    ASSERT_EQ(testDijkstra.distances[i], INF);
  }
}

TEST(dijkstra, initNulls)
{
  ASSERT_FALSE(Dijkstra_Init(NULL, 9, 0));
}

TEST(dijkstra, destruct)
{
  tDijkstra testDijkstra;
  Dijkstra_Init(&testDijkstra, 9, 0);

  Dijkstra_Destruct(&testDijkstra);

  ASSERT_EQ(testDijkstra.distances, nullptr);
  ASSERT_EQ(testDijkstra.visited, nullptr);
}

TEST(dijkstra, distanceCityArrayIsNull)
{
  tDijkstra testDijkstra;
  Dijkstra_Init(&testDijkstra, 9, 0);
  Dijkstra_Dist(NULL, &testDijkstra, 0, 1);
}

TEST(dijkstra, distanceDijkstraIsNull)
{
  Data_t arr[100];
  Dijkstra_Dist(arr, NULL, 0, 1);
}

TEST(dijkstra, distanceBothPointerAreNull)
{
  Dijkstra_Dist(NULL, NULL, 0, 1);
}

TEST(dijkstra, distanceStartCityIsSameAsEndCity)
{
  tDijkstra testDijkstra;
  Dijkstra_Init(&testDijkstra, 9, 0);
  Data_t arr[100];
  Dijkstra_Dist(arr, &testDijkstra, 0, 0);
}

TEST(dijkstra, destructNulls)
{
  Dijkstra_Destruct(NULL);
}

TEST_P(DijkstraTestParam, distance)
{
  auto [mapFile, expectedValues, expectedResult] = GetParam();
  FILE *testMapFile = fopen(mapFile.c_str(), "r");
  unsigned numOfCities = Map_Read_Map(mapHeap, testMapFile);
  unsigned source = 0;
  Dijkstra_Init(&testDijkstra, numOfCities, source);
  ASSERT_EQ(Dijkstra_Dist(mapHeap, &testDijkstra, source, 1), expectedResult);

  ASSERT_THAT(std::vector<unsigned>(testDijkstra.distances, testDijkstra.distances + numOfCities),
              ::testing::ElementsAreArray(expectedValues));

  if (testMapFile != NULL)
    fclose(testMapFile);
}

INSTANTIATE_TEST_SUITE_P(
  distance,
  DijkstraTestParam,
  testing::Values(
    std::make_tuple("test_files/map1.csv",
                    std::vector<unsigned>({0, 15, 20, 16, 19, 33, 26, 24, 26}),
                    true),
    std::make_tuple("test_files/map2.csv",
                    std::vector<unsigned>({0, 28, 12, 40, 9, 25, 33, 34, 45}),
                    true),
    std::make_tuple("test_files/map4.csv",
                    std::vector<unsigned>({0, INF, INF, INF, INF, INF, INF, INF, INF, 1}),
                    false)));
