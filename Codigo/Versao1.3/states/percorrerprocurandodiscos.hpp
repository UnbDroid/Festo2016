#ifndef PERCORRERPROCURANDODISCOS_HPP
#define PERCORRERPROCURANDODISCOS_HPP

#include "robotinostate.hpp"

class PercorrerProcurandoDiscos: public RobotinoState
{
public:
    /** Singleton. */
    static PercorrerProcurandoDiscos *instance();

    /**
    * Called when entering the PercorrerProcurandoDiscos state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to PercorrerProcurandoDiscos.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the PercorrerProcurandoDiscos state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    PercorrerProcurandoDiscos();
    ~PercorrerProcurandoDiscos();
};

#endif