#ifndef ROBOTBASE_HPP
#define ROBOTBASE_HPP

#include "statemachine.hpp"

/** Provides a simple implementation of a robot controlled by a finite-state
 * machine. */
template <class owner_t> class RobotBase
{
public:
    /** Initializes the class, changing the FSM to the given state.
     *
     * @param owner the class that owns this instance.
     * @param initial_state the robot's initial state.*/
    RobotBase(owner_t *owner, State <owner_t> *initial_state) : state_machine(owner) {
        state_machine.change_state(initial_state);
    }
    /** Updates the state machine with the new state.
     *
     * @param new_state the state to change to. */
    void change_state(State<owner_t> *new_state) {
        if(!new_state) throw std::invalid_argument("Cannot change to NULL state.");
        state_machine.change_state(new_state);
    }

    /** Returns the robot's previous state. */
    State<owner_t> *previous_state() {
        return state_machine.previous_state;
    }

    /** Abstract method to be called in the program's main loop. */
    virtual void update() = 0;
protected:
    /** Defines the robot's behavior. */
    StateMachine<owner_t> state_machine;
};

#endif              /* ROBOTBASE_HPP */
