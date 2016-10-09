#ifndef IRPARADEPELAPAREDEPROCURANDODISCO_HPP
#define IRPAREDEPELAPAREDEPROCURANDODISCO_HPP

#include "robotinostate.hpp"

class IrParedePelaParedeProcurandoDisco: public RobotinoState
{
public:
    /** Singleton. */
    static IrParedePelaParedeProcurandoDisco *instance();

    /**
    * Called when entering the IrParedePelaParedeProcurandoDisco state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to IrParedePelaParedeProcurandoDisco.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the IrParedePelaParedeProcurandoDisco state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    IrParedePelaParedeProcurandoDisco();
    ~IrParedePelaParedeProcurandoDisco();
};

#endif