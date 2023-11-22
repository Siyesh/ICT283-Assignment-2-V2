#include "Vector.h"
#include "Date.h"
#include "Time.h"
#include "BST.h"
#include "WindData.h"


#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include <limits>
#include <iomanip> // for std::fixed and std::setprecision. Allows for 2 decimal places for the sPCC
//#include <cstdlib>

#include <map>


/*typedef struct
{
    Date d;
    Time t;
    float windSpeed;
    float airTemp;
    float solarRad;
}WindRecType;
*/

float readFile(const std::string& fileName, std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
void Menu(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
void Options();

void avgSpeedAndSSD(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
float calculateSSD(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float average);

float calculateAirTempSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month, float &tempSum, Vector<float> &airTemps);

void avgAirTempAndSSD(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
void totalSolarRad(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
void writeFile(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);

int promptYear();
int promptMonth();
bool isValidInputType(unsigned short int &input);

float calculateWindSpeedandAirTempSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month, float &speedSum, float &tempSum, Vector<float> &windSpeeds);

float calculateSolarRadSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month);
void printAvgWindSpeedAndAirTemp(float speed, float temp, float total);
void printSolarRadTotalMonth(float solarSum);

float average(float sum, float total);
float speedMetersPerSecToKmPerHour(const float metre);
float wattsToKiloWatts(const float watts);

double calculateSPCC(const Vector<double>& x, const Vector<double>& y);
void calculateSPCCForMonth(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map);
void extractMonthData(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, unsigned short int month, Vector<double>& windSpeeds, Vector<double>& airTemps, Vector<double>& solarRads);

int main()
{
    std::map <int, BST<WindData> > year_map, month_map;


//    std::map<std::pair<int, int>, Vector<WindRecType>> monthlyDataMap;

    std::ifstream dataSource("data/data_source.txt");

    if (!dataSource.is_open()) {
        std::cout << "data_source.txt file is not found";
        return 1;
    }

    // Check if the file is empty
    if (dataSource.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "File is empty, nothing to read.";
        return 1;
    }

    //Vector<WindRecType> WindDataVec;

    std::string line;

    while (std::getline(dataSource, line)) {
        std::string fileName = "data/" + line;
        readFile(fileName, month_map, year_map);
    }

    Menu(month_map, year_map);

    return 0;
}





float readFile(const std::string& fileName, std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    // Declare a windData variable to hold each record for the WindData object
    WindData windData;

    // Declare a string to hold each header name
    std::string header;

    // Open the file with the given filename
    std::ifstream infile(fileName.c_str());

    // Check if the file was successfully opened
    if(!infile) {
        std::cout << fileName << " not found\n";
        //exit(1);  // Exit the program if the file was not found
    };

    // Declare a string to hold each line from the file
    std::string line;

    // Read the first line from the file (the header line)
    getline(infile, line);

    // Create a stringstream from the line to easily parse it
    std::stringstream ss(line);

    // Initialize a counter to keep track of the column index
    int c = 0;

    // Declare an array of the headers we're interested in: the "time and date", "Air Temp", "wind speed", "Solar radiation"
    std::string headers[4] = {"WAST", "T", "S", "SR"};

    // Declare an array to hold the positions of the headers
    int pos[4] = {0};

    // Loop through each header in the line
    while (getline(ss, header, ',')) {
     //   std::cout << header << " " << c << "\n";

        // Check if the header is one we're interested in, and if so, store its position
        for (int i = 0; i < 4; i++)
            if (header == headers[i])
                pos[i] = c;

        // Increment the column index counter
        c++;
    }

    // Print out the positions of the headers we're interested in
  //  for (int i = 0; i < 4; i++){
   //     std::cout << pos[i] << " ";
   // }

    // Ignore the rest of the first line
   // infile.ignore(1000, '\n');

while (!infile.eof()) {
    int c = 0;
    getline(infile, line);
    std::stringstream ss(line);
    std::string value;

    WindData windData; //  instance of WindData
    while (getline(ss, value, ',')) {
        std::stringstream vs(value);
        for (int i = 0; i < 4; i++) {
            if (pos[i] == c) {
                switch (i) {
                    case 0: {
                        Date date;
                        Time time;
                        vs >> date >> time;
                        windData.setDate(date);
                        windData.setTime(time);
                        break;
                    }
                    case 1: {
                        float airTemp;
                        vs >> airTemp;
                        windData.setAirTemp(airTemp);
                        break;
                    }
                    case 2: {
                        float windSpeed;
                        vs >> windSpeed;
                        windSpeed = speedMetersPerSecToKmPerHour(windSpeed);
                        windData.setWindSpeed(windSpeed);
                        break;
                    }
                    case 3: {
                        float solarRad;
                        vs >> solarRad;
                        solarRad = wattsToKiloWatts(solarRad);
                        windData.setSolarRad(solarRad);
                        break;
                    }
                    default:
                        break;
                }
            }
            c++;
        }

        // Extract month and year using the getDate() method
        int year = windData.getDate().getYear();
        int month = windData.getDate().getMonth();

        month_map[month].insert(windData);
        year_map[year].insert(windData);
    }
}

}
    // Remove the last record, which is likely incomplete or duplicated
    //WindDataVec.popBack();


void Menu(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    char choice;
    Options();
    do{
        std::cout << '\n' << "Enter an option:" << std::endl;
        std::cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
            case 'A':
                avgSpeedAndSSD(month_map, year_map);
                break;

            case 'B':
                avgAirTempAndSSD(month_map, year_map);
                break;

            case 'C':
                calculateSPCCForMonth(month_map, year_map);
                break;

            case 'D':
                writeFile(month_map, year_map);
                break;

            case 'E':
                break;

            default:
                std::cout << "Invalid character entered" << std::endl;
                break;
        }
    }while(choice != 'E');
}

void Options()
{
    std::cout << "A - average wind speed and sample standard deviation for this wind speed given specified month and year." << std::endl;
    std::cout << "B - average average ambient air temperature and sample standard deviation for each month of a specified year" << std::endl;
    std::cout << "C - sPCC calculation is carried out for a user specified month and combinations of two data field, used to be solarRad" << std::endl;
    std::cout << "D - Write the average wind speed and its sample standard deviation , average ambient air temperature and its sample standard deviation, and total solar radiation for each month of a specified year" << std::endl;
    std::cout << "E - Exit program" << std::endl;
}


void avgSpeedAndSSD(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    WindData windData;

    unsigned short int yearInput = promptYear();
    unsigned short int monthInput = promptMonth();
    float speedSum = 0;
    float tempSum = 0;
    float total = 0;
    Vector<float> windSpeeds; // To store individual wind speeds for standard deviation calculation

    // Calculate the sum of wind speeds and temperatures
    total = calculateWindSpeedandAirTempSum(WindDataVec, yearInput, monthInput, speedSum, tempSum, windSpeeds);

    // Calculate the average wind speed
    float avgSpeed = average(speedSum, total);

    // Calculate the standard deviation for wind speed
    float stdDevSpeed = calculateSSD(windSpeeds, avgSpeed);

    std::cout << WindData.d.monthAry[monthInput - 1] << ' ' << yearInput << ": ";
    std::cout << "average Wind Speed: " << avgSpeed << " km/h, ";
    std::cout << "Standard Deviation: " << stdDevSpeed << " km/h" << std::endl;
}

float calculateSSD(const Vector<float> &vec, float average) {
    float sum_value = 0;
    int N = vec.getSize(); // Get the size of the vector

    for (int i = 0; i < N; ++i) {
        float value = vec[i]; // Get the i-th element from vec
        sum_value += pow(value - average, 2); // Calculate the squared difference from the mean
    }

    return sqrt(sum_value / (N - 1)); // Calculate the standard deviation
}


void avgAirTempAndSSD(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    WindData windData;
    unsigned short int yearInput = promptYear();
    float tempSum;
    float total;
    Vector<float> airTemps; // To store individual air temperatures for standard deviation calculation

    std::cout << yearInput << std::endl;

    for(unsigned short int i = 0; i < 12; i++){

        tempSum = 0;

        // Calculate the sum of air temperatures
        total = calculateAirTempSum(WindDataVec, yearInput, i + 1, tempSum, airTemps);

        // Calculate the average air temperature
        float avgTemp = average(tempSum, total);

        // Calculate the standard deviation for air temperature
        float stdDevTemp = calculateSSD(airTemps, avgTemp);

        std::cout << WindData.d.monthAry[i] << ": ";
        std::cout << "average Air Temperature: " << avgTemp << " degrees C, ";
        std::cout << "Standard Deviation: " << stdDevTemp << " degrees C" << std::endl;
    }
}

float calculateAirTempSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month, float &tempSum, Vector<float> &airTemps)
{
    unsigned short int total = 0;
    airTemps.clear(); // Clear the vector to store new values

    for(unsigned int i = 0; i < WindDataVec.getSize(); i++){

        WindRecType WindData = WindDataVec[i];  // Using the overloaded subscript operator

        if((year == WindData.d.getYear()) && (month == WindData.d.getMonth())){
            // Counting the average
            tempSum = tempSum + WindData.airTemp;
            airTemps.pushBack(WindData.airTemp); // Store individual air temperature
            total++;
        }
    }
    return total;
}





