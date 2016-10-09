#ifndef MODULO3_HPP
#define MODULO3_HPP

#include "robotinostate.hpp"

class Modulo3: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo3 *instance();

    /**
    * Called when entering the Modulo3 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo3.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo3 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo3();
    ~Modulo3();
};

#endif