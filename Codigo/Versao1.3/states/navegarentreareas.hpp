#ifndef NAVEGARENTREAREAS_HPP
#define NAVEGARENTREAREAS_HPP

#include "robotinostate.hpp"

class NavegarEntreAreas: public RobotinoState
{
public:
    /** Singleton. */
    static NavegarEntreAreas *instance();

    /**
    * Called when entering the NavegarEntreAreas state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to NavegarEntreAreas.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the NavegarEntreAreas state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    NavegarEntreAreas();
    ~NavegarEntreAreas();
};

#endif