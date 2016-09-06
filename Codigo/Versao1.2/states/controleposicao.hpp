#ifndef ROBOTINOCONTROLARPOSICAO_HPP
#define ROBOTINOCONTROLARPOSICAO_HPP

#include "robotinostate.hpp"

class ControlarPosicao: public RobotinoState
{
public:
    /** Singleton. */
    static ControlarPosicao *instance();

    /**
    * Called when entering the ControlarPosicao state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to ControlarPosicao.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the ControlarPosicao state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    ControlarPosicao();
    ~ControlarPosicao();
};

#endif