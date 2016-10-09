#ifndef SEGUINDOPAREDE_HPP
#define SEGUINDOPAREDE_HPP

#include "robotinostate.hpp"

class SeguindoParede: public RobotinoState
{
public:
    /** Singleton. */
    static SeguindoParede *instance();

    /**
    * Called when entering the SeguindoParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to SeguindoParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the SeguindoParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    SeguindoParede();
    ~SeguindoParede();
};

#endif