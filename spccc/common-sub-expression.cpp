#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Struct to store the operations
struct Operation {
    int id;
    string lhs;
    string rhs;
};

// Function to parse the input line
Operation parseLine(const string& line) {
    Operation op;
    sscanf(line.c_str(), "%d", &op.id);

    size_t space1 = line.find(' ');
    size_t space2 = line.find(' ', space1 + 1);
    op.lhs = line.substr(space1 + 1, space2 - space1 - 1);
    op.rhs = line.substr(space2 + 1);

    return op;
}

int main() {
    ifstream input_file("/home/vaishali_maam/spcc/input.txt");
    ofstream output_file("/home/vaishali_maam/spcc/output.txt");
    string line;

    vector<Operation> operations;
    unordered_map<string, string> common_subexpression;

    // Read input and parse lines
    while (getline(input_file, line)) {
        Operation op = parseLine(line);
        operations.push_back(op);
    }

    // Process the operations
    for (const Operation& op : operations) {
        // Check if the rhs already exists in the common_subexpression map
        auto it = common_subexpression.find(op.rhs);
        if (it != common_subexpression.end()) {
            // Common subexpression found, but only eliminate if lhs is different
            if (it->second != op.lhs) {
                common_subexpression[op.lhs] = it->second;
            } else {
                // If lhs is the same, add the current rhs to the map and output the operation
                common_subexpression[op.lhs] = op.rhs;
                output_file << op.id << " " << op.lhs << " " << op.rhs << endl;
            }
        } else {
            // No common subexpression found, add the current rhs to the map
            common_subexpression[op.rhs] = op.lhs;

            // Write the operation to the output file
            output_file << op.id << " " << op.lhs << " " << op.rhs << endl;
        }
    }

    input_file.close();
    output_file.close();

    return 0;
}