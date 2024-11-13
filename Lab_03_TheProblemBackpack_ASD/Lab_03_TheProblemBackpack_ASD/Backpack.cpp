#include <iostream>;
#include <vector>;
#include <fstream>
#include <algorithm>
using namespace std;
void fillVectorFromFile(const string& filename, vector<vector<int>>& vec) {
    ifstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < vec.size(); i++) {
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
void fillVectorWithZeros(vector<vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            vec[i][j] = 0;
        }
    }
}
void printVector(vector<vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            printf("%3d", vec[i][j]);
        }
        cout << '\n';
    }
    cout << '\n';
}
void SolverBackpackProblem(vector<vector<int>>& vecBackpack, vector<vector<int>>& vecThings) {
    for (int i = 2; i < vecBackpack.size(); i++) {
        for (int j = 2; j < vecBackpack[i].size(); j++) {
            // if the weight of the item is greater than the current possible, then
            if (j <= vecThings[1][i-2]) {
                vecBackpack[i][j] = vecBackpack[i - 1][j];
            }
            // otherwise, we choose a maximum of 2 options
            else {
                vecBackpack[i][j] = max(vecBackpack[i - 1][j], vecBackpack[i - 1][j - vecThings[1][i-2]] + vecThings[2][i-2]);
            }
        }
    }
}
vector<int> FindAvailableThings(vector<vector<int>>& vecBackpack, vector<vector<int>>& vecThings) {
    vector<int> numbers;
    int i = vecBackpack.size() - 1;
    int j = vecBackpack[i].size() - 1;
    while (i > 1 && j > 1) {
        if (vecBackpack[i][j] == vecBackpack[i - 1][j]) {
            i--;
        }
        else {
            numbers.push_back(i-1);
            j = j - vecThings[1][i-2];
            i--;
        }
    }
    return numbers;
}

// w[k] = vecThings[1][i-2] - the weight of the item
// p[k] = vecThings[2][i-2] - the value of a thing
// [i-2] - item number
//-------------------------------------------------------------------------

int main() {
    /*
    int n = 3;

    int m = 9;
    // k - number of items
    int k = 9 + 2;
    // w - maximum capacity of the backpack
    int w = 45 + 2;
    */

    int n = 3;
    int m, k, w;

    cout << "Enter the number of items (m > 0, integer): " << '\n';
    while (!(cin >> m) || m <= 0) {
        cout << "Error: Incorrect input. Enter an integer greater than 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    k = m + 2;

    cout << "Enter the capacity of the backpack (w > 0, integer): ";
    while (!(cin >> w) || w <= 0) {
        cout << "Error: Incorrect input. Enter an integer greater than 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    w = w + 2;

    vector<vector<int>> things(n, vector<int>(m));
    vector<vector<int>> backpack(k, vector<int>(w));

    fillVectorFromFile("things.txt", things);
    if (things.empty()) {
        return 1;
    }
    fillVectorWithZeros(backpack);

    for (int i = 2; i < backpack.size(); i++) {
        for (int j = 0; j < backpack[i].size(); j++) {
            backpack[i][0] = i - 1;
        }
    }
    for (int i = 0; i < backpack.size(); i++) {
        for (int j = 2; j < backpack[i].size(); j++) {
            backpack[0][j] = j - 1;
        }
    }
    cout << "The matrix of things:" << '\n';
    cout << "Line 1 - item numbers" << '\n';
    cout << "Line 2 - the capacity of the elements" << '\n';
    cout << "Line 3 - the value of the elements" << '\n';
    printVector(things);

    SolverBackpackProblem(backpack, things);
    cout << "Backpack matrix:" << '\n';
    printVector(backpack);

    vector<int> result = FindAvailableThings(backpack, things);

    reverse(result.begin(), result.end());
    cout << "Numbers of available items:" << endl; 
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}