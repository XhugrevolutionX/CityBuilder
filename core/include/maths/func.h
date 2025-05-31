
#ifndef CORE_MATHS_FUNC_H
#define CORE_MATHS_FUNC_H
#include <cmath>

namespace core {

inline float Cos(Radian angle) {
  return std::cos(static_cast<float>(angle));
}
inline float Sin(Radian angle) {
  return std::sin(static_cast<float>(angle));
}
inline float Tan(Radian angle) {
  return std::tan(static_cast<float>(angle));
}
inline Radian Acos(float ratio) {
  return static_cast<Radian>(std::acos(ratio));
}
inline Radian Asin(float ratio) {
  return static_cast<Radian>(std::asin(ratio));
}
inline Radian Atan(float ratio) {
  return static_cast<Radian>(std::atan(ratio));
}
inline Radian Atan2(float x, float y) {
  return static_cast<Radian>(std::atan2(y,x));
}

}

#endif //CORE_MATHS_FUNC_H
