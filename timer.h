#ifndef TIMER_H
#define TIMER_H
#include <sys/timeb.h>

using namespace std;
class Timer
{
public:
    Timer();
    double getDeltaTime();
    void update();
private:
    int pre_time = 0;
    double deltaTime = 0.1;
    int getMiliseconds();
};

#endif // TIMER_H