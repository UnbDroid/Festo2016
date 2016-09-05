#ifndef PROCURARCOR_HPP
#define PROCURARCOR_HPP

#include "robotinostate.hpp"

class ProcurarCor: public RobotinoState
{
public:
    /** Singleton. */
    static ProcurarCor *instance();

    /**
    * Called when entering the ProcurarCor state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to ProcurarCor.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the ProcurarCor state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    ProcurarCor();
    ~ProcurarCor();
};

#endif