void totalSolarRad(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    WindData windData;;
    unsigned short int yearInput = promptYear();
    float solarSum;

    std::cout << yearInput << std::endl;

    for(unsigned short int i = 0; i < 12; i++){

        solarSum = calculateSolarRadSum(WindDataVec, yearInput, i + 1);

        std::cout << WindData.d.monthAry[i] << ": ";
        printSolarRadTotalMonth(solarSum);
    }
}

void writeFile(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map)
{
    WindRecType WindData;

    unsigned short int yearInput = promptYear();
    float tempSum, speedSum, solarSum;
    float total;
    Vector<float> windSpeeds, airTemps; // To store individual values for standard deviation calculation
    std::ofstream ofile("WindTempSolar.csv");

    ofile << yearInput << std::endl;

    for(unsigned short int i = 0; i < 12; i++){

        tempSum = 0;
        speedSum = 0;
        windSpeeds.clear();
        airTemps.clear();

        total = calculateWindSpeedandAirTempSum(WindDataVec, yearInput, i + 1, speedSum, tempSum, windSpeeds);
        solarSum = calculateSolarRadSum(WindDataVec, yearInput, i + 1);

        float avgSpeed = average(speedSum, total);
        float stdDevSpeed = calculateSSD(windSpeeds, avgSpeed);

        float avgTemp = average(tempSum, total);
        float stdDevTemp = calculateSSD(airTemps, avgTemp);

        if (total > 0) {
            ofile << WindData.d.monthAry[i] << ',';
            if (avgSpeed != 0) {
                ofile << avgSpeed << "(" << stdDevSpeed << "),";
            } else {
                ofile << ",";
            }

            if (avgTemp != 0) {
                ofile << avgTemp << "(" << stdDevTemp << "),";
            } else {
                ofile << ",";
            }

            ofile << solarSum << std::endl;
        }
    }

    if (ofile.tellp() == std::streampos(0)) {
        ofile << "No Data" << std::endl;
    }

    std::cout << "File has been written to." << std::endl;
}

