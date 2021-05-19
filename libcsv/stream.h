///
/// This file is part of libcsv library.
/// Distributed under the MIT License (http://opensource.org/licenses/MIT)
/// Copyright 2021 damianzim
///

#ifndef LIBCSV_STREAM_H_
#define LIBCSV_STREAM_H_

#include <ostream>

namespace csv {

class NullOStream : public std::ostream {
 public:
  NullOStream() : std::ostream(nullptr){};
};

template <typename T>
inline const NullOStream& operator<<(const NullOStream& os, const T&) {
  return os;
}

}  // namespace csv

#endif  // LIBCSV_STREAM_H_
