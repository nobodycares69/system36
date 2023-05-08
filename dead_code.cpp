#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

void extractVariables(const string& expr, unordered_set<string>& vars) {
    for (size_t i = 0; i < expr.size(); ++i) {
        if (isalpha(expr[i])) {
            vars.insert(string(1, expr[i]));
        }
    }
}

int main() {
    ifstream input_file("/home/vaishali_maam/spcc/input.txt");
    ofstream output_file("/home/vaishali_maam/spcc/output.txt");
    string line;

    vector<Operation> operations;
    unordered_set<string> used_vars;

    // Read input and parse lines
    while (getline(input_file, line)) {
        Operation op = parseLine(line);
        operations.push_back(op);
    }

    // Add the output variable (lhs of the last operation) to the used_vars set
    used_vars.insert(operations.back().lhs);
    extractVariables(operations.back().rhs, used_vars);

    // Iterate through the operations in reverse order
    for (auto it = operations.rbegin() + 1; it != operations.rend(); ++it) {
        // Check if the lhs of the current operation is in the used_vars set
        if (used_vars.find(it->lhs) != used_vars.end()) {
            extractVariables(it->rhs, used_vars);
        } else {
            // Mark the current operation as dead
            it->id = -1;
        }
    }

    // Iterate through the operations in the original order and output only the ones that are not marked as dead
    for (const Operation& op : operations) {
        if (op.id != -1 && used_vars.find(op.lhs) != used_vars.end()) {
            output_file << op.id << " " << op.lhs << " " << op.rhs << endl;
        }
    }

    input_file.close();
    output_file.close();

    return 0;
}