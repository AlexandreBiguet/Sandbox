/// Try to implement the turnstile state machine
/// See: https://en.wikipedia.org/wiki/Finite-state_machine

#include <iostream>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/euml/common.hpp>
#include <boost/msm/front/functor_row.hpp>
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
    void on_entry(const Event&, StateMachine&) {}

    template <typename Event, typename StateMachine>
    void on_exit(const Event&, StateMachine&) {}
  };

  struct Unlocked : public msm::front::state<> {
    template <typename Event, typename StateMachine>
    void on_entry(const Event&, StateMachine&) {}

    template <typename Event, typename StateMachine>
    void on_exit(const Event&, StateMachine&) {}
  };

  using initial_state = Locked;

  /// Transitions actions

  struct Unlocking {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
      std::cout << "Unlocking\n";
    }
  };

  struct Buzz {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
      std::cout << "Buuuuuuuz\n";
    }
  };

  struct CheckCoinValue {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const& evt, FSM& fsm, SourceState& src,
                    TargetState& tgt) {
      return evt._value > 10.0;
    }
  };

  struct Trespassing {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&) {
      std::cout << "Going through\n";
    }
  };

  struct GetRich {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const& evt, FSM&, SourceState&, TargetState&) {
      std::cout << "adding " << evt._value << "$ \n";
    }
  };

  // clang-format off
  struct transition_table  // Note : this MUST be lower_snake_case
      : mpl::vector<
          msm::front::Row<Locked, OnCoinEvent, Unlocked, Unlocking,msm::front::none>,
          msm::front::Row<Locked, OnPushEvent, Locked, Buzz, msm::front::none>,
          msm::front::Row<Locked, OnCoinEvent, Locked, msm::front::none, CheckCoinValue>,
          msm::front::Row<Unlocked, OnPushEvent, Locked, Trespassing, msm::front::none>,
          msm::front::Row<Unlocked, OnCoinEvent, Locked, GetRich, msm::front::none> > {};
  // clang-format on

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
