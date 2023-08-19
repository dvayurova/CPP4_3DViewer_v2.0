#include <gtest/gtest.h>

#include "../model/model_facade.h"

TEST(ViewerTest, Test_1) {
  std::string file_name = "";
  s21::Model model;
  model.ReadDataFile(file_name);
  EXPECT_EQ(model.GetEdgesCount(), 0);
  EXPECT_EQ(model.GetVertexCount(), 0);
  EXPECT_EQ(model.GetFacetsCount(), 0);
};

TEST(ViewerTest, Test_2) {
  std::string file_name = "cube.obj";
  s21::Model model;
  model.ReadDataFile(file_name);
  model.ChangeModel("rotate", 0.2, 1);
  EXPECT_EQ(model.GetEdgesCount(), 10);
  EXPECT_EQ(model.GetVertexCount(), 24);
  EXPECT_EQ(model.GetFacetsCount(), 60);
  EXPECT_EQ(model.GetVertexes()[model.GetEdgesCount()], 2);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 6);

  file_name = "lamp.obj";
  model.ReadDataFile(file_name);
  model.ChangeModel("rotate", 0.1, 2);
  EXPECT_EQ(model.GetEdgesCount(), 4403);
  EXPECT_EQ(model.GetVertexCount(), 13320);
  EXPECT_EQ(model.GetFacetsCount(), 35262);
  EXPECT_NEAR(model.GetVertexes()[model.GetEdgesCount()], -1.42317, 5);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 1680);

  file_name = "female.obj";
  model.ReadDataFile(file_name);
  model.ChangeModel("rotate", 0.3, 3);
  EXPECT_EQ(model.GetEdgesCount(), 124120);
  EXPECT_EQ(model.GetVertexCount(), 187014);
  EXPECT_EQ(model.GetFacetsCount(), 744720);
  EXPECT_NEAR(model.GetVertexes()[model.GetEdgesCount()], 6.93511, 5);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 13838);
};

TEST(ViewerTest, Test_3) {
  std::string file_name = "cube.obj";
  s21::Model model;
  model.ChangeModel("rotate", 0.2, 2);
  EXPECT_EQ(model.GetEdgesCount(), 10);
  EXPECT_EQ(model.GetVertexCount(), 24);
  EXPECT_EQ(model.GetFacetsCount(), 60);
  EXPECT_NEAR(model.GetVertexes()[model.GetEdgesCount()], 2, 5);
  EXPECT_EQ(model.GetFacets()[model.GetEdgesCount()], 6);
};

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
