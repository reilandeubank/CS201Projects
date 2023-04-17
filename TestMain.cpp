#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"

void foo(CircularDynamicArray<int> x) {
	cout << "in foo" << endl;
	for (int i=0; i<x.length()/2; i++){
		cout << x[i] << " and " << x.length()/2+i << endl;
		x[i] = x[x.length()/2+i];
	}
	// X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"	
	for (int i=0; i< x.length();i++) cout << x[i] << " ";  cout << endl;
}

int main(){
	CircularDynamicArray<int> A,B;
	for(int i=0; i<10;i++) A.addEnd(i);
	B = A;
	A.addEnd(15); A.addEnd(19);
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" 
	cout << "Select is " << A.linearSearch(5) << endl;
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	cout << "Select is " << A.binSearch(15) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => -1
	cout << "Select is " << A.binSearch(15) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 10	
	A.addFront(10); 
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	cout << "Select is " << A.linearSearch(5) << endl;
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
	cout << "Quick Select should be 2, is " << A.QuickSelect(3) << endl;
	for (int i=0; i< A.capacity();i++) cout << A[i] << " ";  cout << endl;
    // Select => 2	
	cout << "WCSelect should be 15, is " << A.WCSelect(12) << endl;
	// Select => 15
	A.stableSort();
	//for (int i=0; i< A.capacity();i++) cout << A[i] << " ";  cout << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
	A.addEnd(11); A.addFront(1); A.addFront(2); A.addFront(3);
	//cout << "capacity is " << A.length() << endl;
	// A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32
	A.delFront(); A.delFront();
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	foo(A);
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"
	for (int i=0; i< B.length();i++) cout << B[i] << " ";  cout << endl;
	// B => "0 1 2 3 4 5 6 7 8 9"
}