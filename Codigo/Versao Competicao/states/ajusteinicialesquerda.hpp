#ifndef ROBOTINOAJUSTEINICIALESQUERDA_HPP
#define ROBOTINOAJUSTEINICIALESQUERDA_HPP

#include "robotinostate.hpp"

class AjusteInicialEsquerda: public RobotinoState
{
public:
    /** Singleton. */
    static AjusteInicialEsquerda *instance();

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
    AjusteInicialEsquerda();
    ~AjusteInicialEsquerda();
};

#endif