#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Sliding Window Algorithm Technique:
// - Used to solve problems that involve subarrays or substrings, 
//   otherwise referred to as windows.
// - The main idea is to use the results of the previous window
//   for computations for the next window.
// - Commonly used for problems like finding subarrays with a
//   specific sum or finding the longest substring with unique
//   characters.
//
// - This does not require that the array be sorted.
//
// Types:
// - Fixed Size: Usually involves taking out the first element of the previous
//               window and putting in the next element in the array.
// - Variable Size: Usually involves increasing the right pointer of the window
//                  one by one until a condition is true. If the condition does
//                  not match at any step, the window is shrunk by increasing
//                  the left pointer.
//
// Problem: Given an array of numbers, calculate the maximum sum
//          of a subarray with size k.

// Naive Approach: Test all subarrays.
// Time Complexity: O(n * k)
// Space Complexity: O(1)
int NaiveMaxSum(vector<int>& numbers, int k) {
    int n = numbers.size();
    int maxSum = INT_MIN;

    // Iterates for each possible subarray.
    for (int i = 0; i <= n - k; i++) {
        int currentSum = 0;

        // Iterates for each element in the current window.
        for (int j = 0; j < k; j++)
            // i + j Grabs each element within the window in order.
            currentSum += numbers[i + j];

        // The last saved maximum sum is evaluated with the new one
        // created from each subarray.
        maxSum = max(currentSum, maxSum);
    }

    return maxSum;
}

// Expected Approach: Sliding Window Technique.
// Time Complexity: O(n)
// Space Complexity: O(1)
int SlidingWindowMaxSum(vector<int>& numbers, int k) {
    int n = numbers.size();

    // The give window size cannot be greater than the array's.
    if (n <= k) {
        cout << "\nInvalid array or subarray size...\n";
        return INT_MIN;
    }

    int maxSum = 0;

    // Compute the sum of the first window.
    // Iterates for each element in the first window.
    for (int i = 0; i < k; i++) {
        maxSum += numbers[i];
    }

    // Compute the sum of the other following windows
    // by removing the first element of the last window
    // and adding the last element of the current window.
    int windowSum = maxSum;

    // Starts at the end of the first window.
    // Iterates through the rest of the array.
    for (int i = k; i < n; i++) {
        // i - k Grabs the first element of the last window.
        // i Grabs the next element after the last window.
        windowSum += numbers[i] - numbers[i - k];
        maxSum = max(windowSum, maxSum);
    }

    return maxSum;
}

int main() {
    vector<int> numbers = {5, 2, -1, 0, 3};

    cout << "The maximum sum is: " << NaiveMaxSum(numbers, 3) << endl;
    cout << "The maximum sum is: " << SlidingWindowMaxSum(numbers, 3) << endl;

    return 0;
}