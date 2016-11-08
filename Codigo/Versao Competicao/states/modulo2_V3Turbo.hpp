#ifndef MODULO2V3TURBO_HPP
#define MODULO2V3TURBO_HPP

#include "robotinostate.hpp"

class Modulo2_V3Turbo: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo2_V3Turbo *instance();

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
    Modulo2_V3Turbo();
    ~Modulo2_V3Turbo();
};

#endif
