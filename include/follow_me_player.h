#pragma once

#include <include/clip.h>
#include <include/ticks_command.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace follow_me {

class FollowMePlayer {
private:
  // map with clip name as key and clip as value
  std::unordered_map<std::string, Clip> map_name_clip;

  // vector with names of the clips in the order they were added
  std::vector<std::string> clips;

  // ticks playback command
  TicksCommand ticks_command;

  // zero-based index of the current clip being played
  int clip_index;

  // current tick being played, zero-based
  long current_tick;

  // "recording" of which clip was played at each tick
  std::vector<std::string> recording;

  /**
   * @brief      Adds a clip
   *
   * Creates a clip and adds it to the map and list of clips.
   * If a clip with the same name already exists the new clip replaces the
   * existing, but retains the playback position of the existing clip
   *
   * @param[in]  str_clip  A string with a clip definition
   */
  void add_clip(std::string str_clip);

  /**
   * @brief      Adds a ticks commands from string input
   *
   * Creates a ticks command from a string input
   *
   * @param[in]  str_ticks_command  A string with a ticks command definition
   */
  void add_ticks_command(std::string str_ticks_command);

  /**
   * @brief      Gets the current clip.
   *
   * @return     Pointer to the clip currently played.
   */
  Clip *get_current_clip();

public:
  /**
   * @brief      Default constructor
   */
  FollowMePlayer();

  /**
   * @brief      Parses one line of input
   *
   * @param[in]  input  A string
   */
  void parse_input(std::string str);

  /**
   * @brief      Plays the next tick and handle follow action
   */
  void next_tick();

  /**
   * @brief      Starts the playback
   *
   * Continues until the number of ticks defined in the current ticks command
   * has been played
   */
  void play();

  /**
   * @brief      Gets the number of clips
   *
   * @return     number of clips
   */
  const size_t total_clips();

  /**
   * @brief      Gets the "recording" of which clip was played at each tick
   *
   * @return     a vector of clip names
   */
  const std::vector<std::string> get_recording();
};

} // namespace follow_me
