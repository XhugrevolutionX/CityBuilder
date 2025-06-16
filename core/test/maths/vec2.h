#ifndef VEC2_H
#define VEC2_H

#include <filesystem>

#include "angle.h"
#include "func.h"

namespace core
{
    template <typename VectorT, typename T>
    concept is_vector2 = requires(VectorT v)
    {
        { v.x } -> std::same_as<T&>;
        { v.y } -> std::same_as<T&>;
    };

    template <typename VectorT, typename T>
    concept is_convertible_to_vector2 = requires(VectorT v)
    {
        { v.x } -> std::convertible_to<T>;
        { v.y } -> std::convertible_to<T>;
    };

    template <typename T>
        requires std::is_arithmetic_v<T>
    class Vec2
    {
    public:
        T x{}, y{};
        constexpr Vec2() = default;
        constexpr Vec2(T x, T y) : x{x}, y{y} {}

        template <typename VectorT>
            requires is_vector2<VectorT, T>
        constexpr explicit Vec2(VectorT v) : x(v.x), y(v.y) {}

        template <typename VectorT>
            requires is_convertible_to_vector2<VectorT, T> && !is_vector2<VectorT, T>
        constexpr explicit Vec2(VectorT v)
            : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

        template <typename VectorT>
            requires is_vector2<VectorT, T>
        explicit constexpr operator VectorT() const {
            return VectorT{x, y};
        }
        //Operators
        [[nodiscard]] constexpr Vec2 operator+(const Vec2 & v2) const noexcept
        {
            return {x + v2.x, y + v2.y};
        }
        [[nodiscard]] constexpr Vec2 operator-(const Vec2 & v2) const noexcept
        {
            return {x - v2.x, y - v2.y};
        }
        [[nodiscard]] constexpr Vec2 operator-() const
        {
            return {-x, -y};
        }
        [[nodiscard]] constexpr Vec2 operator*(const Vec2 & v2) const noexcept
        {
            return {x * v2.x, y * v2.y};
        }
        [[nodiscard]] constexpr Vec2 operator*(const T nb) const noexcept
        {
            return {x * nb, y * nb};
        }
        [[nodiscard]] constexpr Vec2 operator/(const Vec2 & v2) const noexcept
        {
            return {x / v2.x, y / v2.y};
        }
        [[nodiscard]] constexpr Vec2 operator/(T nb) const noexcept
        {
            return {x / nb, y / nb};
        }

        constexpr bool operator==(const Vec2& other) const {
            return x == other.x && y == other.y;
        }
        constexpr Vec2 operator+=(const Vec2 & v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        constexpr Vec2 operator-=(const Vec2 & v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        constexpr Vec2 operator*=(const Vec2 & v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        constexpr Vec2 operator/=(const Vec2 & v) {
            if (v.x != 0.0f) {
                x /= v.x;
            }
            if ( v.y != 0.0f) {
                y /= v.y;
            }
            return *this;
        }
        //Methods
        [[nodiscard]] constexpr T DotProduct(const Vec2 & v2) const noexcept
        {
            return {x * v2.x + y * v2.y};
        }
        [[nodiscard]] constexpr T SquareLength() const noexcept
        {
            return x * x + y * y;
        }
        [[nodiscard]] float Length() const noexcept
        {
            return std::sqrt(SquareLength());
        }
        [[nodiscard]] Vec2 Normalize() const noexcept {
            const auto length = Length();
            if (length == 0) {
                return Vec2{0, 0};
            }
            return *this / length;
        }
        [[nodiscard]] constexpr Vec2 Perpendicular() const  {
            return {-x, y};
        }
        [[nodiscard]] constexpr Vec2 Perpendicular2() const  {
            return {x, -y};
        }

        [[nodiscard]] constexpr Degree AngleBetween(const Vec2 & v2) const noexcept{
          Vec2 v{x,y};

          return Radian(std::acos(DotProduct(v2)/(v.Length() * v2.Length())));
        }
        void Rotate(const Degree& addAngle) noexcept{

          Degree angle{core::Atan2(x,y)};

          angle += addAngle;

          x = Length() * core::Cos(angle);
          y = Length() * core::Sin(angle);
        }
    };
    template <typename VectorT, typename T>
    [[nodiscard]] constexpr VectorT operator*(T nb, const VectorT & v2) noexcept {
        return v2 * nb;
    }
}

#endif //VEC2_H