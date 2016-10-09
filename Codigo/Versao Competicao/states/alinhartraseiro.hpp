#ifndef ALINHARTRASEIRO_HPP
#define ALINHARTRASEIRO4_HPP

#include "robotinostate.hpp"

class AlinharTraseiro: public RobotinoState
{
public:
    /** Singleton. */
    static AlinharTraseiro *instance();

    /**
    * Called when entering the AlinharTraseiro state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AlinharTraseiro.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AlinharTraseiro state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AlinharTraseiro();
    ~AlinharTraseiro();
};

#endif