#ifndef VEC2F_H
#define VEC2F_H

#include <filesystem>

#include "angle.h"
#include "func.h"

namespace core
{
    class Vec2f
    {
    public:
        float x = 0.0f, y = 0.0f;

        [[nodiscard]] constexpr Vec2f operator+(const Vec2f & v2) const noexcept
        {
            return {x + v2.x, y + v2.y};
        }

        [[nodiscard]] constexpr Vec2f operator-(const Vec2f & v2) const noexcept
        {
            return {x - v2.x, y - v2.y};
        }

        [[nodiscard]] constexpr Vec2f operator-() const
        {
            return {-x, -y};
        }

        [[nodiscard]] constexpr Vec2f operator*(const Vec2f & v2) const noexcept
        {
            return {x * v2.x, y * v2.y};
        }
        [[nodiscard]] constexpr Vec2f operator*(const float nb) const noexcept
        {
            return {x *nb, y * nb};
        }

        [[nodiscard]] constexpr Vec2f operator/(const Vec2f & v2) const noexcept
        {
            return {x / v2.x, y / v2.y};
        }

        [[nodiscard]] constexpr Vec2f operator/(float nb) const noexcept
        {
            return {x / nb, y / nb};
        }

        [[nodiscard]] constexpr float DotProduct(const Vec2f & v2) const noexcept
        {
            return {x * v2.x + y * v2.y};
        }

        [[nodiscard]] constexpr float SquareLength() const noexcept
        {
            return x * x + y * y;
        }

        [[nodiscard]] float Length() const noexcept
        {
            return std::sqrt(SquareLength());
        }


        [[nodiscard]] Vec2f Normalize() const noexcept {
            const auto length = Length();
            if (length == 0.0f) {
                return Vec2f{0.0f, 0.0f};
            }
            return *this / length;
        }

        [[nodiscard]] constexpr Vec2f Perpendicular() const  {
            return {-x, y};
        }
        [[nodiscard]] constexpr Vec2f Perpendicular2() const  {
            return {x, -y};
        }
        [[nodiscard]] constexpr Vec2f operator+=(const Vec2f & v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        [[nodiscard]] constexpr Vec2f operator-=(const Vec2f & v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        [[nodiscard]] constexpr Vec2f operator*=(const Vec2f & v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        [[nodiscard]] constexpr Vec2f operator/=(const Vec2f & v) {
          if (v.x != 0.0f) {
            x /= v.x;
          }
          if ( v.y != 0.0f) {
            y /= v.y;
          }
          return *this;
        }
        [[nodiscard]] constexpr Degree AngleBetween(const Vec2f & v2) const noexcept{
          Vec2f v{x,y};

          return Radian(std::acos(DotProduct(v2)/(v.Length() * v2.Length())));
        }
        [[nodiscard]] void Rotate(const Degree& addAngle) noexcept{

          Degree angle{core::Atan2(x,y)};

          angle += addAngle;

          x = Length() * core::Cos(angle);
          y = Length() * core::Sin(angle);
        }
    };

    [[nodiscard]] constexpr Vec2f operator*(float nb, const Vec2f & v2) noexcept {
        return v2 * nb;
    }
}

#endif //VEC2F_H