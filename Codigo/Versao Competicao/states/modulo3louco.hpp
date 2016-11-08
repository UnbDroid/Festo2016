#ifndef MODULO3LOUCO_HPP
#define MODULO3LOUCO_HPP

#include "robotinostate.hpp"

class Modulo3Louco: public RobotinoState
{
public:
    /** Singleton. */
    static Modulo3Louco *instance();

    /**
    * Called when entering the Modulo3Louco state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to Modulo3Louco.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the Modulo3Louco state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    Modulo3Louco();
    ~Modulo3Louco();
};

#endif