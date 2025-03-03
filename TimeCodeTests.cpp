//Author: Harein Abeysekera
//Date: February 17th, 2025

#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(1, 10, 30); 
	assert(t2 == 4230);
	
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(0, 0, 0);
	assert(t3 == 0);

	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	
	TimeCode tc4 = TimeCode(3, 60, 0); // This is an invalid time code that should roll over
	assert(tc4.ToString() == "4:0:0");  // Expecting 4 hours and 0 minutes after rolling over the 60 minutes
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	TimeCode tc2 = TimeCode(10, 30, 45);
	tc2.GetComponents(h, m, s);
	assert(h == 10 && m == 30 && s == 45);
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}

void TestAddition() {
    cout << "Testing Addition" << endl;

    TimeCode tc1(2, 30, 45); // 2 hours, 30 minutes, 45 seconds
    TimeCode tc2(1, 44, 20); // 1 hour, 44 minutes, 20 seconds
    TimeCode result = tc1 + tc2; // Expected result: 4 hours, 15 minutes, 5 seconds

    assert(result.ToString() == "4:15:5");

    cout << "PASSED!" << endl << endl;
}

void TestComparison(){
    cout << "Testing Comparison Operators" << endl;

<<<<<<< HEAD
<<<<<<< HEAD
=======
    // Creating test cases
>>>>>>> 4741e2d (Forgot to add tests)
=======
>>>>>>> c88ae26 (Save local changes before pulling)
    TimeCode tc1 = TimeCode(1, 30, 30);  // 1 hour, 30 minutes, 30 seconds
    TimeCode tc2 = TimeCode(2, 0, 0);    // 2 hours, 0 minutes, 0 seconds
    TimeCode tc3 = TimeCode(1, 30, 30);  // 1 hour, 30 minutes, 30 seconds (same as tc1)

    // Test equality (==) operator
    assert(tc1 == tc3); // Should be equal
    assert(!(tc1 == tc2)); // Should not be equal

    // Test inequality (!=) operator
    assert(tc1 != tc2); // Should be unequal
    assert(!(tc1 != tc3)); // Should not be unequal

    // Test less than (<) operator
    assert(tc1 < tc2); // tc1 is less than tc2
    assert(!(tc2 < tc1)); // tc2 is not less than tc1

    // Test greater than (>) operator
    assert(!(tc1 > tc2)); // tc1 is not greater than tc2
    assert(tc2 > tc1); // tc2 is greater than tc1

    // Test less than or equal to (<=) operator
    assert(tc1 <= tc3); // tc1 is equal to tc3
    assert(tc1 <= tc2); // tc1 is less than tc2

    // Test greater than or equal to (>=) operator
    assert(tc2 >= tc1); // tc2 is greater than or equal to tc1
    assert(tc3 >= tc1); // tc3 is equal to tc1

    cout << "PASSED!" << endl << endl;
}


// Many More Tests...

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestSubtract();
	TestSetMinutes();
	TestAddition();  
	TestComparison(); 
	
	// Many other test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
