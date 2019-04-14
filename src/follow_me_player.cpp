#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>

#include <include/follow_me_player.h>
#include <include/util.h>

namespace follow_me {

void FollowMePlayer::add_clip(std::string str_clip) {
  auto _clip = Clip{str_clip};

  auto it = map_name_clip.find(_clip.name);
  if (it == map_name_clip.end()) {
    map_name_clip.insert({_clip.name, _clip});
    clips.push_back(_clip.name);
  } else {
    it->second = _clip;
  }
}

void FollowMePlayer::add_ticks_command(std::string str_ticks_command) {
  this->ticks_command = TicksCommand{str_ticks_command};
}

Clip *FollowMePlayer::get_current_clip() {
  auto name = this->clips.at(this->clip_index);
  return &this->map_name_clip.find(name)->second;
}

FollowMePlayer::FollowMePlayer() {
  this->clip_index = 0;
  this->current_tick = 0;
}

void FollowMePlayer::parse_input(std::string str) {
  std::size_t found = str.find_first_of(" ");
  if (found != std::string::npos) {
    std::string type = str.substr(0, found);
    if (type.compare("clip") == 0) {
      this->add_clip(str.substr(found + 1));
    } else if (type.compare("ticks") == 0) {
      this->add_ticks_command(str.substr(found + 1));
      this->play();
    }
  }
}

void FollowMePlayer::next_tick() {
  auto clip = this->get_current_clip();

  // get the pair of random values for the current tick.
  // first value is to choose the the action, the second value is to choose the
  // clip
  auto random_values = this->ticks_command.get_random_pair(this->current_tick);

  // play one tick and use the returned value to determine which action
  // should be triggered
  switch (clip->play_tick(random_values.first)) {
  case Action::None:
    break;
  case Action::Any: {
    // choose the next clip index in the range [0,number_of_clips)
    this->clip_index =
        static_cast<int>(random_values.second * this->total_clips());
    break;
  }
  case Action::Other: {
    // For random playback the index chosen from [0,number_of_clips-1)
    //
    // For deterministic playback the index is chosen from [0,number_of_clips)
    // and if the index is the same as the current clip index, number_of_clips-1
    // is used as the index of the next clip.
    auto tmp = random_values.second *
               (this->total_clips() - this->ticks_command.is_random());
    this->clip_index =
        (tmp == this->clip_index) ? this->total_clips() - 1 : tmp;
    break;
  }
  case Action::Next:
    // advance to the next clip with wraparound
    ++this->clip_index;
    this->clip_index = this->clip_index % this->total_clips();
    break;
  case Action::Previous:
    // advance to the previous clip with wraparound
    this->clip_index =
        (this->clip_index + this->total_clips() - 1) % this->total_clips();
    break;
  default:
    assert(false);
    break;
  }
}

void FollowMePlayer::play() {
  this->current_tick = 0;
  while (this->current_tick < this->ticks_command.ticks()) {
    this->recording.push_back(this->get_current_clip()->name);
    printf("%s\n", this->get_current_clip()->name.c_str());
    this->next_tick();

    this->current_tick++;
  }
}

const size_t FollowMePlayer::total_clips() { return this->clips.size(); }

const std::vector<std::string> FollowMePlayer::get_recording() {
  return this->recording;
}

} // namespace follow_me
