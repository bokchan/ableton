#pragma once

#include <string>
#include <unordered_map>

namespace follow_me {

/**
 * @brief       enum of follow actions
 *
 * None         : Nothing happens – the clip keeps playing.
 * Any          : Any clip (including the playing one) can be triggered.
 * Other        : Any other clip can be triggered.
 * Next         : The next clip (in the order they were created) will be
 * triggered. Previous : The previous clip will be triggered.
 */
enum class Action { None, Any, Other, Next, Previous };

class FollowAction {
private:
  // mapping from a string to an Action enum value
  static std::unordered_map<std::string, Action> map_str_action_enum;

  // Associated trigger actions for the clip
  Action action1, action2;

  // A floating-point value in the interval [0,1.0) used for which to choose
  // either action1 or action2
  double mid_point;

  /**
   * @brief      Convert from a string to the corresponding Action enum value
   *
   * @param[in]  str_action  The action as string
   *
   * @return     An Action enum if the action is found, else Action::None
   */
  static Action str_to_action(std::string str_action);

public:
  /**
   * @brief      Default constructor.
   */
  FollowAction() = default;

  /**
   * @brief      Constructs the object and calculates the mid_point
   *
   * @param[in]  chance1  The chance of action 1
   * @param[in]  chance2  The chance of action 2
   * @param[in]  action1  The action 1 as string
   * @param[in]  action2  The action 2 as string
   */
  FollowAction(double chance1, double chance2, std::string action1,
               std::string action2);

  /**
   * @brief      Returns a follow action
   *
   * If the argument random_value is less than mid_point, action1 is chosen
   * otherwise action2
   *
   * @return     A follow action.
   */
  Action get_action(double random_value);
};

} // namespace follow_me
