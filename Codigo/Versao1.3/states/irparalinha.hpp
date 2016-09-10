#ifndef ROBOTINOBASE_HPP
#define ROBOTINOBASE_HPP

#include "robotinostate.hpp"

class IrParaLinha: public RobotinoState
{
public:
    /** Singleton. */
    static IrParaLinha *instance();

    /**
    * Called when entering the IrParaLinha state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParaLinha.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParaLinha state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrParaLinha();
    ~IrParaLinha();
};

#endif