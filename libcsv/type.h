///
/// This file is part of libcsv library.
/// Distributed under the MIT License (http://opensource.org/licenses/MIT)
/// Copyright 2021 damianzim
///

#ifndef LIBCSV_TYPE_H_
#define LIBCSV_TYPE_H_

#include <ostream>
#include <sstream>
#include <string>

namespace csv::type {

struct Type {
  virtual std::string Stringify() const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Type& type) {
  return os << type.Stringify();
}

class Bool : public Type {
 public:
  Bool(bool value) : value_(value){};
  std::string Stringify() const override { return value_ ? "true" : "false"; }

 private:
  bool value_;
};

template <size_t Precision = 0>
class Float : public Type {
 public:
  Float(float value) : value_(value){};
  std::string Stringify() const override {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(Precision) << value_;
    return ss.str();
  }

 private:
  float value_;
};

}  // namespace csv::type

#endif  // LIBCSV_TYPE_H_
