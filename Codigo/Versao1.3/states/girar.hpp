#ifndef ROBOTINOGIRAR_HPP
#define ROBOTINOGIRAR_HPP

#include "robotinostate.hpp"

class Girar: public RobotinoState
{
public:
    /** Singleton. */
    static Girar *instance();

    /**
    * Called when entering the Girar state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Girar.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Girar state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Girar();
    ~Girar();
};

#endif