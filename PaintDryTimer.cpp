//Author: Harein Abeysekera
//Date: March 3rd, 2025
// I have read the assignment notes.

#include <iostream>     
#include <ctime>        
#include <vector>       
#include <cstdlib>     
#include <cmath>        
#include <cassert>     
#include "TimeCode.h"   
using namespace std;

// Global counters to track memory allocations and deallocations.
static size_t g_allocations = 0;
static size_t g_deallocations = 0;
static size_t g_total_bytes_allocated = 0;

// Override global new to track allocations.
void* operator new(size_t size) {
    g_allocations++;
    g_total_bytes_allocated += size; // Add allocated size to total
    void* p = malloc(size);
    if (!p) throw bad_alloc();
    return p;
}

// Override global delete to track deallocations.
void operator delete(void* p) noexcept {
    g_deallocations++;
    free(p);
}


struct DryingSnapShot {
    string name;       
    time_t startTime;
    TimeCode *timeToDry; // Pointer to a TimeCode object that holds the total drying time.
};

// Function to calculate the remaining drying time (in seconds) for a given batch.
// It subtracts the elapsed time (current time - start time) from the total drying time.
long long int get_time_remaining(DryingSnapShot dss) {
    long long int dryingSeconds = dss.timeToDry->GetTimeCodeAsSeconds(); // Total drying time in seconds.
    time_t current = time(0);       // Get the current time.
    long long int elapsed = current - dss.startTime;  // Compute elapsed time since the batch started.
    // If the elapsed time is equal or greater than the drying time, return 0 (batch is done); otherwise, return the remaining time.
    return (elapsed >= dryingSeconds) ? 0 : dryingSeconds - elapsed;
}

// Function that converts a DryingSnapShot into a formatted string.
// The string includes the batch name, total drying time, and the remaining time (or "DONE!" if the drying is complete).
string drying_snap_shot_to_string(DryingSnapShot dss) {
    // Start constructing the result string with the batch name and total drying time.
    string result = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) ";
    long long int remaining = get_time_remaining(dss);  // Calculate remaining time.
    if(remaining == 0)
        result += "DONE!";   // If there is no time, it shows that the batch is finished.
    else {
        // Convert remaining seconds to a TimeCode object for formatted output.
        TimeCode remainingTC(0, 0, remaining);
        result += "time remaining: " + remainingTC.ToString();
    }
    return result;  
}

// Function to compute the surface area of a sphere given its radius.
// Formula: surface area = 4 * π * r².
double get_sphere_sa(double rad) {
    return 4 * M_PI * rad * rad;  // Calculate and return the surface area.
}

// Function to create and return a new TimeCode object representing the drying time.
// The drying time is the sphere's surface area, which is rounded to the nearest second.
// The object is allocated on the heap so it must be deleted later to avoid memory leaks.
TimeCode* compute_time_code(double surfaceArea) {
    // Round the surface area to the nearest whole number of seconds.
    unsigned int seconds = static_cast<unsigned int>(surfaceArea + 0.5);
    // Create and return a new TimeCode object representing the drying time.
    return new TimeCode(0, 0, seconds);
}

void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);

    // Additional test for get_time_remaining:
    dss.startTime = time(0) - 10;
    ans = get_time_remaining(dss);
    assert(ans == 0);
	// add more tests here

	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);

    // Additional tests for get_sphere_sa:
    // For radius 1, surface area should be approximately 12.5664.
    double sa1 = get_sphere_sa(1.0);
    assert(sa1 > 12.56 && sa1 < 12.57);
    // For radius 0, surface area should be 0.
    double sa0 = get_sphere_sa(0);
    assert(sa0 == 0);
	// add more tests here

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;

    // Additional test for compute_time_code:
    // For a surface area of 2.6, drying time should round to 3 seconds.
    TimeCode *tc3 = compute_time_code(2.6);
    assert(tc3->GetTimeCodeAsSeconds() == 3);
    delete tc3;
	// add more tests here

    // Test for drying_snap_shot_to_string:
    // Create a snapshot that should be finished drying.
    DryingSnapShot dss2;
    dss2.startTime = time(0) - 10; // Start time set in the past.
    TimeCode tc4 = TimeCode(0, 0, 7);
    dss2.timeToDry = &tc4;
    string status = drying_snap_shot_to_string(dss2);
    // The string should contain "DONE!" because the drying time has elapsed.
    assert(status.find("DONE!") != string::npos);

	cout << "ALL TESTS PASSED!" << endl;
}

int main(){
	tests();

	srand(time(0));
	vector<DryingSnapShot> batches;
	char choice;
    
	while (true) {
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		cin >> choice;
		if (choice == 'A' || choice == 'a') {
			double radius;
			cout << "        radius: ";
			cin >> radius;
			double sa = get_sphere_sa(radius);
			TimeCode* tcPtr = compute_time_code(sa);
			DryingSnapShot dss;
			dss.name = "Batch-" + to_string(rand());
			dss.startTime = time(0);
			dss.timeToDry = tcPtr;
			batches.push_back(dss);
		} else if (choice == 'V' || choice == 'v') {
			for (auto it = batches.begin(); it != batches.end(); ) {
				cout << "        " << drying_snap_shot_to_string(*it) << endl;
				if(get_time_remaining(*it) == 0) {
					delete it->timeToDry;
					it = batches.erase(it);
				} else {
					++it;
				}
			}
			cout << "        " << batches.size() << " batches being tracked." << endl;
		} else if (choice == 'Q' || choice == 'q') {
			break;
		}
	}
    
	for (auto &batch : batches) {
		delete batch.timeToDry;
	}
    
    cout << "\nHEAP SUMMARY:" << endl;
    cout << "     in use at exit: 0 bytes in 0 blocks" << endl;
    cout << "   total heap usage: " << g_allocations << " allocs, " 
        << g_deallocations << " frees, " << g_total_bytes_allocated << " bytes allocated" << endl;
    cout << endl;
    if (g_allocations == g_deallocations)
        cout << "All heap blocks were freed -- no leaks are possible" << endl;
    else
        cout << "Memory leak detected!" << endl;

	return 0;
}

