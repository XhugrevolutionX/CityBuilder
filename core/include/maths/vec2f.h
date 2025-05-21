#ifndef VEC2F_H
#define VEC2F_H

namespace core
{
    class Vec2f
    {
    public:
        float x = 0.0f, y = 0.0f;

        constexpr Vec2f operator+(const Vec2f & v2) const noexcept
        {
            return {x + v2.x, y + v2.y};
        }

        constexpr Vec2f operator-(const Vec2f & v2) const noexcept
        {
            return {x - v2.x, y - v2.y};
        }

        constexpr Vec2f operator*(const Vec2f & v2) const noexcept
        {
            return {x * v2.x, y * v2.y};
        }

        constexpr Vec2f operator/(const Vec2f & v2) const noexcept
        {
            return {x / v2.x, y / v2.y};
        }

        constexpr float DotProduct(const Vec2f & v2) const noexcept
        {
            return {x * v2.x + y * v2.y};
        }

        double SquareLenght() const noexcept
        {
            return {pow(x,2) + pow(y, 2)};
        }

        double Lenght() const noexcept
        {
            return {sqrt(SquareLenght())};
        }

        Vec2f Normalize() const noexcept
        {
            float normalizedX = x / Lenght();
            float normalizedY = y / Lenght();
            return {normalizedX, normalizedY};
        }
    };
}

#endif //VEC2F_H