#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;
void fillVectorFromFile(const string& filename, vector<vector<int>>& vec) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < vec.size(); i++) {
            // Expanding the vector for the current line to the desired size
            vec[i].resize(i + 1);
            for (int j = 0; j < vec[i].size(); j++) {
                file >> vec[i][j];
            }
        }
        file.close();
    }
    else {
        cerr << "File opening error: " << filename << '\n';
    }
}
void fillVectorWithZero(vector<vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        vec[i].resize(i + 1);
        for (int j = 0; j < vec[i].size(); j++) {
            vec[i][j] = 0;
        }
    }
}
// Solving the problem: finding the maximum sum in a triangle
void Solver(vector<vector<int>>& vec, vector<vector<int>>& result) {
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            // Handling of extreme cases:
            // The vertex of the triangle
            if (i == 0) {
                result[i][j] = vec[i][j];
            }
            // Leftmost position
            else if (i > 0 && j == 0) {
                result[i][j] = vec[i][j] + result[i - 1][j];
            }
            // Far right position
            else if (i > 0 && j == result[i].size() - 1) {
                result[i][j] = vec[i][j] + result[i - 1][j - 1];
            }
            // Other cases
            else {
                result[i][j] = vec[i][j] + max(result[i - 1][j - 1], result[i - 1][j]);
            }
        }
    } 
}
// Function for finding the maximum element and the path to it
vector<int> Finder(vector<vector<int>>& result) {
    vector<int> Path;
    int maxElement = -1;
    int lastIndex = -1;
    // Finding the maximum element in the last row
    for (int j = 0; j < result[result.size() - 1].size(); j++) {
        if (result[result.size() - 1][j] > maxElement) {
            maxElement = result[result.size() - 1][j];
            lastIndex = j;
        }
    }
    // FIND PATH: Restoring the path from the maximum element to the top
    Path.push_back(lastIndex);
    int i = result.size() - 1;
    int j = lastIndex; 
    while (i > 0) {
        // If you have reached the left edge
        if (j == 0) {
            i--;
            Path.push_back(j);
        }
        // If you have reached the right edge
        else if (j == result[i].size() - 1) {
            i--;
            j = result[i].size() - 1;
            Path.push_back(j);

        }
        // Other cases
        else {
            if (result[i-1][j - 1] > result[i-1][j]) {
                i--;
                j--;
                Path.push_back(j);
            }
            else {
                i--;
                Path.push_back(j);
            }
        }
    }
    return Path;
}
void printVector(vector<vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}
int main() {
    int n;
    cout << "Enter the dimension of the triangle (an integer greater than 0): ";
    while (!(cin >> n) || n <= 0) {
        cout << "Error: Incorrect input. Enter an integer greater than 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<vector<int>> triangle(n);
    vector<vector<int>> result(n);
    fillVectorFromFile("triangle.txt", triangle);
    if (triangle.empty()) { 
        return 1; 
    }

    cout << "Initial Data: " << '\n' << '\n';
    printVector(triangle);

    fillVectorWithZero(result);
    Solver(triangle, result);
    cout << "Result: " << '\n' << '\n';
    printVector(result);

    vector<int> Path = Finder(result);
    // Flip the path so that it goes from the top to the bottom
    reverse(Path.begin(), Path.end());
    cout << "Path" << '\n';
    for (auto element : Path) {
        cout << element << " ";
    }
    cout << '\n' << '\n' << '\n';
	return 0;
}
