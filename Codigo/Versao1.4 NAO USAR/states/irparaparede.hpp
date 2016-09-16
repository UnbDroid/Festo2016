#ifndef IRPARAPAREDE_HPP
#define IRPARAPAREDE_HPP

#include "robotinostate.hpp"

class IrParaParede: public RobotinoState
{
public:
    /** Singleton. */
    static IrParaParede *instance();

    /**
    * Called when entering the IrParaParede state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParaParede.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParaParede state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrParaParede();
    ~IrParaParede();
};

#endif