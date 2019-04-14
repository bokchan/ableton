#include <include/ticks_command.h>
#include <include/util.h>

#include <assert.h>

namespace follow_me {

using vec_pairs_double = std::vector<std::pair<double, double>>;

TicksCommand::TicksCommand(std::string str_ticks_command) {
  size_t i = 0;
  this->ticks_ = stol(get_token(str_ticks_command, i));

  while (i != std::string::npos) {
    double p1 = stod(get_token(str_ticks_command, i));
    double p2 = stod(get_token(str_ticks_command, i));
    random_pairs.emplace_back(p1, p2);
  }
  this->uniform_random_double =
      std::uniform_real_distribution<double>(0.0, 1.0);

  this->is_random_ = this->random_pairs.size() == 0;
}

const long TicksCommand::ticks() { return this->ticks_; }

const vec_pairs_double TicksCommand::get_random_pairs() {
  return this->random_pairs;
}

const std::pair<double, double>
TicksCommand::get_random_pair(size_t tick_index) {
  if (this->random_pairs.size() > 0) {
    assert(tick_index < this->random_pairs.size());
    return this->random_pairs.at(tick_index);
  } else {
    auto p1 = uniform_random_double(this->generator);
    auto p2 = uniform_random_double(this->generator);
    return std::make_pair(p1, p2);
  }
}

bool TicksCommand::is_random() { return this->is_random_; }

} // namespace follow_me
