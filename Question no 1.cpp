#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

// Define a struct to hold each student record
struct Student {
    int id;
    string name;
    string date_birth;
    int roll_no;
    string department;
    string address;
    int age;
};

// Function to calculate age from date of birth
int calculateAge(const string& date_birth) {
    int day, month, year;
    sscanf(date_birth.c_str(), "%d/%d/%d", &day, &month, &year);

    time_t t = time(nullptr);
    tm* now = localtime(&t);

    int age = now->tm_year + 1900 - year;
    if (now->tm_mon + 1 < month || (now->tm_mon + 1 == month && now->tm_mday < day)) {
        age--;
    }

    return age;
}

// Function to read the CSV file and store records in a vector
vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    string line;
    // Assuming the first line is the header and we skip it
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        string temp;
        
        getline(ss, temp, ',');
        student.id = stoi(temp);
        
        getline(ss, student.name, ',');
        
        getline(ss, student.date_birth, ',');
        student.age = calculateAge(student.date_birth);
        
        getline(ss, temp, ',');
        student.roll_no = stoi(temp);
        
        getline(ss, student.department, ',');
        
        getline(ss, student.address, ',');
        
        students.push_back(student);
    }

    file.close();
    return students;
}

// Comparison function to sort by name
bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

// Comparison function to sort by age
bool compareByAge(const Student& a, const Student& b) {
    return a.age > b.age;
}

// Function to write the vector to a CSV file
void writeCSV(const string& filename, const vector<Student>& students) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Writing the header
    file << "id,name,date_birth,roll_no,department,address\n";

    for (const auto& student : students) {
        file << student.id << "," << student.name << "," << student.date_birth << ","
             << student.roll_no << "," << student.department << "," << student.address << "\n";
    }

    file.close();
}

int main() {
    string input_file = "D:\\Berojgari\\Treeleaf\\Book1.csv";
    string output_file_name = "D:\\Berojgari\\Treeleaf\\sorted_by_name.csv";
    string output_file_age = "D:\\Berojgari\\Treeleaf\\sorted_by_age.csv";

    // Read the CSV file
    vector<Student> students = readCSV(input_file);

    if (students.empty()) {
        cerr << "No data found or error reading data." << endl;
        return 1;
    }

    // Sort by name and write to a new CSV file
    sort(students.begin(), students.end(), compareByName);
    writeCSV(output_file_name, students);

    // Sort by age and write to another new CSV file
    sort(students.begin(), students.end(), compareByAge);
    writeCSV(output_file_age, students);

    cout << "Files have been written successfully." << endl;
    return 0;
}
