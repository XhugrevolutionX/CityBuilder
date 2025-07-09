﻿#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <algorithm>
#include <array>
#include <span>
#include <tracy/Tracy.hpp>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif // TRACY_ENABLE

namespace core::experimental {

template<size_t N>
struct StringLiteral {
  constexpr StringLiteral(const char (&arg)[N]) {
    std::copy_n(arg, N, str);
  }
  char str[N];
};

template<typename TAsset, typename TAssetType, StringLiteral folderPath>
requires std::is_enum_v<TAssetType> && requires
{
  {static_cast<size_t>(TAssetType::kLength)};
}
class AssetManager {
  public:

  void Load(std::span<const std::string_view> assetsPaths) {
    for (size_t i = 0; i < assets_.size(); ++i) {
      assets_[i] = TAsset(std::format("{}/{}", folderPath.str, assetsPaths[i]));
    }
  }

  const TAsset &Get(TAssetType asset_index) {
    const auto index = static_cast<int64_t>(asset_index);
    if (index < 0 || index >= std::ssize(assets_)) {
      throw std::out_of_range("Invalid index");
    }
    return assets_[index];
  }
private:
  std::array<TAsset, static_cast<size_t>(TAssetType::kLength)> assets_{};
};

}


#endif
