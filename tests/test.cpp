#define CATCH_CONFIG_MAIN
#include <include/catch.hpp>

#include <include/follow_me_player.h>
#include <include/ticks_command.h>
#include <include/util.h>

#include <string>
#include <vector>

using namespace follow_me;

TEST_CASE("test_util", "[util]") {
  SECTION("test function trim") {
    std::string str{" whitespace "};
    REQUIRE(trim(str) == "whitespace");
  }

  SECTION("test function get_token") {
    std::string str{"token1 token2 token3"};
    size_t pos = 0;
    auto expected = get_token(str, pos);
    REQUIRE(expected == "token1");
    expected = get_token(str, pos);
    REQUIRE(expected == "token2");
    expected = get_token(str, pos);
    REQUIRE(expected == "token3");
  }
}

TEST_CASE("test_follow_actions", "[follow_action][class]") {
  SECTION("test object construction and function get_action") {
    auto action1 = FollowAction{1.0, 0.0, "next", "none"};
    REQUIRE(action1.get_action(0.5) == Action::Next);

    action1 = FollowAction{0.0, 1.0, "next", "none"};
    REQUIRE(action1.get_action(0.5) == Action::None);
  }
}

TEST_CASE("test_ticks_command", "[ticks_command][class]") {
  SECTION("test object construction") {
    std::string cmd_str = "9 1.0 0.0 0.5 0.7 1.0 0.0 1.0 0.0 0.8 0.4 1.0 0.0 "
                          "0.6 0.2 1.0 0.0 0.9 0.4";
    TicksCommand cmd{cmd_str};
    REQUIRE(cmd.ticks() == 9);

    std::vector<std::pair<double, double>> expected = {
        {1.0, 0.0}, {0.5, 0.7}, {1.0, 0.0}, {1.0, 0.0}, {0.8, 0.4},
        {1.0, 0.0}, {0.6, 0.2}, {1.0, 0.0}, {0.9, 0.4}};

    REQUIRE_THAT(cmd.get_random_pairs(),
                 Catch::Matchers::Equals(expected));
  }
}

TEST_CASE("follow_me_player", "[follow_me_player][class]") {
  FollowMePlayer app;

  SECTION("test_playback_prev_next_wraparound") {
    std::string input[] = {"clip a 2 1.0 0.0 previous none",
                           "clip b 2 1.0 0.0 previous none",
                           "clip c 3 1.0 0.0 next none", "ticks 10"};

    for (auto const &line : input) {
      app.parse_input(line);
    }

    REQUIRE(app.total_clips() == 3);

    std::vector<std::string> expected{"a", "a", "c", "c", "c",
                                      "a", "a", "c", "c", "c"};
    REQUIRE_THAT(app.get_recording(), Catch::Matchers::Equals(expected));
  }

  SECTION("test_action_other_any_deterministic") {
    std::string clips[] = {
        "clip a 2 1.0 0.0 other any", "clip b 2 1.0 0.0 any none",
        "clip c 3 1.0 0.0 any next",
        "ticks 9 1.0 0.0 0.5 0.7 1.0 0.0 1.0 0.0 0.8 0.4 1.0 0.0 "
        "0.6 0.2 1.0 0.0 0.9 0.4"};

    for (auto const &line : clips) {
      app.parse_input(line);
    }

    std::vector<std::string> expected{"a", "a", "c", "c", "c",
                                      "b", "b", "a", "a"};
    REQUIRE_THAT(app.get_recording(), Catch::Matchers::Equals(expected));
  }
}
