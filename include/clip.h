#pragma once

#include <include/follow_action.h>

#include <string>

namespace follow_me {

class Clip {
public:
  // clip name
  std::string name;

  // clip length in ticks
  long ticks;

  // follow action for the clip
  FollowAction action;

  // counts the number of ticks played
  long tick_counter;

  /**
   * @brief      Constructs the object from a string
   *
   * @param[in]  str_clip  A string with a clip definition
   */
  Clip(std::string str_clip);

  /**
   * @brief      Plays one tick of and return the clip's trigger action
   *
   * If the clip is not finished Action::None is returned.
   * If the clip has played till the end, the argument `random_value` is used
   * to determine the trigger action.
   *
   * @param[in]  random_value
   *
   * @return     A follow action
   */
  Action play_tick(double random_value);
};

} // follow_me
