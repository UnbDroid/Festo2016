#ifndef ROBOTINOTEST_HPP
#define ROBOTINOTEST_HPP

#include "robotinostate.hpp"

class AvoidanceControl: public RobotinoState
{
public:
    /** Singleton. */
    static AvoidanceControl *instance();

    /**
    * Called when entering the Test state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Test.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Test state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AvoidanceControl();
    ~AvoidanceControl();
};

#endif
