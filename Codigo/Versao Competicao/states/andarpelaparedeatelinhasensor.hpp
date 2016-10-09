#ifndef ANDARPELAPAREDEATELINHASENSOR_HPP
#define ANDARPELAPAREDEATELINHASENSOR_HPP

#include "robotinostate.hpp"

class AndarPelaParedeAteLinhaSensor: public RobotinoState
{
public:
    /** Singleton. */
    static AndarPelaParedeAteLinhaSensor *instance();

    /**
    * Called when entering the AndarPelaParedeAteLinhaSensor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AndarPelaParedeAteLinhaSensor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AndarPelaParedeAteLinhaSensor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AndarPelaParedeAteLinhaSensor();
    ~AndarPelaParedeAteLinhaSensor();
};

#endif