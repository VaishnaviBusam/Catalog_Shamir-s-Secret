#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

struct Point {
    double x, y;
};

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

double lagrangeInterpolation(const vector<Point>& points) {
    int n = points.size();
    vector<double> xi(n), yi(n);

    for (int i = 0; i < n; i++) {
        xi[i] = points[i].x;
        yi[i] = points[i].y;
    }

    double f_0 = 0; 

    for (int i = 0; i < n; i++) {
        f_0 += yi[i] * lagrangeBasis(0, xi, i);
    }

    return f_0;  // Return the constant term
}

vector<Point> readPointsFromJson(const string& filename, int k) {
    vector<Point> points;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return points; 
    }

    while (getline(file, line)) {
        if (line.find("base") != string::npos) {
            size_t baseStart = line.find(":") + 1;
            size_t baseEnd = line.find(",", baseStart);
            string baseStr = line.substr(baseStart, baseEnd - baseStart);
            int base = stoi(baseStr);

            getline(file, line);
            size_t valueStart = line.find(":") + 1;
            size_t valueEnd = line.find(",", valueStart);
            string valueStr = line.substr(valueStart, valueEnd - valueStart);
            valueStr.erase(remove(valueStr.begin(), valueStr.end(), '\"'), valueStr.end()); // Remove quotes

            int y = convertToBase10(valueStr, base);

            points.push_back(Point{(double)(points.size() + 1), (double)y}); // Use points.size() + 1 as x
        }
        if (points.size() >= k) {
            break;
        }
    }

    return points;
}

int main() {
    string filename = "json_catalog.txt";  
    int k = 3;  // We are using 3 points (as given in the input)
    vector<Point> points = readPointsFromJson(filename, k);

    // Perform Lagrange interpolation to find f(0)
    double constantTerm = lagrangeInterpolation(points);
    cout << "The constant term (f(0)) is: " << constantTerm << endl;

    return 0;
}
