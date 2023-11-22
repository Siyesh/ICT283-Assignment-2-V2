#include "Date.h"

// Default constructor initializes all member variables to 1
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 1;
}

const std::string Date::monthAry[12] ={
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

bool Date::setDay(const unsigned short d)
{
    if (isValidDay(d)) {
        m_day = d;
        return true;
    }
    return false;
}


bool Date::setMonth(const unsigned short m)
{
        if (isValidMonth(m)) {
        m_month = m;
        return true;
    }
    return false;
}

bool Date::setYear(const unsigned short y)
{
    if (isValidYear(y)) {
        m_year = y;
        return true;
    }
    return false;
}

//____Validation Methods Below:________________________________________________________________________________________

bool Date::isValidDay(unsigned short d)
{
    if (d >= 1 && d <= 31) {
        return true;
    }
    return false;
}

bool Date::isValidMonth(unsigned short m)
{
    if (m >= 1 && m <= 12) {
        return true;
    }
    return false;
}


bool Date::isValidYear(unsigned short y)
{
    if (y >= 1800 && y <= 2999) {
        return true;
    }
    return false;
}


bool Date::isValidDate(unsigned short d, unsigned short m, unsigned short y)
{
    if (!isValidDay(d) || !isValidMonth(m) || !isValidYear(y)) {
        return false;
    }

    if (m == 2) {
        if (isLeapYear(y)) {
            if (d > 29) {
                return false;
            }
        } else {
            if (d > 28) {
                return false;
            }
        }
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (d > 30) {
            return false;
        }
    }

    return true;
}

bool Date::isLeapYear(unsigned short y)
{
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        return true;
    }
    return false;
}


//________Overloaded Input and Output Stream_____________________________________________________________________________________________________________

// Overloaded input stream operator for reading Date objects
std::istream & operator >>( std::istream & input, Date & D )
{
    //i could loop it but readibility is simpler this way for me

    unsigned d;
    unsigned m;
    unsigned y;

    // Ignore leading zero if present
    if(input.peek() == '0')
        input.ignore(1);

     // Read day
    input >> d;
    input.ignore(1); // Ignore delimiter

    // Ignore leading zero if present
    if(input.peek() == '0')
        input.ignore(1);

    // Read month
    input >> m;
    input.ignore(1); //Ignore delimiter

    //Read year
    input >> y;

    // Set the read values to the Date object
    D.setDay(d);
    D.setMonth(m);
    D.setYear(y);

    return input; // Return the input stream
}

// Overloaded output stream operator for printing Date objects
std::ostream & operator <<( std::ostream & os, const Date & D )
{
    // Print the date in the format "Date: day month year"
    os << "  Date:  " << D.getDay() << ' ' << D.getMonth() << ' ' << D.getYear() << '\n';

    return os; // Return the output stream

};


//________Overloaded Operators for BST Comparison:__________________

bool operator > (const Date &A, const Date &B) {
    return A.getYear() > B.getYear() ||
           (A.getYear() == B.getYear() && A.getMonth() > B.getMonth()) ||
           (A.getYear() == B.getYear() && A.getMonth() == B.getMonth() && A.getDay() > B.getDay());
}

bool operator < (const Date &A, const Date &B) {
    return A.getYear() < B.getYear() ||
           (A.getYear() == B.getYear() && A.getMonth() < B.getMonth()) ||
           (A.getYear() == B.getYear() && A.getMonth() == B.getMonth() && A.getDay() < B.getDay());
}


bool operator == (const Date &A, const Date &B) {
    return A.getYear() == B.getYear() &&
           A.getMonth() == B.getMonth() &&
           A.getDay() == B.getDay();
}



