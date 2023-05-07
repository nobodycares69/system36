/*Remove comment*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char* argv[]) {
    // Check that the user has provided a filename as an argument
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    // Open the input file
    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: could not open file " << argv[1] << endl;
        return 1;
    }

    // Open the output file
    ofstream outfile(argv[2]);
    if (!outfile.is_open()) {
        cerr << "Error: could not open file " << argv[2] << endl;
        return 1;
    }

    string line;
    bool in_comment = false;

    // Read in the program line by line
    while (getline(infile, line)) {
        // Loop over each character in the line
        for (int i = 0; i < line.size(); i++) {
            // If we're not currently in a comment, check for the start of a comment
            if (!in_comment && line[i] == '/' && i < line.size() - 1 && line[i+1] == '*') {
                in_comment = true;
                i++;  // Skip the '*' character
            }
            // If we're currently in a comment, check for the end of the comment
            else if (in_comment && line[i] == '*' && i < line.size() - 1 && line[i+1] == '/') {
                in_comment = false;
                i++;  // Skip the '/' character
            }
            // If we're not in a comment and this character is not part of a comment, output it
            else if (!in_comment) {
                outfile << line[i];
            }
        }
        // Output a newline character after each line
        outfile << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
