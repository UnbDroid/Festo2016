#ifndef CONTARLINHAS_HPP
#define CONTARLINHAS_HPP

#include "robotinostate.hpp"

class ContarLinhas: public RobotinoState
{
public:
    /** Singleton. */
    static ContarLinhas *instance();

    /**
    * Called when entering the ContarLinhas state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to ContarLinhas.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the ContarLinhas state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    ContarLinhas();
    ~ContarLinhas();
};

#endif