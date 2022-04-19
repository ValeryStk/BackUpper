#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <string>

class TimeManager
{
public:

    TimeManager();
    void stop();
    void start();
    void addTimes(std::vector<std::chrono::seconds> &&timeVector);
    void delTime(std::chrono::seconds dt);

private:
    std::unordered_map<long long,long long> times;
    void sleep();
    bool isRun;

};

#endif // TIMEMANAGER_H
