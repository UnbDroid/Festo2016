#ifndef NAVEGARENTREAREAS2_HPP
#define NAVEGARENTREAREAS2_HPP

#include "robotinostate.hpp"

class NavegarEntreAreas2: public RobotinoState
{
public:
    /** Singleton. */
    static NavegarEntreAreas2 *instance();

    /**
    * Called when entering the NavegarEntreAreas2 state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to NavegarEntreAreas2.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the NavegarEntreAreas2 state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    NavegarEntreAreas2();
    ~NavegarEntreAreas2();
};

#endif