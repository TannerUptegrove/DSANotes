#include <iostream>
#include <vector>
using namespace std;

// Two Pointers Algorithm Technique:
// - Two indices (pointers) are used to traverse a data structure
//   either towards each other or in the same direction.
// - This is typically used for problems involving sorted arrays,
//   or those asking about two elements, subarrays, or ranges instead
//   of working with single elements.
// - Can be used to detect cycles in linked lists.

// Problem: Given a sorted array of numbers and a target integer,
//          find if there exists any pair of elements such that
//          their sum is equal to the target.

// Naive Approach: Check all possible pairs.
// Time Complexity: O(n^2)
// Space Complexity: O(1)
vector<int> NaiveTwoSum(vector<int>& numbers, int target) {
    int n = numbers.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (numbers[i] + numbers[j] == target) {
                cout << "\nNumbers " << numbers[i] << " and " << numbers[j] << " sum to the target.\n";
                return {numbers[i], numbers[j]};
            }
        }
    }

    cout << "\nA valid pair could not be found...\n";
    return {};
}

// Expected Approach: Two Pointers Technique.
// Time Complexity: O(n)
// Space Complexity: O(1)
vector<int> TwoSumPointers(vector<int>& numbers, int target) {
    int n = numbers.size();

    // Pointers to initialized to represent the edges of the array.
    // They will move towards each other as the algorithm tries to
    // find a valid sum, although which one moves depends on
    // if the sum they calculated is less than or equal to the target.
    int left = 0, right = n - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum == target) {
            cout << "\nNumbers " << numbers[left] << " and " << numbers[right] << " sum to the target.\n";
            return {numbers[left], numbers[right]};
        }
        else if (sum < target) 
            left++; // Move towards a higher sum.
        else
            right--; // Move towards a smaller sum.
    }


    cout << "\nA valid pair could not be found...\n";
    return {};
}

int main() {
    vector<int> numbers = {-3, -1, 0, 1, 2};

    vector<int> pair = NaiveTwoSum(numbers, -2);
    pair = TwoSumPointers(numbers, -2);

    return 0;
}