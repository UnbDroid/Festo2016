#ifndef MODULO2_HPP
#define MODULO2_HPP

#include "robotinostate.hpp"

class Modulo2: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo2 *instance();

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
    Modulo2();
    ~Modulo2();
};

#endif
