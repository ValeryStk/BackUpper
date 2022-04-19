#include "TimeManager.h"
#include "TimeManager.h"
#include <iostream>
using std::cout;
using std::endl;



TimeManager::TimeManager()
{


    times = {
        {seconds(1min).count(),seconds(1min).count()},
        {seconds(7s).count(),  seconds(7s).count()},
        {seconds(3min).count(),seconds(3min).count()},
        {seconds(25s).count(),seconds(25s).count()},
        {seconds(1min + 20s).count(),seconds(1min + 20s).count()}
    };
    vector<seconds> vt = {5s, 2h, 30min,3h+30min};
    addTimes(std::move(vt));
    cout<<"Time manager"<<endl;
    delTime(seconds(7s));
    delTime(seconds(5s));

}

void TimeManager::sleep()
{

    while(isRun){

        long long nearestTime = times.begin()->first;
        for(auto &it:times){
            if(nearestTime > it.second) nearestTime = it.second;
        }
        cout << "Nearest time:" << nearestTime <<endl;
        std::this_thread::sleep_for(seconds(nearestTime));

        for(auto &it:times){
            times[it.first] = it.second - nearestTime;
            if(it.second == 0){
                cout << "***** Timer "<<it.first<<" seconds triggered"<<endl;
                times[it.first] = it.first;
            }
        }
        cout << "--------------------------------------------\n"<<endl;
        for(auto &it:times)cout << "Changed state for timer "<<it.first<<" -->"<<it.second<<endl;
    }
}


void TimeManager::stop()
{
    isRun = false;
}

void TimeManager::start()
{
    if(times.size() == 0){
        cout << "No times case: ";
        return;
    }
    isRun = true;
    sleep();
}

void TimeManager::addTimes(std::vector<seconds> &&timeVector)
{
    for(auto&&it:timeVector){
        auto timeValue = std::pair<long long,long long>(seconds(it).count(),seconds(it).count());
        times.insert(timeValue);
        cout << "Time value:"<<timeValue.second<<endl;
    }
}


void TimeManager::delTime(const seconds &dt)
{
    auto it = times.find(dt.count());
    if(it != times.end())times.erase(it);
}
