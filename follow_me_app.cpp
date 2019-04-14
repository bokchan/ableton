#include <iostream>

#include <include/follow_me_player.h>
#include <include/util.h>

using namespace follow_me;

/**
 * @brief      Reads input from stdin
 *
 * Reads input from stdin and passes it to a new FollowMePlayer instance
 */
int main(int argc, char **argv) {
  FollowMePlayer player;

  std::string line;
  while (std::getline(std::cin, line)) {
    line = trim(line);
    if (line.size() > 0) {
      player.parse_input(line);
    }
  }

  return 0;
}
