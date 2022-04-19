#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <string>

using namespace std::chrono_literals;
using namespace std::chrono;
using std::vector;

class TimeManager
{
public:

    TimeManager();
    void stop();
    void start();
    void addTimes(vector<seconds> &&timeVector);
    void delTime(const seconds &dt);

private:
    std::unordered_map<long long,long long> times;
    void sleep();
    bool isRun;

};

#endif // TIMEMANAGER_H
