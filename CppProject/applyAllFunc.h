#pragma once
#include <iostream>
using namespace std;
template<class T, class Func>
void ApplyAll(T& ds, const Func& f)
{
    for (auto itr = ds.begin(); itr != ds.end(); ++itr)
    {
        //the function gets an instance "ds" and applies a funtion "f" (or an insance of a function) runs "f" on "ds"
        //we assume that "ds" is a Data Structure that supports this function\ instance "f";
        f(*itr);
    }
}