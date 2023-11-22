#include "WindData.h"

// Default constructor
WindData::WindData()
    : d(), t(), windSpeed(0.0f), airTemp(0.0f), solarRad(0.0f) {
}

// Parameterized constructor
WindData::WindData(const Date& date, const Time& time, float windSpeed, float airTemp, float solarRad)
    : d(date), t(time), windSpeed(windSpeed), airTemp(airTemp), solarRad(solarRad) {
}

// Copy constructor
WindData::WindData(const WindData& other)
    : d(other.d), t(other.t), windSpeed(other.windSpeed), airTemp(other.airTemp), solarRad(other.solarRad) {
}

// Assignment operator
WindData& WindData::operator=(const WindData& other) {
    if (this != &other) {
        d = other.d;
        t = other.t;
        windSpeed = other.windSpeed;
        airTemp = other.airTemp;
        solarRad = other.solarRad;
    }
    return *this;
}

// Destructor
WindData::~WindData() {
    //body
}

// Getters
const Date& WindData::getDate() const {
    return d;
}

const Time& WindData::getTime() const {
    return t;
}

float WindData::getWindSpeed() const {
    return windSpeed;
}

float WindData::getAirTemp() const {
    return airTemp;
}

float WindData::getSolarRad() const {
    return solarRad;
}

// Setters
void WindData::setDate(const Date& date) {
    d = date;
}

void WindData::setTime(const Time& time) {
    t = time;
}

void WindData::setWindSpeed(float ws) {
    windSpeed = ws;
}

void WindData::setAirTemp(float at) {
    airTemp = at;
}

void WindData::setSolarRad(float sr) {
    solarRad = sr;
}

bool WindData::operator==(const WindData& other) const {
    return this->d == other.d;
}

bool WindData::operator<(const WindData& other) const {
    return this->d < other.d;
}

bool WindData::operator>(const WindData& other) const {
    return this->d > other.d;
}
