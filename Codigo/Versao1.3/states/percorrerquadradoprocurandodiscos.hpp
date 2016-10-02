#ifndef PERCORRERQUADRADOPROCURANDODISCOS_HPP
#define PERCORRERQUADRADOPROCURANDODISCOS_HPP

#include "robotinostate.hpp"

class PercorrerQuadradoProcurandoDiscos: public RobotinoState
{
public:
    /** Singleton. */
    static PercorrerQuadradoProcurandoDiscos *instance();

    /**
    * Called when entering the PercorrerQuadradoProcurandoDiscos state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to PercorrerQuadradoProcurandoDiscos.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the PercorrerQuadradoProcurandoDiscos state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    PercorrerQuadradoProcurandoDiscos();
    ~PercorrerQuadradoProcurandoDiscos();
};

#endif