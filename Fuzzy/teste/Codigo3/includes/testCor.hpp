#ifndef ROBOTINOTESTCOR_HPP
#define ROBOTINOTESTCOR_HPP

#include "robotinostate.hpp"

class TestCor: public RobotinoState
{
public:
    /** Singleton. */
    static TestCor *instance();

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
    TestCor();
    ~TestCor();
};

#endif
