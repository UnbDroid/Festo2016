#ifndef AJUSTARNASLINHASORTOGONAIS_HPP
#define AJUSTARNASLINHASORTOGONAIS_HPP

#include "robotinostate.hpp"

class AjustarNasLinhasOrtogonais: public RobotinoState
{
public:
    /** Singleton. */
    static AjustarNasLinhasOrtogonais *instance();

    /**
    * Called when entering the AjustarNasLinhasOrtogonais state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AjustarNasLinhasOrtogonais.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AjustarNasLinhasOrtogonais state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AjustarNasLinhasOrtogonais();
    ~AjustarNasLinhasOrtogonais();
};

#endif