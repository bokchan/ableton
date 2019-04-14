#include <include/follow_action.h>
#include <include/util.h>

#include <ctime>

namespace follow_me {

Action FollowAction::str_to_action(std::string str_action) {
  auto action = map_str_action_enum.find(str_action);
  if (action != map_str_action_enum.end()) {
    return action->second;
  }

  return Action::None;
}

FollowAction::FollowAction(double chance1, double chance2, std::string action1,
                           std::string action2) {
  this->mid_point = chance1 / (chance1 + chance2);
  this->action1 = this->str_to_action(action1);
  this->action2 = this->str_to_action(action2);
}

Action FollowAction::get_action(double random_value) {
  return random_value < this->mid_point ? this->action1 : this->action2;
}

std::unordered_map<std::string, Action> FollowAction::map_str_action_enum = {
    {"none", Action::None},
    {"any", Action::Any},
    {"other", Action::Other},
    {"next", Action::Next},
    {"previous", Action::Previous}};

} // namespace follow_me
