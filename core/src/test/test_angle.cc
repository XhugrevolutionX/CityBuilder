#include "gtest/gtest.h"
#include "maths/angle.h"
#include "maths/func.h"
#include "maths/vec2f.h"

TEST(Vec2f, Conversion) {
  core::Degree degree{45.0f};
  auto result = core::Cos(degree);
  EXPECT_FLOAT_EQ(result, std::cos(core::Pi/4.0f));
}

TEST(Vec2f, Cos) {
  float x = 2, y = 5;
  core::Vec2f v{x,y};

  core::Radian angle{core::Atan2(x,y)};

  EXPECT_FLOAT_EQ(core::Cos(angle), v.x/v.Length());
}
TEST(Vec2f, Sin) {
  float x = 2, y = 5;
  core::Vec2f v{x,y};

  core::Radian angle{core::Atan2(x,y)};

  EXPECT_FLOAT_EQ(core::Sin(angle), v.y/v.Length());
}
TEST(Vec2f, Tan) {
  float x = 2, y = 5;
  core::Vec2f v{x,y};

  core::Radian angle{core::Atan2(x,y)};

  EXPECT_FLOAT_EQ(core::Tan(angle), v.y/v.x);
}
TEST(Vec2f, Acos) {
  float x = 5, y = 5;

  core::Radian angle{core::Atan2(x,y)};

  auto result = core::Cos(angle);
  auto result2 = core::Acos(result);

  EXPECT_FLOAT_EQ(static_cast<float>(result2), static_cast<float>(angle));
}
TEST(Vec2f, Asin) {
  float x = 5, y = 5;

  core::Radian angle{core::Atan2(x,y)};

  auto result = core::Sin(angle);
  auto result2 = core::Asin(result);

  EXPECT_FLOAT_EQ(static_cast<float>(result2), static_cast<float>(angle));
}
TEST(Vec2f, Atan) {
  float x = 5, y = 5;

  core::Radian angle{core::Atan2(x,y)};

  auto result = core::Tan(angle);
  auto result2 = core::Atan(result);

  EXPECT_FLOAT_EQ(static_cast<float>(result2), static_cast<float>(angle));
}
TEST(Vec2f, Atan2) {

}