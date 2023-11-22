#include "Time.h"

// Default constructor initializes the time to 00:00
Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

bool Time::setMinute(const unsigned short m){

    if(isValidMinute(m)){
        m_minute = m;
        return true;
    }

    return false;
}

bool Time::setHour(const unsigned short h){

    if(isValidHour(h)){
        m_hour = h;
        return true;
    }

    return false;
}


//_____Validation Methods________________________________________________
bool Time::isValidMinute(const unsigned short m)
{
    if (m >= 0 && m <= 59) {
        return true;
    }
    return false;
}

bool Time::isValidHour(const unsigned short h)
{
    if (h >= 0 && h <= 23) {
        return true;
    }
    return false;
}




//____Overloaded Operators______________________________________

// Overloaded input stream operator for reading Time objects
std::istream & operator >>( std::istream & input, Time & T )
{
    unsigned h; // Temporary variable to store the hour
    unsigned m; // Temporary variable to store the minute

    input >> h; // Read the hour part
    input.ignore(1); // Ignore the delimiter

    // Check if the next character is '0' and ignore it if so
    if(input.peek() == '0')
        input.ignore(1);

    input >> m; // Read the minute part
    input.ignore(1);

    T.setHour(h); // Set the hour in the Time object
    T.setMinute(m); // Set the minute in the Time object

    return input;
}

// Overloaded output stream operator for printing Time objects
std::ostream & operator <<( std::ostream & os, const Time & T )
{
    os << "  Time:  " << T.getHour() << ':'; // Print the hour part and the delimiter

    // Check if the minute part is less than 10, and prepend a '0' if so
    if(T.getMinute() < 10){
        os << '0' << T.getMinute() << '\n';
    }else{
        os << T.getMinute() << '\n';
    }

    return os; // Return the output stream
}
