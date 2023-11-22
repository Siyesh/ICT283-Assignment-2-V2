#ifndef DATE_H
#define DATE_H

#include <string.h>
#include <iostream>

/**
 * @class Date
 * @brief Represents a date in day, month, and year
 * Can be used to:
 * - Store a date
 * - Validate a date
 * - Set and get the day, month, and year components of a date
 * - Determine if a year is a leap year
 * @author Siyeshen Govender 34443324
 *
 * @version 4.2
 *
 * @date 10-10-2023, Initial implementation
 * @date 11-10-2023, Added leap year functionality
 * @date 12-10-2023, Added validation for day, month, and year
 * @date 13-10-2023, Improved input/output stream operators
 * @date 06-11-2023, Added overloaded operators >, < and == for date value comparisons
 *
 */
class Date
{
    public:
        /**
         * @brief Default constructor that initializes Date object
         */
        Date();

        ///< in a string format all the 12 months
        static const std::string monthAry[12];

        /**
         * @brief Gets the day component of the date
         * @return The day as an unsigned integer
         */
        unsigned short getDay()const{return m_day;}

        /**
         * @brief Gets the month component of the date
         * @return The month as an unsigned integer
         */
        unsigned short getMonth()const{return m_month;}

        /**
         * @brief Gets the year component of the date
         * @return The year as an unsigned integer
         */
        unsigned short getYear()const{return m_year;}

        /**
         * @brief Sets the day component of the date
         * @param d The day as an unsigned integer
         */
        bool setDay(const unsigned short d);

        /**
         * @brief Sets the month component of the date
         * @param m The month as an unsigned integer
         */
        bool setMonth(const unsigned short m);

        /**
         * @brief Sets the year component of the date
         * @param y The year as an unsigned integer
         */
        bool setYear(const unsigned short y);

        bool isValidDay(unsigned short d);
        bool isValidMonth(unsigned short m);
        bool isValidYear(unsigned short y);

        bool isValidDate(unsigned short d, unsigned short m, unsigned short y);

        bool isLeapYear(unsigned short y);

    private:
        unsigned short m_day; ///< The day component of the date
        unsigned short m_month; ///< The month component of the date
        unsigned short m_year; ///< The year component of the date
};

/**
 * @brief Overloads the input stream operator for Date objects
 * @param input The input stream
 * @param D The Date object to store the input
 * @return The updated input stream
 */
std::istream & operator >>( std::istream &input, Date &D );

/**
 * @brief Overloads the output stream operator for Date objects
 * @param os The output stream
 * @param D The Date object
 * @return The updated output stream
 */
std::ostream & operator <<( std::ostream &os, const Date &D );

bool operator > (const Date &A, const Date &B);


bool operator < (const Date &A, const Date &B);


bool operator == (const Date &A, const Date &B);

#endif // DATE_H
