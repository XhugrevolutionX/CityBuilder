#include "gtest/gtest.h"
#include "maths/vec2.h"

TEST(Vec2, EMPTY)
{
    constexpr core::Vec2<float> v;
    EXPECT_FLOAT_EQ(0, v.x);
    EXPECT_FLOAT_EQ(0, v.y);
}

TEST(Vec2, Add)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2 v1{x1,x2};
    constexpr core::Vec2 v2{y1,y2};

    constexpr auto result = v1 + v2;

    static_assert(result.x == x1 + y1);
    static_assert(result.y == x2 + y2);

    EXPECT_FLOAT_EQ(result.x, x1 + y1);
    EXPECT_FLOAT_EQ(result.y, x2 + y2);
}

TEST(Vec2, Sub)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2 v1{x1,x2};
    constexpr core::Vec2 v2{y1,y2};

    constexpr auto result = v1 - v2;

    static_assert(result.x == x1 - y1);
    static_assert(result.y == x2 - y2);

    EXPECT_FLOAT_EQ(result.x, x1 - y1);
    EXPECT_FLOAT_EQ(result.y, x2 - y2);
}

TEST(Vec2, Mult)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2 v1{x1,x2};
    constexpr core::Vec2 v2{y1,y2};

    constexpr auto result = v1 * v2;

    static_assert(result.x == x1 * y1);
    static_assert(result.y == x2 * y2);

    EXPECT_FLOAT_EQ(result.x, x1 * y1);
    EXPECT_FLOAT_EQ(result.y, x2 * y2);
}

TEST(Vec2, Div)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = 4;
    constexpr core::Vec2 v1{x1,x2};
    constexpr core::Vec2 v2{y1,y2};

    constexpr auto result = v1 / v2;

    EXPECT_FLOAT_EQ(result.x, x1 / y1);
    EXPECT_FLOAT_EQ(result.y, x2 / y2);
}

TEST(Vec2, DivByZero)
{
    float x1 = 1, x2 = 0;
    float y1 = 0, y2 = 0;
    core::Vec2 v1{x1,x2};
    core::Vec2 v2{y1,y2};

    auto result = v1 / v2;

    EXPECT_TRUE(isnan(result.x) || isnan(result.y) || isinf(result.x) || isinf(result.y));
}

TEST(Vec2, DotProd)
{
    constexpr float x1 = 2, x2 = 2;
    constexpr float y1 = 2, y2 = 3;
    constexpr core::Vec2 v1{x1,x2};
    constexpr core::Vec2 v2{y1,y2};

    constexpr auto result = v1.x * v2.x + v1.y * v2.y;

    EXPECT_FLOAT_EQ(result, v1.DotProduct(v2));
}

TEST(Vec2, SquareLength)
{
    float x1 = 2, x2 = 2;
    core::Vec2 v1{x1,x2};

    auto result = std::powf(v1.x, 2) + std::powf(v1.y, 2);

    EXPECT_FLOAT_EQ(result, v1.SquareLength());
}

TEST(Vec2, Length)
{
    float x1 = 2, x2 = 2;
    core::Vec2 v1{x1,x2};

    auto result = std::sqrt(v1.SquareLength());

    EXPECT_FLOAT_EQ(result, v1.Length());
}

TEST(Vec2, Normalize)
{
    float x1 = 2, x2 = 2;
    core::Vec2 v1{x1,x2};

    float length = v1.Length();

    float normalizedX = v1.x / length;
    float normalizedY = v1.y / length;

    core::Vec2 result = {normalizedX, normalizedY};

    auto normalized = v1.Normalize();

    EXPECT_FLOAT_EQ(result.x, normalized.x);
    EXPECT_FLOAT_EQ(result.y, normalized.y);
    EXPECT_FLOAT_EQ(normalized.Length(), 1.0f);
}

TEST(Vec2, NormalizeZero){
  float x1 = 0, x2 = 0;
  core::Vec2 v1{x1,x2};

  auto normalized = v1.Normalize();

  EXPECT_FLOAT_EQ(0, normalized.x);
  EXPECT_FLOAT_EQ(0, normalized.y);
  EXPECT_FLOAT_EQ(normalized.Length(), 0.0f);
}

TEST(Vec2, AngleBetween) {
  float x1 = 0, y1 = 5;
  float x2 = 5, y2 = 0;

  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};

  core::Degree deg{90};

  EXPECT_FLOAT_EQ(static_cast<float>(v1.AngleBetween(v2)), static_cast<float>(deg));
}

TEST(Vec2, Rotate) {
  float x1 = 5, y1 = 5;
  float x2 = -5, y2 = 5;

  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};

  core::Degree deg{90};

  v1.Rotate(deg);

  EXPECT_FLOAT_EQ(v1.x, v2.x);
  EXPECT_FLOAT_EQ(v1.y, v2.y);
}

TEST(Vec2, Perpendiculars) {
  float x1 = 4, y1 = 5;
  float x2 = -4, y2 = 5;
  float x3 = 4, y3 = -5;
  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};
  core::Vec2 v3{x3,y3};

  core::Vec2 per1 = v1.Perpendicular();
  core::Vec2 per2 = v1.Perpendicular2();

  EXPECT_FLOAT_EQ(per1.x, v2.x);
  EXPECT_FLOAT_EQ(per1.y, v2.y);
  EXPECT_FLOAT_EQ(per2.x, v3.x);
  EXPECT_FLOAT_EQ(per2.y, v3.y);
}
TEST(Vec2, AddEqual) {
  float x1 = 0, y1 = 5;
  float x2 = 0, y2 = 5;
  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};
  core::Vec2 v3{x1 + x2,y1 + y2};

  v1 += v2;
  EXPECT_FLOAT_EQ(v1.x, v3.x);
  EXPECT_FLOAT_EQ(v1.y, v3.y);
}
TEST(Vec2, MinusEqual) {
  float x1 = 0, y1 = 5;
  float x2 = 0, y2 = 5;
  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};
  core::Vec2 v3{x1 - x2,y1 - y2};

  v1 -= v2;
  EXPECT_FLOAT_EQ(v1.x, v3.x);
  EXPECT_FLOAT_EQ(v1.y, v3.y);
}
TEST(Vec2, MultiplyEqual) {
  float x1 = 0, y1 = 5;
  float x2 = 0, y2 = 5;
  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};
  core::Vec2 v3{x1 * x2,y1 * y2};

  v1 *= v2;
  EXPECT_FLOAT_EQ(v1.x, v3.x);
  EXPECT_FLOAT_EQ(v1.y, v3.y);
}
TEST(Vec2, DivideEqual) {
  float x1 = 0, y1 = 5;
  float x2 = 0, y2 = 5;
  core::Vec2 v1{x1,y1};
  core::Vec2 v2{x2,y2};
  core::Vec2 v3 = v1;
  if (x2 != 0.0f) {
    v3.x = x1 / x2;
  }
  if (y2 != 0.0f) {
    v3.y = y1 / y2;
  }

  v1 /= v2;
  EXPECT_FLOAT_EQ(v1.x, v3.x);
  EXPECT_FLOAT_EQ(v1.y, v3.y);
}