int promptYear()
{
    Date d;
    unsigned short int year = 0;

    do{
        std::cout << '\n' << "Enter Year:" << std::endl;
    }while(!isValidInputType(year) || !d.isValidYear(year));

    return year;
}

int promptMonth()
{
    Date d;
    unsigned short int month = 0;

    do{
        std::cout << '\n' << "Enter Month:" << std::endl;
    }while(!isValidInputType(month) || !d.isValidMonth(month));

    return month;
}

bool isValidInputType(unsigned short int &input)
{
    bool validInput = false;

    if(!(std::cin >> input)){

        std::cout << "Invalid Value" << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }else{

        validInput = true;
    }
    return validInput;
}

float calculateWindSpeedandAirTempSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month, float &speedSum, float &tempSum, Vector<float> &windSpeeds)
{
    unsigned short int total = 0;

    for(unsigned int i = 0; i < WindDataVec.getSize(); i++){

        WindRecType WindData = WindDataVec[i];  // Using the overloaded subscript operator

        if((year == WindData.d.getYear()) && (month == WindData.d.getMonth())){
            // Counting the average
            tempSum = tempSum + WindData.airTemp;
            speedSum = speedSum + WindData.windSpeed;

            // Add the individual wind speed to the windSpeeds vector
            windSpeeds.pushBack(WindData.windSpeed);

            total++;
        }
    }
    return total;
}



