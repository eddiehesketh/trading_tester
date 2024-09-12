#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    fstream new_file;
    

    // open a file to perform read operation using file object.
    new_file.open("test_file.txt", ios::in); 
    
    // Checking whether the file is open.
    if (new_file.is_open()) { 
        string sa;
        // Read data from the file object and put it into a string.
        while (std::getline(new_file, sa)) { 
            // Print the data of the string.
            cout << sa << "\n"; 
        }
        
        // Close the file object.
        new_file.close(); 
    }
}