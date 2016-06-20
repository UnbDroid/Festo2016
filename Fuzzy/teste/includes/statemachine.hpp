#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stdexcept>

/** Abstract class to define interfacing with a state. */
template <class owner_t> class State
{
public:
    virtual ~State() {}
    /** Called when this becomes the current state. */
    virtual void enter(owner_t *) {}
    /* Called to execute the tasks in the current state. */
    virtual void execute(owner_t *) = 0;
    /* Called when this is no longer the current state. */
    virtual void exit(owner_t *) {}
};

/** Defines a finite state machine (FSM). Provides a simple implementation of the
 * example given in the book
 * <a href="http://www.ai-junkie.com/books/toc_pgaibe.html">Programming AI by
 * Example</a>. An excerpt:
 *
 * "<i>Finite state machines, or FSMs as they are usually referred to, have for
 * many years been the AI coder's instrument of choice to imbue a game agent with
 * the illusion of intelligence.
 *
 * ...
 *
 * Here are just some of the reasons why:
 *  - They are quick and simple to code.
 *  - They are easy to debug.
 *  - They have little computational overhead.
 *  - They are flexible.</i>" */
template <class owner_t> class StateMachine
{
public:
    /** Initializes the FSM, storing who owns it.
     *
     * @param o The object that owns this instance. */
    StateMachine(owner_t * o):
        current_state(NULL), previous_state(NULL), owner(o) {
        if(!owner) throw std::invalid_argument("State-machine must have non NULL owner.");
    }
    /** Destrutor. */
    virtual ~StateMachine() {
    }
    /**  Processes the actions of the FSM within the program's main loop. */
    virtual void update() {
        if(current_state) current_state->execute(owner);
    }
    /** Changes the FSM's current state.
     *
     * @param new_state the FSM's new state. */
    virtual void change_state(State<owner_t> *new_state) {
        if(!new_state) throw std::invalid_argument("State-machine cannot change to NULL state.");

        if(current_state) current_state->exit(owner);

        previous_state = current_state, current_state = new_state;

        current_state->enter(owner);
    }
public:
    /** The instance's current state. */
    State<owner_t> *current_state;
    /** The instance's previous state. */
    State<owner_t> *previous_state;
private:
    /** Object that owns the instance. */
    owner_t *owner;
};

#endif // STATEMACHINE_HPP