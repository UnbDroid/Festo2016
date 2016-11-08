#ifndef MODULO3TESTAR_HPP
#define MODULO3TESTAR_HPP

#include "robotinostate.hpp"

class Modulo3Testar: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo3Testar *instance();

    /**
    * Called when entering the Modulo3Testar state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo3Testar.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo3Testar state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo3Testar();
    ~Modulo3Testar();
};

#endif