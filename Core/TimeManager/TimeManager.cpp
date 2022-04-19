#include "TimeManager.h"
#include <iostream>

using namespace std::chrono_literals;

TimeManager::TimeManager()
{


    times = {
        {std::chrono::seconds(1min).count(),std::chrono::seconds(1min).count()},
        {std::chrono::seconds(7s).count(),std::chrono::seconds(7s).count()},
        {std::chrono::seconds(3min).count(),std::chrono::seconds(3min).count()},
        {std::chrono::seconds(25s).count(),std::chrono::seconds(25s).count()},
        {std::chrono::seconds(1min + 20s).count(),std::chrono::seconds(1min + 20s).count()}
    };
    std::vector<std::chrono::seconds> vt = {5s, 2h, 30min,3h+30min};
    addTimes(std::move(vt));
    std::cout<<"Time manager";
    delTime(std::chrono::seconds(7s));
    delTime(std::chrono::seconds(5s));

}

void TimeManager::sleep()
{

    while(isRun){

        long long nearestTime = times.begin()->first;
        for(auto it:times){
            if(nearestTime > it.second) nearestTime = it.second;
        }
        std::cout << "Nearest time:" << nearestTime;
        std::this_thread::sleep_for(std::chrono::seconds(nearestTime));

        for(auto &it:times){
            times[it.first] = it.second - nearestTime;
            if(it.second == 0){
                std::cout << "***** Timer "<<it.first<<" seconds triggered";
                times[it.first] = it.first;
            }
        }
        std::cout << "--------------------------------------------\n";
        for(auto it:times)std::cout << "Changed state for timer "<<it.first<<" -->"<<it.second;
    }
}


void TimeManager::stop()
{
    isRun = false;
}

void TimeManager::start()
{
    if(times.size()==0){
        std::cout << "No times case: ";
        return;}
    isRun = true;
    sleep();
}

void TimeManager::addTimes(std::vector<std::chrono::seconds> &&timeVector)
{
    for(auto&&it:timeVector){
        auto timeValue = std::pair<long long,long long>(std::chrono::seconds(it).count(),std::chrono::seconds(it).count());
        times.insert(timeValue);
        std::cout << "Time value:"<<timeValue.second;
    }
}

void TimeManager::delTime(std::chrono::seconds dt)
{
    auto it = times.find(dt.count());
    if(it != times.end())times.erase(it);
}
