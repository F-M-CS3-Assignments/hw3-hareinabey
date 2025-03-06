//Author: Harein Abeysekera
//Date: March 3rd, 2025
// I have read the assignment notes.

#include <iostream>     
#include <fstream>     
#include <sstream>      
#include <vector>       
#include <stdexcept>    
#include <algorithm>    
#include "TimeCode.h"  
using namespace std;

// Function that splits a string into tokens using a specified delimiter.
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;  // Vector to store the resulting substrings.
    string token;           // Temporary string to hold each token.
    istringstream tokenStream(s);  // Create an input string stream from the given string.
    while(getline(tokenStream, token, delimiter)) {
        tokens.push_back(token); // Add each token to the vector.
    }
    return tokens; 
}

// Updated parse_line function using friend's approach:
// It splits the line by commas, then searches for a token containing a colon.
// Then it splits that token by spaces and picks the first part that contains a colon.
// Finally, it splits the extracted time by ':' and converts it to a TimeCode.

TimeCode parse_line(const string &line) {
    vector<string> tokens = split(line, ',');  // Split the line by commas.
    string time_str = "";
    
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].find(":") != string::npos) {  // Find a token that contains a colon.
            vector<string> parts = split(tokens[i], ' '); // Split that token by spaces.
            for (int j = 0; j < parts.size(); j++) {
                if (parts[j].find(":") != string::npos) { // Extract the part that contains a colon.
                    time_str = parts[j];
                    break;
                }
            }
            if (!time_str.empty())
                break;
        }
    }
    
    if (time_str.empty()) { // If no time was found, return default TimeCode.
        return TimeCode(0, 0, 0);
    }
    // Remove any spaces from the extracted time.
    time_str.erase(remove(time_str.begin(), time_str.end(), ' '), time_str.end());
    
    // Split the time string by ':'.
    vector<string> time_parts = split(time_str, ':');
    if (time_parts.size() == 2) { 
        int hours = stoi(time_parts[0]);
        int minutes = stoi(time_parts[1]);
        int seconds = 0; // Default for seconds is 0.
        return TimeCode(hours, minutes, seconds);
    } else if (time_parts.size() == 3) {
        int hours = stoi(time_parts[0]);
        int minutes = stoi(time_parts[1]);
        int seconds = stoi(time_parts[2]);
        return TimeCode(hours, minutes, seconds);
    } else {
        return TimeCode(0, 0, 0);
    }
}

int main() {
    // Open the CSV file (hardcoded).
    ifstream infile("Space_Corrected.csv");
    if (!infile) {  // Check if the file opening failed.
         cerr << "Failed to open Space_Corrected.csv" << endl;
         return 1;
    }
    
    string line;  // Variable to hold each line read from the file.
    
    // Skip the header row.
    getline(infile, line);
    
    vector<TimeCode> times;     // Vector to store valid TimeCode objects.
    int valid_data_points = 0;
    
    // Read the file line by line.
    while(getline(infile, line)) {
         if(line.empty()) continue;  // Skip empty lines.
         try {
              TimeCode tc = parse_line(line);  // Parse the line into a TimeCode.
              // If the parsed time is 0:0:0 and the line doesn't contain "00:00 UTC",
              // assume the launch instance is missing exact time data and skip it.
              if(tc.GetHours() == 0 && tc.GetMinutes() == 0 && line.find("00:00 UTC") == string::npos) {
                  continue;
              } else {
                  times.push_back(tc);  // Add the valid TimeCode to the vector.
                  valid_data_points++;
              }
         } catch (const exception &e) {
              // Ignore lines that cannot be parsed.
         }
    }
    infile.close();  // Close the file.
    
    if (times.empty()) {
         cout << "0 data points." << endl;
         return 0;
    }
    
    // Sum all TimeCode objects in seconds.
    unsigned long long total_seconds = 0;
    for (const auto &tc : times) {
         total_seconds += tc.GetTimeCodeAsSeconds();
    }
    
    // Compute the average time in seconds using rounding.
    unsigned long long n = times.size();
    unsigned long long avg_seconds = (total_seconds + n / 2) / n;
    int avg_hours = avg_seconds / 3600;
    int avg_minutes = (avg_seconds % 3600) / 60;
    int avg_secs = avg_seconds % 60;
    TimeCode avg(avg_hours, avg_minutes, avg_secs);
    
    // Output the total number of valid data points and the computed average time.
    cout << valid_data_points << " data points." << endl;
    cout << "AVERAGE: " << avg.ToString() << endl;
    return 0;
}
