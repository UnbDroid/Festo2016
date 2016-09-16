#ifndef IDENTIFICARCOR_HPP
#define IDENTIFICARCOR_HPP

#include "robotinostate.hpp"

class IdentificarCor: public RobotinoState
{
public:
    /** Singleton. */
    static IdentificarCor *instance();

    /**
    * Called when entering the IdentificarCor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IdentificarCor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IdentificarCor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IdentificarCor();
    ~IdentificarCor();
};

#endif