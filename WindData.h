#ifndef WIND_DATA_H
#define WIND_DATA_H

#include "../Date.h"
#include "../Time.h"

/**
 * @class WindData
 * @brief Represents wind data including date, time, wind speed, air temperature, and solar radiation
 * This class is used for:
 * - Storing and managing wind data records
 * - Providing access to individual data components (date, time, wind speed, etc.)
 * - Overloading comparison operators for sorting and comparison purposes
 * @author Siyeshen Govender
 *
 * @version 3.0
 *
 */
class WindData {
public:

    /**
     * @brief Default constructor that initializes WindData object with default values
     */
    WindData();

    /**
     * @brief Parameterized constructor to initialize WindData with specific values
     * @param date The date component of the wind data
     * @param time The time component of the wind data
     * @param windSpeed The wind speed measurement
     * @param airTemp The air temperature measurement
     * @param solarRad The solar radiation measurement
     */
    WindData(const Date& date, const Time& time, float windSpeed, float airTemp, float solarRad);

    /**
     * @brief Copy constructor for WindData
     * @param other The WindData object to copy from
     */
    WindData(const WindData& other);

    /**
     * @brief Destructor for WindData
     */
    ~WindData();

    /**
     * @brief Assignment operator for WindData
     * @param other The WindData object to assign from
     * @return Reference to the updated WindData object
     */
    WindData& operator=(const WindData& other);

    // Getters
    /**
     * @brief Gets the date component of the wind data
     * @return The date as a Date object
     */
    const Date& getDate() const;

    /**
     * @brief Gets the time component of the wind data
     * @return The time as a Time object
     */
    const Time& getTime() const;

    /**
     * @brief Gets the wind speed measurement
     * @return The wind speed as a float
     */
    float getWindSpeed() const;

    /**
     * @brief Gets the air temperature measurement
     * @return The air temperature as a float
     */
    float getAirTemp() const;

    /**
     * @brief Gets the solar radiation measurement
     * @return The solar radiation as a float
     */
    float getSolarRad() const;

    // Setters
    /**
     * @brief Sets the date component of the wind data
     * @param date The date as a Date object
     */
    void setDate(const Date& date);

    /**
     * @brief Sets the time component of the wind data
     * @param time The time as a Time object
     */
    void setTime(const Time& time);

    /**
     * @brief Sets the wind speed measurement
     * @param windSpeed The wind speed as a float
     */
    void setWindSpeed(float windSpeed);

    /**
     * @brief Sets the air temperature measurement
     * @param airTemp The air temperature as a float
     */
    void setAirTemp(float airTemp);

    /**
     * @brief Sets the solar radiation measurement
     * @param solarRad The solar radiation as a float
     */
    void setSolarRad(float solarRad);

    /**
     * @brief Overloads the equality operator for WindData objects
     * @param other The WindData object to compare with
     * @return True if the objects are equal, false otherwise
     */
    bool operator == (const WindData& other) const;

    /**
     * @brief Overloads the less-than operator for WindData objects
     * @param other The WindData object to compare with
     * @return True if this object is less than the other, false otherwise
     */
    bool operator < (const WindData& other) const;

    /**
     * @brief Overloads the greater-than operator for WindData objects
     * @param other The WindData object to compare with
     * @return True if this object is greater than the other, false otherwise
     */
    bool operator > (const WindData& other) const;

private:
    Date d; ///< The date object component of the WindData
    Time t; ///< The time object component of the WindData
    float windSpeed; ///< The wind speed component of the WindData
    float airTemp; ///< The air temperature component of the WindData
    float solarRad; ///< The solar radiation component of the WindData

};

#endif // WIND_DATA_H
