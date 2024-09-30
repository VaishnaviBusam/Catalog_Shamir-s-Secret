#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

// Point struct to represent each point with x and y coordinates
struct Point {
    double x, y;
};

// Function to convert a string from any base to base 10
int convertToBase10(const string& value, int base) {
    int result = 0;
    int power = 0;

    for (int i = value.length() - 1; i >= 0; i--) {
        int digit = (value[i] >= '0' && value[i] <= '9') ? value[i] - '0' : value[i] - 'A' + 10;
        result += digit * pow(base, power);
        power++;
    }

    return result;
}

// Function to calculate the Lagrange basis polynomial for a given point
double lagrangeBasis(double x, const vector<double>& xi, int i) {
    double numerator = 1;
    double denominator = 1;

    for (int j = 0; j < xi.size(); j++) {
        if (j != i) {
            numerator *= (x - xi[j]);
            denominator *= (xi[i] - xi[j]);
        }
    }

    return numerator / denominator;
}

// Function to perform Lagrange interpolation and compute f(0)
double lagrangeInterpolation(const vector<Point>& points) {
    int n = points.size();
    vector<double> xi(n), yi(n);

    // Extract x and y values from the points
    for (int i = 0; i < n; i++) {
        xi[i] = points[i].x;
        yi[i] = points[i].y;
    }

    double f_0 = 0;  // This will store f(0), the constant term

    // Calculate f(0) using the Lagrange interpolation formula
    for (int i = 0; i < n; i++) {
        f_0 += yi[i] * lagrangeBasis(0, xi, i);
    }

    return f_0;  // Return the constant term
}

// Function to read points from the JSON file and extract points manually
vector<Point> readPointsFromJson(const string& filename, int k) {
    vector<Point> points;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return points; // Return empty points if file cannot be opened
    }

    // Read through the JSON file line by line
    while (getline(file, line)) {
        // Find the lines that contain the points
        if (line.find("base") != string::npos) {
            // Extract base value
            size_t baseStart = line.find(":") + 1;
            size_t baseEnd = line.find(",", baseStart);
            string baseStr = line.substr(baseStart, baseEnd - baseStart);
            int base = stoi(baseStr);

            // Read the next line for value
            getline(file, line);
            size_t valueStart = line.find(":") + 1;
            size_t valueEnd = line.find(",", valueStart);
            string valueStr = line.substr(valueStart, valueEnd - valueStart);
            valueStr.erase(remove(valueStr.begin(), valueStr.end(), '\"'), valueStr.end()); // Remove quotes

            // Convert the value to base 10
            int y = convertToBase10(valueStr, base);

            // Store the point (x = i, y = converted value)
            points.push_back(Point{(double)(points.size() + 1), (double)y}); // Use points.size() + 1 as x
        }
        // Stop reading after k points
        if (points.size() >= k) {
            break;
        }
    }

    return points;
}

int main() {
    // Read points from the JSON file
    string filename = "points.json";  // Path to your JSON file
    int k = 3;  // We are using 3 points (as given in the input)
    vector<Point> points = readPointsFromJson(filename, k);

    // Perform Lagrange interpolation to find f(0)
    double constantTerm = lagrangeInterpolation(points);
    cout << "The constant term (f(0)) is: " << constantTerm << endl;

    return 0;
}
