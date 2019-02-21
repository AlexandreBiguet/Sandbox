/// Try to implement the turnstile state machine
/// See: https://en.wikipedia.org/wiki/Finite-state_machine

#include <iostream>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

/// Two states
///  - Locked (initial)
///  - Unlocked

/// One events
///  - coin

/// One action
///  - push

// TODO :
//  - add a light with two states. If the light is green the turnstile is
//    unlocked. If red then locked

namespace {

struct OnCoinEvent {
  OnCoinEvent(int value = 5) : _value(value) {}
  int _value;
};

struct OnPushEvent {
  OnPushEvent(double power = 120.0) : _power(power) {}
  double _power;
};

struct Turnstile : public msm::front::state_machine_def<Turnstile> {
  template <typename Event, typename StateMachine>
  void on_entry(const Event&, StateMachine&) {
    std::cout << "Show time\n";
  }

  template <typename Event, typename StateMachine>
  void on_exit(const Event&, StateMachine&) {
    std::cout << "Bye bye\n";
  }

  struct Locked : public msm::front::state<msm::front::default_base_state> {
    template <typename Event, typename StateMachine>
    void on_entry(const Event&, StateMachine&) {
      // TODO : light is red
      // std::cout << "Locked State : In\n";
    }

    template <typename Event, typename StateMachine>
    void on_exit(const Event&, StateMachine&) {
      // TODO : light is green
      // std::cout << "Locked State : Out\n";
    }
  };

  struct Unlocked : public msm::front::state<> {
    template <typename Event, typename StateMachine>
    void on_entry(const Event&, StateMachine&) {
      // TODO : light is green
      // std::cout << "UnLocked State : In\n";
    }

    template <typename Event, typename StateMachine>
    void on_exit(const Event&, StateMachine&) {
      // TODO : light is red
      // std::cout << "UnLocked State : Out\n";
    }
  };

  using initial_state = Locked;

  /// Transitions actions
  void unlocking(const OnCoinEvent&) { std::cout << "Unlocking \n"; }

  void buzz(const OnPushEvent&) { std::cout << "Buuuuuuuz\n"; }

  bool check_coin_value(const OnCoinEvent& on_coin_event) {
    return on_coin_event._value > 10.0;
  }

  void trespassing(const OnPushEvent&) { std::cout << "Going through\n"; }

  void get_rich(const OnCoinEvent& evt) {
    std::cout << "adding " << evt._value << "$ \n";
  }

  struct transition_table  // Note : this MUST be lower_snake_case
      : mpl::vector<
            a_row<Locked, OnCoinEvent, Unlocked, &Turnstile::unlocking>,
            a_row<Locked, OnPushEvent, Locked, &Turnstile::buzz>,
            g_row<Locked, OnCoinEvent, Locked, &Turnstile::check_coin_value>,
            a_row<Unlocked, OnPushEvent, Locked, &Turnstile::trespassing>,
            a_row<Unlocked, OnCoinEvent, Locked, &Turnstile::get_rich> > {};

  template <class FSM, class Event>
  void no_transition(Event const& e, FSM&, int state) {
    std::cout << "no transition from state " << state << " on event "
              << typeid(e).name() << std::endl;
  }
};

}  // namespace

static char const* const state_names[] = {"Locked", "Unlocked"};
void log_state(msm::back::state_machine<Turnstile> const& p) {
  std::cout << " -> Current State is: " << state_names[p.current_state()[0]]
            << std::endl;
}

int main() {
  msm::back::state_machine<Turnstile> machine;
  machine.start();
  log_state(machine);
  machine.process_event(OnCoinEvent());
  log_state(machine);
  machine.stop();
  return 0;
}
