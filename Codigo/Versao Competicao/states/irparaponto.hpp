#ifndef ROBOTINOIRPARAPONTO_HPP
#define ROBOTINOIRPARAPONTO_HPP

#include "robotinostate.hpp"

class IrParaPonto: public RobotinoState
{
public:
    /** Singleton. */
    static IrParaPonto *instance();

    /**
    * Called when entering the IrParaPonto state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParaPonto.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParaPonto state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrParaPonto();
    ~IrParaPonto();
};

#endif
