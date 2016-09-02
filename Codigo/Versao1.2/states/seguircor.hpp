#ifndef ROBOTINOBASE_HPP
#define ROBOTINOBASE_HPP

#include "robotinostate.hpp"

class Base: public RobotinoState
{
public:
    /** Singleton. */
    static Base *instance();

    /**
    * Called when entering the Base state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Base.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Base state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Base();
    ~Base();
};

#endif