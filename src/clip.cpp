#include <include/clip.h>
#include <include/util.h>

namespace follow_me {

Clip::Clip(std::string str_clip) {
  size_t i = 0;
  this->name = get_token(str_clip, i);
  this->ticks = stol(get_token(str_clip, i));
  auto chance1 = stod(get_token(str_clip, i));
  auto chance2 = stod(get_token(str_clip, i));
  auto action1 = get_token(str_clip, i);
  auto action2 = get_token(str_clip, i);

  this->action = FollowAction{chance1, chance2, action1, action2};
  this->tick_counter = 0;
}

Action Clip::play_tick(double random_value) {
  if (++this->tick_counter == this->ticks) {
    this->tick_counter = 0;
    return this->action.get_action(random_value);
  } else {
    return Action::None;
  }
}

} // namespace follow_me
