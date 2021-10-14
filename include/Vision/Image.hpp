#ifndef FP__VISION__IMAGE_HPP_
#define FP__VISION__IMAGE_HPP_

#include <iostream>
#include <sstream>

#include "Core.hpp"

namespace fp {

enum class ColorModel : uint8 { G0, G1, G2, G3, G4, G5, G6, G7 };
enum class PixelFormat : uint8 { Custom, Mono, Gray, RGB, RGBA };

enum class BitDepth : uint8 { I8 = 1, I16 = 2, F32 = 3, F64 = 4 };

class MetaPixel {
 private:
  ColorModel model_ = ColorModel::G3;
  PixelFormat fmt_ = PixelFormat::RGB;
  BitDepth bitDepth_ = BitDepth::I8;
  bool free;  // wasted space

 public:
  MetaPixel() = default;
  ~MetaPixel() = default;

  MetaPixel(ColorModel model, BitDepth depth = BitDepth::I8)
      : model_{model}, fmt_{PixelFormat::Custom}, bitDepth_{depth} {}

  MetaPixel(PixelFormat fmt, BitDepth depth = BitDepth::I8)
      : fmt_{fmt}, model_{static_cast<ColorModel>(fmt)}, bitDepth_{depth} {}

  auto model() const -> uint16 { return static_cast<uint16>(model_); }
  auto format() const -> uint16 { return static_cast<uint16>(fmt_); }
  auto depth() const -> uint16 { return static_cast<uint16>(bitDepth_); }
};

class Image {
 private:
  uint32 width_ = 0;
  uint32 height_ = 0;
  MetaPixel metaPix_ = {};
  uint32 bufferSize_ = 0;

  byte *data_ = nullptr;

 public:
  Image() = default;

  Image(uint32 width, uint32 height, MetaPixel metaPix = {})
      : width_{width}, height_{height}, metaPix_{metaPix} {
    bufferSize_ = width * height * metaPix_.model() * metaPix_.depth();
    data_ = new byte[bufferSize_];
  }

  Image(uint32 width, uint32 height, ColorModel model,
        BitDepth depth = BitDepth::I8)
      : Image{width, height, {model, depth}} {}

  Image(uint32 width, uint32 height, PixelFormat fmt,
        BitDepth depth = BitDepth::I8)
      : Image{width, height, {fmt, depth}} {}

  ~Image() { delete[] data_; }

  auto width() const -> uint32 { return width_; }
  auto height() const -> uint32 { return height_; }
  auto metadata() const -> const MetaPixel & { return metaPix_; }
  auto bufferSize() const -> uint32 { return bufferSize_; }

  auto about() {
    auto stream = std::stringstream{};
    stream << "[ width=" << this->width() << ", height=" << this->height()
           << ", channels=" << this->metadata().model()
           << ", depth=" << this->metadata().depth() << " ]";
    return stream.str();
  }
};

}  // namespace fp

#endif
