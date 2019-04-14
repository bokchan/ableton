#pragma once

#include <random>
#include <vector>

namespace follow_me {

class TicksCommand {
  using vec_pairs_double = std::vector<std::pair<double, double>>;

private:
  // generator and engine for random double values
  std::mt19937 generator;
  std::uniform_real_distribution<double> uniform_random_double;

  // The pair of random values for each tick
  vec_pairs_double random_pairs;

  // The number of ticks in the command
  long ticks_;

  // flag to indicate if the playback is random, i.e. no random values were
  // defined
  bool is_random_;

public:
  TicksCommand() {}
  /**
   * @brief      Constructs the object from a string
   *
   * @param[in]  str_ticks_command  A string with a ticks command definition
   */
  TicksCommand(std::string str_ticks_command);

  /**
   * @brief      Gets the number of ticks in the command
   *
   * @return     number of ticks
   */
  const long ticks();

  /**
   * @brief      Gets the pairs of random values
   *
   * @return     The vector with pairs of random values
   */
  const vec_pairs_double get_random_pairs();

  /**
   * @brief      Gets the pair of random values for a specific tick by index
   *
   * If no random values were given at initialization a pair of random
   * numbers are generated
   *
   * @param[in]  tick_index  The tick index
   *
   * @return     A pair of probabilities
   */
  const std::pair<double, double> get_random_pair(size_t tick_index);

  /**
   * @brief      Checks whether playback is random
   *
   * @return     True if random, False otherwise.
   */
  bool is_random();
};

} // namespace follow_me
