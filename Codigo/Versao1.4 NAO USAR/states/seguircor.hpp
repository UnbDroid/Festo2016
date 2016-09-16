#ifndef SEGUIRCOR_HPP
#define SEGUIRCOR_HPP

#include "robotinostate.hpp"


class SeguirCor: public RobotinoState
{
public:
    /** Singleton. */
    static SeguirCor *instance();

    /**
    * Called when entering the SeguirCor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to SeguirCor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the SeguirCor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    SeguirCor();
    ~SeguirCor();
};

#endif