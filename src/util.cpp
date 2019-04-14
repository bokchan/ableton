#include <string>

namespace follow_me {

std::string get_token(std::string str, size_t &pos, std::string delim = " ") {
  std::size_t found = str.find(delim, pos);
  std::string token = str.substr(pos, found - pos);
  pos = found != std::string::npos ? found + 1 : std::string::npos;
  return token;
}

std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(' ');
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, (last - first + 1));
}
} // namespace follow_me
