#ifndef TIME_H
#define TIME_H

#include <iostream>


/**
 * @class Time
 * @brief Represents time in hours and minutes
 * Can be used to:
 * - Store a time
 * - Validate the hour and minute components of a time
 * - Set and get the hour and minute components of a time
 * @author Siyeshen Govender 34443324
 *
 * @version 3.6
 *
 * @date 1-10-2023, Initial implementation
 * @date 8-10-2023, Added validation for hours and minutes
 * @date 9-10-2023, Optimized getter methods
 */
class Time
{
    public:
        /**
         * @brief Default constructor that initializes Time object
         */
        Time();

        /**
         * @brief Gets the hour component of the time
         * @return The hour as an unsigned integer
         */
        unsigned short getHour() const{return m_hour;}

        /**
         * @brief Gets the minute component of the time
         * @return The minute as an unsigned integer
         */
        unsigned short getMinute() const{return m_minute;}

        /**
         * @brief Sets the hour component of the time
         * @param h The hour as an unsigned short
         */
        bool setHour (const unsigned short h);

        /**
         * @brief Sets the minute component of the time
         * @param m The minute as an unsigned short
         */
        bool setMinute (const unsigned short m);

        /**
        * @brief Validates the hour component of the time
        * @param h The hour as an unsigned short
        * @return True if the hour is valid, false otherwise
        */
        bool isValidHour (const unsigned short h);

        /**
        * @brief Validates the minute component of the time
        * @param m The minute as an unsigned short
        * @return True if the minute is valid, false otherwise
        */
        bool isValidMinute (const unsigned short m);

    private:
        unsigned m_hour; ///< The hour component of the time
        unsigned m_minute; ///< The minute component of the time
};

/**
 * @brief Overloads the input stream operator for Time objects
 * @param input The input stream
 * @param T The Time object to store the input
 * @return The updated input stream
 */
std::istream & operator >>( std::istream & input, Time & T );

/**
 * @brief Overloads the output stream operator for Time objects
 * @param os The output stream
 * @param T The Time object
 * @return The updated output stream
 */
std::ostream & operator <<( std::ostream & os, const Time & T );



#endif // TIME_H
