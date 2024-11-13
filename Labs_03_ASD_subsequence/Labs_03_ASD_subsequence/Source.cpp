#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
//-------------------------------------------------------------------------
// Function for filling in a vector of characters from a file
void FillVectorFromFile(const string& filename, vector<char>& vec) {
	
    ifstream file(filename);

    if (file.is_open()) {
        char c;
        while (file.get(c)) {
            vec.push_back(c);
        }
        file.close();
    }
    else {
        cerr << "File opening error: " << filename << endl;
    }

}
// Function for creating a matrix of size sub1.size() x sub2.size()
// with zero values
void FillVector2d(vector<vector<int>>& vec, vector<char>& sub1, vector<char>& sub2) {
    for (int i = 0; i < sub1.size(); ++i) {
        vector<int> row;
        for (int j = 0; j < sub2.size(); ++j) {
            row.push_back(0);
        }
        vec.push_back(row);
    }
}
void PrintString(vector<char>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << '\n' << '\n' << "\n";
}
void PrintVector2d(vector<vector<int>>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n' << '\n' << "\n";
}
// Function for calculating the distance matrix
// THE NEEDLEMAN-WUNSCH ALGORITHM
void Solver(vector<vector<int>>& matrix, vector<char>& vecStr1, vector<char>& vecStr2) {
    // Filling the bottom row with units
    for (int i = 0; i < vecStr2.size(); i++) {
        if (vecStr1[0] == vecStr2[i]) {
            for (int j = i; j < vecStr2.size(); j++) {
                matrix[0][j] = 1;
            }
            // Exit the loop after the first match
            break;
        }
    }

    // Filling in the only 1 column
    for (int i = 0; i < vecStr1.size(); i++) {
        if (vecStr2[0] == vecStr1[i]) {
            for (int j = i; j < vecStr1.size(); j++) {
                matrix[j][0] = 1;
            }
            // Exit the loop after the first match
            break;
        }
    }

    // Filling the remaining table with values
    for (int i = 1; i < matrix.size(); i++) {
        for (int j = 1; j < matrix[i].size(); j++) {
            if (vecStr1[i] == vecStr2[j]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            }
            else {
                matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);
            }
        }
    }
}
// Function for finding the longest common subsequence
vector<char> FindSubsequence(vector<vector<int>>& matrix, vector<char>& vecStr1, vector<char>& vecStr2) {
    vector<char> result;
    int i = matrix.size() - 1;
    int j = matrix[i].size() - 1;
    // Moving through the matrix from the end to the beginning, 
    // adding characters to the subsequence
    while (i > -1 && j > -1 && matrix[i][j] != 0) {
        // Add a character if it matches
        if (vecStr1[i] == vecStr2[j]) {
            result.push_back(vecStr1[i]);
            i--;
            j--;
        }
        else {
            // Choose the direction of movement according to the matrix,
            // where the value is greater
            if (matrix[i - 1][j] > matrix[i][j - 1]) {
                i--;
            }
            else {
                j--;    
            }
        }
    }
    return result;
}
//-------------------------------------------------------------------------
int main() {
	vector<char> sub1;
	vector<char> sub2;
    vector<vector<int>> MATRIX;
    cout << "There are two lines in your files: 1 - vertical in the matrix , 2 - horizontal in the matrix" << '\n' << '\n';
    FillVectorFromFile("string1.txt", sub1);
    FillVectorFromFile("string2.txt", sub2);

    // Checking for file opening errors
    if (sub1.empty() || sub2.empty()) {
        cerr << "Error: One or both lines were not read" << endl;
        return 1; 
    }
    cout << "First string: " << '\n' << '\n';
    PrintString(sub1);
    cout << "Second string: " << '\n' << '\n';
    PrintString(sub2);
    FillVector2d(MATRIX, sub1, sub2);
    Solver(MATRIX, sub1, sub2);
    cout << "The final matrix after the operation of the NEEDLEMAN-WUNSCH algorithm:" << '\n' << '\n';
    PrintVector2d(MATRIX);
    vector<char> result = FindSubsequence(MATRIX, sub1, sub2);
    reverse(result.begin(), result.end());
    cout << "The maximum matching common sub-chain:" << '\n';
    PrintString(result);
	return 0;
}




