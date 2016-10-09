#ifndef AJUSTARNASLINHASNAVEGANDO_HPP
#define AJUSTARNASLINHASNAVEGANDO_HPP

#include "robotinostate.hpp"

class AjustarNasLinhasNavegando: public RobotinoState
{
public:
    /** Singleton. */
    static AjustarNasLinhasNavegando *instance();

    /**
    * Called when entering the AjustarNasLinhasNavegando state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AjustarNasLinhasNavegando.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AjustarNasLinhasNavegando state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AjustarNasLinhasNavegando();
    ~AjustarNasLinhasNavegando();
};

#endif