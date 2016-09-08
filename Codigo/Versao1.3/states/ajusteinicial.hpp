#ifndef ROBOTINOAJUSTEINICIAL_HPP
#define ROBOTINOAJUSTEINICIAL_HPP

#include "robotinostate.hpp"

class AjusteInicial: public RobotinoState
{
public:
    /** Singleton. */
    static AjusteInicial *instance();

    /**
    * Called when entering the AjusteInicial state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AjusteInicial.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AjusteInicial state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AjusteInicial();
    ~AjusteInicial();
};

#endif