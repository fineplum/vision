#include <Vision/Vision.hpp>

int main() {
  auto img = fp::Image{10, 10, fp::PixelFormat::RGBA, fp::BitDepth::F64};
  std::cout << sizeof(img) << std::endl;
  std::cout << img.about() << std::endl;
  return 0;
}