float calculateSolarRadSum(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, float year, float month)
{
    float sum = 0;
    WindRecType WindData;

    //linear searches the entire vector for indexes matching user input
    for(unsigned int i = 0; i < WindDataVec.getSize() ; i++){

        WindData = WindDataVec[i];  // Use operator[] instead of getElement

        if((year == WindData.d.getYear()) && (month == WindData.d.getMonth())){

            // does not count in values less than 0.017 kWh/m^2 (100 W/hm2)
            if(WindData.solarRad >= wattsToKiloWatts(100)){
                sum = sum + WindData.solarRad;
            }
        }
    }
    return sum;
}


void printAvgWindSpeedAndAirTemp(float speed, float temp, float total)
{
    if(average(speed, total) != 0 || average(temp, total) != 0){

        std::cout << average(speed, total) << " km/h, "
             << average(temp, total) << " degrees C" << std::endl;
    }
    else
    {
        std::cout << "No Data" << std::endl;
    }
}

void printSolarRadTotalMonth(float solarSum)
{
    if(solarSum != 0){

        std::cout << solarSum << " kWh/m^2" << std::endl;
    }else{
        std::cout << "No Data" << std::endl;
    }
}

float average(float sum, float total)
{
    float avg;

    if(total == 0){
        avg = 0;
    }else{
        avg = sum/total;
    }

    return avg;
}

float speedMetersPerSecToKmPerHour(const float metre)
{
    return metre * 3.6;
}

float wattsToKiloWatts(const float watts)
{
    return (watts * ((float)1/(float)6))/ 1000;
}


double calculateSPCC(const Vector<double>& x, const Vector<double>& y) {

    if (x.getSize() != y.getSize()) {
        std::cerr << "Error: Vectors must be of the same size." << std::endl;
        return std::numeric_limits<double>::quiet_NaN(); // Return NaN to indicate an error
    }

    double sumX = 0.0;
    double sumY = 0.0;
    for (unsigned i = 0; i < x.getSize(); ++i) {
        sumX += x[i];
        sumY += y[i];
    }
    double meanX = sumX / x.getSize();
    double meanY = sumY / y.getSize();

    double sumNumerator = 0.0;
    double sumDenominatorX = 0.0;
    double sumDenominatorY = 0.0;

    for (unsigned i = 0; i < x.getSize(); ++i) {
        sumNumerator += (x[i] - meanX) * (y[i] - meanY);
        sumDenominatorX += (x[i] - meanX) * (x[i] - meanX);
        sumDenominatorY += (y[i] - meanY) * (y[i] - meanY);
    }

    double denominator = std::sqrt(sumDenominatorX * sumDenominatorY);
    if (denominator == 0) {
        std::cerr << "Error: Division by zero." << std::endl;
        return std::numeric_limits<double>::quiet_NaN(); // Return NaN to indicate an error
    }

    return sumNumerator/denominator;
}

void calculateSPCCForMonth(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map) {
    unsigned short int month = promptMonth();

    Vector<double> windSpeeds, airTemps, solarRads;
    extractMonthData(WindDataVec, month, windSpeeds, airTemps, solarRads);

    double spcc_ST = calculateSPCC(windSpeeds, airTemps);
    double spcc_SR = calculateSPCC(windSpeeds, solarRads);
    double spcc_TR = calculateSPCC(airTemps, solarRads);

    std::cout << "Sample Pearson Correlation Coefficient for " << WindDataVec[0].d.monthAry[month-1] << std::endl;
    std::cout << "S_T: " << std::fixed << std::setprecision(2) << spcc_ST << std::endl;
    std::cout << "S_R: " << std::fixed << std::setprecision(2) << spcc_SR << std::endl;
    std::cout << "T_R: " << std::fixed << std::setprecision(2) << spcc_TR << std::endl;
}

void extractMonthData(std::map<int,BST<WindData> > month_map, std::map<int,BST<WindData> > year_map, unsigned short int month, Vector<double>& windSpeeds, Vector<double>& airTemps, Vector<double>& solarRads) {

    for (unsigned int i = 0; i < WindDataVec.getSize(); ++i) {
        if (WindDataVec[i].d.getMonth() == month) {
            windSpeeds.pushBack(WindDataVec[i].windSpeed);
            airTemps.pushBack(WindDataVec[i].airTemp);
            solarRads.pushBack(WindDataVec[i].solarRad);
        }
    }
}







