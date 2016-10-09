#ifndef ANDARPELAPAREDEATELINHA_HPP
#define ANDARPELAPAREDEATELINHA_HPP

#include "robotinostate.hpp"

class AndarPelaParedeAteLinha: public RobotinoState
{
public:
    /** Singleton. */
    static AndarPelaParedeAteLinha *instance();

    /**
    * Called when entering the AndarPelaParedeAteLinha state.
    *
    * @param bigbob the robot that is moving to it's goal'.
    */
    void enter(Robotino *robotino);

    /**
     *
     * @param bigbob the robot to AndarPelaParedeAteLinha.
     */
    void execute(Robotino *robotino);

    /**
     * Called when leaving the AndarPelaParedeAteLinha state.
     *
     * @param bigbob the robot that is moving to it's goal.
     */
    void exit(Robotino *robotino);
private:
    AndarPelaParedeAteLinha();
    ~AndarPelaParedeAteLinha();
};

#endif