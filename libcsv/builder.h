///
/// This file is part of libcsv library.
/// Distributed under the MIT License (http://opensource.org/licenses/MIT)
/// Copyright 2021 damianzim
///

#ifndef LIBCSV_BUILDER_H_
#define LIBCSV_BUILDER_H_

#include <initializer_list>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

#include "libcsv/stream.h"

namespace csv {

template <typename... Args>
class CsvBuilder {
  static constexpr auto Columns() { return (sizeof...(Args)); }
  std::ostream& NullStream() {
    static auto kNull = NullOStream{};
    return kNull;
  }

 public:
  constexpr CsvBuilder(std::initializer_list<std::string_view> headers,
                       const char separator = ',')
      : sep_(separator), out_(&NullStream()) {
    if (headers.size() != Columns()) {
      // Skipping header creation
      return;
    }
    header_.resize([&]() constexpr->size_t {
      size_t size = 1;  // for \n
      for (const auto& header : headers)
        size += header.size() + 1;  // +1 for separator;
      return size;
    }());

    auto header_it = header_.data();
    for (const auto& header : headers) {
      std::memcpy(static_cast<void*>(header_it), header.data(), header.size());
      *(header_it += header.size()) = sep_;
      ++header_it;
    }
    *(--header_it) = '\n';
  }

  CsvBuilder<Args...>& operator<<(const std::tuple<Args...>& args) {
    assert(out_ != nullptr);
    std::stringstream row;
    std::apply([&](auto&&... arg) { ((row << arg << sep_), ...); }, args);
    row.seekp(-1, std::ios_base::end) << '\n';
    *out_ << row.str();
    return *this;
  }

  bool AssociateStream(std::ostream* os, bool print_header = true) {
    if (os == nullptr) {
      out_ = &NullStream();
      return false;
    }
    if (!os->good()) return false;
    out_ = os;
    if (print_header) *out_ << header_;
    return out_->good();
  }

  inline CsvBuilder<Args...>& BuildRow(const Args&... args) {
    assert(out_ != nullptr);
    return *this << std::forward_as_tuple(args...);
  }

 private:
  const char sep_;

  std::string header_;
  std::ostream* out_;
};

}  // namespace csv

#endif  // LIBCSV_BUILDER_H_
