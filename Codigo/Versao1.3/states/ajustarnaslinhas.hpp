#ifndef AJUSTARNASLINHAS_HPP
#define AJUSTARNASLINHAS_HPP

#include "robotinostate.hpp"

class AjustarNasLinhas: public RobotinoState
{
public:
    /** Singleton. */
    static AjustarNasLinhas *instance();

    /**
    * Called when entering the AjustarNasLinhas state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AjustarNasLinhas.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AjustarNasLinhas state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AjustarNasLinhas();
    ~AjustarNasLinhas();
};

#endif