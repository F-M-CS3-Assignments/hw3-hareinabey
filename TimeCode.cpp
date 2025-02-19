#include <sstream>
#include <iomanip>
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

// Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    // Convert everything to seconds and store in t
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

void TimeCode::SetHours(unsigned int hours)
{
}
