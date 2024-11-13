#include <iostream>
#include <vector>
#include <algorithm> 
#include <stack>


using namespace std;

// Function for calculating the minimum number of operations for exponentiation
int minOperations(int N, vector<int>& operations) {
    // Array for storing the minimum number of operations for each degree from 1 to N
    vector<int> Op(N + 1, 0);
    // Array for storing the previous number in the sequence of operations
    vector<int> previous(N + 1, 0);

    // For a power of 1, the number of operations is 0
    Op[1] = 0;

    for (int i = 2; i <= N; i++) {
        Op[i] = Op[i - 1] + 1; 
        previous[i] = i - 1;
        for (int j = 2; j <= i - 1; j++) {
            if (Op[i] > Op[j] + Op[i - j] + 1) {
                Op[i] = Op[j] + Op[i - j] + 1;
                previous[i] = j;
            }
            if (i % j == 0 && Op[i] > Op[i / j] + j - 1) {
                Op[i] = Op[i / j] + j - 1;
                previous[i] = i / j;
            }
        }
    }

    // Restoring the path
    int current = N;
    while (current > 1) {
        // Adding the current degree to the vector
        operations.push_back(current);
        // Moving on to the previous degree
        current = previous[current];
    }
    operations.push_back(1);

    reverse(operations.begin(), operations.end());

    return Op[N];
}

int main() {
    int N;
    cout << "Enter the degree of N: ";

    while (!(cin >> N) || N <= 0) {
        cerr << "Error: The power of N must be a positive number. Try again: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> operations;
    int result = minOperations(N, operations);

    cout << "Minimum number of operations: " << result << '\n';
    cout << "The sequence of operations: ";
    for (int op : operations) {
        cout << op << " ";
    }
    cout << '\n';

    return 0;
}