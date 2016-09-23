#ifndef ACHARLINHAS_HPP
#define ACHARLINHAS_HPP

#include "robotinostate.hpp"

class AcharLinhas: public RobotinoState
{
public:
    /** Singleton. */
    static AcharLinhas *instance();

    /**
    * Called when entering the AcharLinhas state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AcharLinhas.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AcharLinhas state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AcharLinhas();
    ~AcharLinhas();
};

#endif