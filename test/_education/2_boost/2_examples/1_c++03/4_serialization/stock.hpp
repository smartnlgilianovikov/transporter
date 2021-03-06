#ifndef SERIALIZATION_STOCK_HPP
#define SERIALIZATION_STOCK_HPP

#include <string>

namespace s11n_example {

/// Structure to hold information about a single stock.
struct stock
{
  std::string name;
  std::size_t size;
  std::string content;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & name;
    ar & size;
    ar & content;
  }
};

} // namespace s11n_example

#endif // SERIALIZATION_STOCK_HPP
