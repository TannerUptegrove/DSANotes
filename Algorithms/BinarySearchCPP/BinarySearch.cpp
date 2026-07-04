#include <iostream>
#include <vector>
using namespace std;

// Binary Search Algorithm:
// - Involves repeatedly dividing a sorted array
//   in halves until a target element is found.
// 

// Given a sorted array, this searches for the index
// of a target integer.
// Time Complexity: O(log n)
// Space Complexity: O(1)
int BinarySearch(vector<int> numbers, int target) {
    int low = 0, high = numbers.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (numbers[mid] == target)
            return mid;
        else if (numbers[mid] < target) // If the target is larger, ignore the left half.
            low = mid + 1;
        else
            high = mid - 1; // If the target is smaller, ignore the right half.
    }

    cout << "\nThe array does not contain the target integer...\n";
    return -1;
}


int main() {
    vector<int> numbers = {2, 3, 4, 10, 40};
    cout << "Index: " << BinarySearch(numbers, 10);

    return 0;
}