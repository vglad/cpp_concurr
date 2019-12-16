#ifndef CPP_CONCURR_INCLUDE_DETAIL_UTILS_HPP
#define CPP_CONCURR_INCLUDE_DETAIL_UTILS_HPP

#include <vector>
#include <iterator>
#include <sstream>
#include <memory>
#include <algorithm>
#include <chrono>

namespace detail {

//*****************************************************************************
// Execution time measurement functions
// Can return container of any type

using namespace std::chrono;
using time_point = high_resolution_clock::time_point;

[[maybe_unused]] static auto time_now() -> time_point {
  return high_resolution_clock::now();
}

//supress MSVS warning about unreferenced local function
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4505)  
#endif
[[maybe_unused]] static auto time_elapsed(time_point const& start_time) -> float {
  return duration_cast<duration<float>>(time_now() - start_time).count();
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif
//*****************************************************************************

//*****************************************************************************
// This tokenizer works only with strings delimited by whitespace
// Can return container of any type
template <typename T>
std::vector<T> tokenize_by_whitespace(std::string const& s) {
  std::istringstream iss(s);
  return { std::istream_iterator<T>{iss}, std::istream_iterator<T>{} };
}
//*****************************************************************************

//*****************************************************************************
// This is general tokenizer
// Returns only containers of <std::string>
// !!!Do not work if returns containers of numeric type
template <typename ContainerT>
ContainerT tokenize_by_delim(std::string const& str,
                             std::string const& delimiters = " ",
                             bool               trimEmpty = false) {
  std::string::size_type pos, lastPos = 0, length = str.length();

  ContainerT tokens;
  using value_type = typename ContainerT::value_type;
  using size_type  = typename ContainerT::size_type;

  while (lastPos < length + 1) {
    pos = str.find_first_of(delimiters, lastPos);
    if (pos == std::string::npos) pos = length;
    if (pos != lastPos || !trimEmpty) {
      tokens.emplace_back(value_type(str.data() + lastPos,
        (size_type)pos - lastPos));
    }
    lastPos = pos + 1;
  }
  return tokens;
}
//*****************************************************************************

//*****************************************************************************
// Erases non-numeric values from container (\n,\t,\r, \t\t, " "...)
template<typename ContainerT>
ContainerT erase_empty_non_num_values(std::unique_ptr<ContainerT> pCont) {
  ContainerT& v = *pCont;
  auto remove_empty =
    [](std::string const& s) {
    try {
      std::stold(s);
      return false;
    } catch (...) {
      return true;
    }
  };
  v.erase(std::remove_if(begin(v), end(v), remove_empty), end(v));
  return v;
}
//*****************************************************************************

//*****************************************************************************
// Creates new container of num type from container of strings
template<typename ContainerIn, typename ContainerOut>
ContainerOut str_to_num(std::unique_ptr<ContainerIn> pContIn) {
  ContainerIn& vIn = *pContIn;
  ContainerOut vOut;
  auto to_num = [&vOut](std::string const& s) { vOut.emplace_back(std::stoi(s)); };
  std::for_each(begin(vIn), end(vIn), to_num);
  return vOut;
}
//*****************************************************************************

//*****************************************************************************
//Turn an expression into a type
//https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/20170989#20170989
//*****************************************************************************
#ifndef _MSC_VER
#  if __cplusplus < 201103
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif __cplusplus < 201402
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#else  // _MSC_VER
#  if _MSC_VER < 1900
#    define CONSTEXPR11_TN
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN
#  elif _MSC_VER < 2000
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN
#    define NOEXCEPT_TN noexcept
#  else
#    define CONSTEXPR11_TN constexpr
#    define CONSTEXPR14_TN constexpr
#    define NOEXCEPT_TN noexcept
#  endif
#endif  // _MSC_VER

class static_string {
  char const* const p_;
  std::size_t const sz_;
public:
  typedef char const* const_iterator;

  template <std::size_t N>
  CONSTEXPR11_TN explicit static_string(const char(&a)[N]) NOEXCEPT_TN
    : p_(a), sz_(N - 1) {
  }

  CONSTEXPR11_TN static_string(char const* p, std::size_t N) NOEXCEPT_TN
    : p_(p), sz_(N) {
  }

  [[nodiscard]] CONSTEXPR11_TN char const* data() const NOEXCEPT_TN { return p_; }
  [[nodiscard]] CONSTEXPR11_TN std::size_t size() const NOEXCEPT_TN { return sz_; }
  [[nodiscard]] CONSTEXPR11_TN const_iterator begin() const NOEXCEPT_TN { return p_; }
  [[nodiscard]] CONSTEXPR11_TN const_iterator end()   const NOEXCEPT_TN { return p_ + sz_; }

  CONSTEXPR11_TN char operator[](std::size_t n) const {
    return n < sz_ ? p_[n] : throw std::out_of_range("static_string");
  }

};

inline std::ostream& operator<<(std::ostream& os, static_string const& s) {
  return os.write(s.data(), s.size());
}

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<        ";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}
//*****************************************************************************


}

#endif //CPP_CONCURR_INCLUDE_DETAIL_UTILS_HPP