#include <algorithm>


#include "gtest/gtest.h"
#include "maths/vec2f.h"

TEST(Vec2f, EMPTY)
{
    core::Vec2f v;
    EXPECT_FLOAT_EQ(0, v.x);
    EXPECT_FLOAT_EQ(0, v.y);
}

TEST(Vec2f, Add)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2f v1{x1,x2};
    constexpr core::Vec2f v2{y1,y2};

    constexpr auto result = v1 + v2;

    static_assert(result.x == x1 + y1);
    static_assert(result.y == x2 + y2);

    EXPECT_FLOAT_EQ(result.x, x1 + y1);
    EXPECT_FLOAT_EQ(result.y, x2 + y2);
}

TEST(Vec2f, Sub)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2f v1{x1,x2};
    constexpr core::Vec2f v2{y1,y2};

    constexpr auto result = v1 - v2;

    static_assert(result.x == x1 - y1);
    static_assert(result.y == x2 - y2);

    EXPECT_FLOAT_EQ(result.x, x1 - y1);
    EXPECT_FLOAT_EQ(result.y, x2 - y2);
}

TEST(Vec2f, Mult)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = -4;

    constexpr core::Vec2f v1{x1,x2};
    constexpr core::Vec2f v2{y1,y2};

    constexpr auto result = v1 * v2;

    static_assert(result.x == x1 * y1);
    static_assert(result.y == x2 * y2);

    EXPECT_FLOAT_EQ(result.x, x1 * y1);
    EXPECT_FLOAT_EQ(result.y, x2 * y2);
}

TEST(Vec2f, Div)
{
    constexpr float x1 = 1, x2 = 2;
    constexpr float y1 = 3, y2 = 4;
    constexpr core::Vec2f v1{x1,x2};
    constexpr core::Vec2f v2{y1,y2};

    constexpr auto result = v1 / v2;

    EXPECT_FLOAT_EQ(result.x, x1 / y1);
    EXPECT_FLOAT_EQ(result.y, x2 / y2);
}

TEST(Vec2f, DivByZero)
{
    float x1 = 1, x2 = 0;
    float y1 = 0, y2 = 0;
    core::Vec2f v1{x1,x2};
    core::Vec2f v2{y1,y2};

    auto result = v1 / v2;

    EXPECT_TRUE(isnan(result.x) || isnan(result.y) || isinf(result.x) || isinf(result.y));
}

TEST(Vec2f, DotProd)
{
    constexpr float x1 = 2, x2 = 2;
    constexpr float y1 = 2, y2 = 3;
    constexpr core::Vec2f v1{x1,x2};
    constexpr core::Vec2f v2{y1,y2};

    constexpr auto result = v1.x * v2.x + v1.y * v2.y;

    EXPECT_FLOAT_EQ(result, v1.DotProduct(v2));
}

TEST(Vec2f, SquareLenght)
{
    float x1 = 2, x2 = 2;
    core::Vec2f v1{x1,x2};

    double result = pow(v1.x, 2) + pow(v1.y, 2);

    EXPECT_FLOAT_EQ(result, v1.SquareLenght());
}

TEST(Vec2f, Lenght)
{
    float x1 = 2, x2 = 2;
    core::Vec2f v1{x1,x2};

    double result = sqrt(pow(v1.x, 2) + pow(v1.y, 2));

    EXPECT_FLOAT_EQ(result, v1.Lenght());
}

TEST(Vec2f, Normalize)
{
    float x1 = 2, x2 = 2;
    core::Vec2f v1{x1,x2};

    float normalizedX = v1.x / v1.Lenght();
    float normalizedY = v1.y / v1.Lenght();

    core::Vec2f result = {normalizedX, normalizedY};

    EXPECT_FLOAT_EQ(result.x, v1.Normalize().x);
    EXPECT_FLOAT_EQ(result.y, v1.Normalize().y);
}
