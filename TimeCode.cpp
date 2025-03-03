//Author: Harein Abeysekera
//Date: February 17th, 2025

#include <sstream>
#include <iomanip>
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

// Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    if (hr < 0 || min < 0 || sec < 0) {  // Checks for negative values
        throw invalid_argument("Negative arguments not allowed: " + to_string(hr) + ", " + to_string(min) + ", " + to_string(sec));
    }
    // Convert everything to seconds and store in t
    t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

// Set the hours
void TimeCode::SetHours(unsigned int hours) {
    //if (hours > 23) throw invalid_argument("Invalid hour");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);
}

// Set the minutes
void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes > 59) throw invalid_argument("Invalid minute");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

// Set the seconds
void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds > 59) throw invalid_argument("Invalid second");
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

// Reset TimeCode to 0
void TimeCode::reset() {
    t = 0;
}

//get hours by dividing by 3600 because there are 3600 seconds in an hour
unsigned int TimeCode::GetHours() const {
    return t / 3600;
}

//get minutes by dividing remainder got from hours by 60 because there are 60 mins in an hour
unsigned int TimeCode::GetMinutes() const {
    return (t % 3600) / 60;
}

//get seconds by getting the remainder of the seconds in a minute 
unsigned int TimeCode::GetSeconds() const {
    return t % 60;
}


// Get the time components (hours, minutes, seconds)
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = t / 3600;  
    min = (t % 3600) / 60;  
    sec = t % 60; 
}

// Convert time components to total seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec) {
    return (hr * 3600) + (min * 60) + sec;
}

// Convert TimeCode (hh:mm:ss) into a string 
string TimeCode::ToString() const {
    unsigned int hours, minutes, seconds;
    GetComponents(hours, minutes, seconds);
    return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}


// Overload addition operator
TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, this->t + other.t);
}

// Overload subtraction operator
TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (this->t < other.t) {
        throw invalid_argument("Cannot subtract larger time from smaller time");
    }
    return TimeCode(0, 0, this->t - other.t);
}

// Overload multiplication operator
TimeCode TimeCode::operator*(double a) const {
    return TimeCode(0, 0, static_cast<long long unsigned int>(t * a));
}

// Overload division operator
TimeCode TimeCode::operator/(double a) const{
    if (a==0){
        throw invalid_argument("Cannot divide by 0.");
    } else if(a < 0){
        throw invalid_argument("Cannot produce negative time....");
    }
    TimeCode divTime = TimeCode();
    divTime.t = t/a;
    return divTime;
}

// Comparison operators
bool TimeCode::operator==(const TimeCode& other) const {
    return t == other.t;
}

bool TimeCode::operator!=(const TimeCode& other) const {
    return t != other.t;
}

bool TimeCode::operator<(const TimeCode& other) const {
    return t < other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const {
    return t <= other.t;
}

bool TimeCode::operator>(const TimeCode& other) const {
    return t > other.t;
}

bool TimeCode::operator>=(const TimeCode& other) const {
    return t >= other.t;
}