#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

using namespace std;

template <typename T>
    class CircularDynamicArray{
    private:
        int cap;
        int size;
        int front;
        T *arr;
        T *newArr;
        T *arr2;

    int wrapper(int n) {                //Math to convert user index to real index
        if (n < 0) {
            return wrapper(n + cap);
        }
        else {
            return (front + n) % cap;
        }
    }

    int partition(T arr[], int left, int right)
    {
        int x = int (arr[right]), i = left;
        for (int j = left; j <= right - 1; j++)
        {
            if (int(arr[j]) <= x)
            {
                swap(&arr[i], &arr[j]);
                i++;
            }
        }
        swap(&arr[i], &arr[right]);
        return i;
    }

    int randomPartition(T arr[], int left, int right)                   //returns a random partition for the array
    {
        int n = right-left+1;
        int pivot = rand() % n;
        swap(&arr[left + pivot], &arr[right]);
        return partition(arr, left, right);
    }

    T kthSmallest(T arr[], int l, int r, int k)                         //returns kth smallest element
    {
        if (k > 0 && k <= r - l + 1)                                    //checks if k is a possitive integer and less than the range of values
        {
            int pos = randomPartition(arr, l, r);
            if (pos-l == k-1)                                           //if the position is the kth smallest
                return arr[pos];
            if (pos-l > k-1)                                            //if it is in the left sub array
                return kthSmallest(arr, l, pos-1, k);
            return kthSmallest(arr, pos+1, r, k-pos+l-1);               //return if in right sub array
        }
        return -1;
    }

    void swap(T *a, T *b)
    {
        T temp = *a;
        *a = *b;
        *b = temp;
    }

    void swap(T a, T b) {
        T temp = a;
        a = b;
        b = temp;
    }

    int WCpartition(T arr[], int l, int r, int x) {
        int i;                                                          // Search for x in arr[l..r] and move it to end
        for (i=l; i<r; i++)
            if (arr[i] == x)
            break;
        swap(&arr[i], &arr[r]);
    
        i = l;  if                                                      // Standard partition algorithm
        for (int j = l; j <= r - 1; j++)
        {
            if (arr[j] <= x)
            {
                swap(&arr[i], &arr[j]);
                i++;
            }
        }
        swap(&arr[i], &arr[r]);
        return i;
    }

    int WCfindMedian(T arr[], int n) {
        sorter(arr, 0, size-1);                                         // Sort the array
        return arr[n/2];                                                // Return middle element
    }

    T WCkthSmallest(T arr[], int l, int r, int k) {
        if (k > 0 && k <= r - l + 1)                                    // If k is smaller than number of elements in array
        {
            int n = r-l+1;                                              // Number of elements in arr[l..r]
    
            // Divide arr[] in groups of size 5, calculate median of every group and store it in median[] array.
            int i, median[(n+4)/5];                                     // There will be floor((n+4)/5) groups;
            for (i=0; i<n/5; i++) {
                median[i] = WCfindMedian(arr+l+i*5, 5);
            }
            if (i*5 < n) {                                              //For last group with less than 5 elements
                median[i] = WCfindMedian(arr+l+i*5, n%5);
                i++;
            }   
    
            // Find median of all medians using recursive call.
            // If median[] has only one element, then no need
            // of recursive call
            int medOfMed = (i == 1)? median[i-1]: WCkthSmallest(median, 0, i-1, i/2);
    
            // Partition the array around a random element and
            // get position of pivot element in sorted array
            int pos = WCpartition(arr, l, r, medOfMed);
    
            if (pos-l == k-1) {                                      // If position is same as k
                return arr[pos];
            }
            if (pos-l > k-1) {                                      // If position is more, recur for left
                return WCkthSmallest(arr, l, pos-1, k);
            }
            return WCkthSmallest(arr, pos+1, r, k-pos+l-1);         // Else recur for right subarray
        }
    
        return -1;  j                                               // If k is more than number of elements in array
    }

    void mergeSort(T arr[], int left, int right) {                                  //handles recursive merge
        if (left >= right) {
            return;
        }
        int middle = left + ((right - left) / 2);
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }

    void merge(T arr[], int const left, int const middle, int const right) {        //Takes the two arrays and merges them into one
        int sizeLeft = middle - left + 1;
        int sizeRight = right - middle;
        T *leftSubArray = new T[sizeLeft];
        T *rightSubArray = new T[sizeRight];

        int i = 0, j = 0, k = 0;

        for (int i = 0; i < sizeLeft; i++) {
            leftSubArray[i] = arr[left + i];
        }
        for (int j = 0; j < sizeRight; j++){
            rightSubArray[j] = arr[middle + j + 1];
        }

        i = 0;
        j = 0;
        k = left;
        while(i < sizeLeft && j < sizeRight) {
            if (leftSubArray[i] <= rightSubArray[j]) {
                arr[k] = leftSubArray[i];
                i++;
            }
            else {
                arr[k] = rightSubArray[j];
                j++;
            }
            k++;
        }
        while (i < sizeLeft) {
            arr[k] = leftSubArray[i];
            i++;
            k++;
        }
        while (k < sizeRight) {
            arr[k] = rightSubArray[j];
            j++;
            k++;
        }
        delete []leftSubArray;
        delete []rightSubArray;

    }

    int binarySearch(T arr[], int l, int r, int x) {            //Handles binary search recursive calls
        if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x){
            return mid;
        }
        if (arr[mid] > x){
            return binarySearch(arr, l, mid - 1, x);
        }
        return binarySearch(arr, mid + 1, r, x);
        }
        return -1;
    }

    void sorter(T arr[], int left, int right) {
        if (size < cap) {
            arr2 = new T[size];
            for (int i = 0; i < size; i++) {
                arr2[i] = arr[wrapper(i)];
            }
            front = 0;
            arr = arr2;
        }
        mergeSort(arr, left, right);
    }
    
    public:
    CircularDynamicArray() {                                    //Default constructor
        arr = new T[cap=2];
        size = 0;
        front = 0;
    }

    CircularDynamicArray(int s) {                               //Overloaded constructor with int for size
        arr = new T[cap=s];
        size = 0;
        front = 0;
    }

    ~CircularDynamicArray(){                                    //Destructor
        delete arr;
    }

    CircularDynamicArray(CircularDynamicArray &a) {             //Copy Constructor
        cap = a.cap;
        size = a.size;

        for(int i = 0; i < size; i++) {
            arr[i] = a[i];
        }
    }

    CircularDynamicArray& operator=(CircularDynamicArray& a) {
        cap = a.cap;
        size = a.size;
        T *arr = new T[cap];
        for(int i = 0; i < size; i++) {
            arr[i] = a[i];
        }
        return *this;
    }

    T &operator[](int i) {
        if(i > cap) {
            cout << "Index out of bounds" <<endl; 
            // return first element
            return arr[wrapper(0)];
        }
        
        return arr[wrapper(i)];
    }

    void addEnd(T v) {                  //Add v to end of arr in O(1) amortized 
        if (size == 0) {                //if array is empty
            arr[0] = v;
            size++;
        }
        else if (size < cap) {          //has space for add
            arr[wrapper(size)] = v;
            size++;
        }
        else {                          //if size = capacity
            arr2 = new T[cap*=2];
            for (int i = 0; i < cap; i++) {
                arr2[i] = arr[i];
            }
            arr = arr2;
            addEnd(v);
        }
    }

    void addFront(T v) {                //Add v to front of arr (circular) in O(1) amortized
        if (size == 0) {                //if array is empty
            arr[0] = v;
        }
        else if (size < cap) {          //has space for add
            arr[wrapper(-1)] = v;
            front--;
            if (front < 0) {
                front += cap;
            }
        }
        else {                          //if size = capacity
            arr2 = new T[cap*=2];
            for (int i = 0; i < cap; i++) {
                arr2[i] = arr[i];
            }
            arr = arr2;
            addFront(v);
        }
        size++;
    }

    void delEnd() {                     //Deletes end of arr in O(1) amortized
        if (size-1 >= (cap*.25)) {      //if resize not needed
            arr[wrapper(size)] = -1;
            size--;
        }
        else {                          //if less than 1/4 array is full
            cap = cap/2;
            arr2 = new T[cap];
            for (int i = 0; i < cap; i++) {
                arr2[i] = arr[i];
            }
            arr = arr2;
            size--;
        }
    }

    void delFront() {                   //Deletes front of arr in O(1) amortized
        if (size-1 >= (cap*.25)) {      //if resize not needed
            arr[wrapper(0)] = -1;
            size--;
            front++;
        }
        else {                          //if less than 1/4 array is full
            cap = cap/2;
            arr2 = new T[cap];
            for (int i = 0; i < cap; i++) {
                arr2[i] = arr[i];
            }
            arr = arr2;
            size--;
            front++;
        }
    }

    int length() {                      //return size
        return size;
    }

    int capacity() {                    //return capacity
        return cap;
    }

    void clear() {                      //clears arr, starts over size 0 capacity 2
        delete arr;
        arr = new T[cap=2];
        size = 0;
    }

    T QuickSelect(int k) {              //select key k from array in O(n) but worst case O(n^2)
        arr2 = new T[cap];
        for (int i = 0; i < cap; i++) {
            arr2[i] = arr[wrapper(i)];
        }
        return kthSmallest(arr2, 0, size-1, k);
    }

    T WCSelect(int k) {                 //O(n), better worst case running time than QuickSelect
        arr2 = new T[cap];
        for (int i = 0; i < cap; i++) {
            arr2[i] = arr[wrapper(i)];
        }
        return kthSmallest(arr2, 0, size - 1, k);
    }

    void stableSort() {                 //Stable mergeSort, O(n lg n)
        sorter(arr, 0, size-1);
    }

    int linearSearch (T e) {            //Searches array in O(n)
        for (int i = 0; i < size-1; i++) {
            if (arr[wrapper(i)] == e) {
                return i;
            }
        }
        return -1;
    }

    int binSearch(T e) {                //searches array in O(lg n)
        int val = binarySearch(arr, 0, size - 1, e) - front;
        while (val < 0) {
            val += cap;
        }
        return val;
    }
};