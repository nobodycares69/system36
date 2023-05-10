// Code for pretty much all 2-pass, just remove print statements and you are
// good to go.
// I did not go single code, that makes it hard to understand.

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

struct Symbol {
    string name;
    int value;
    int length;
    string relocation;
};

struct Operand {
    string mnemonic;
    map<string, string> properties;
};

map<string, Symbol> symbol_table;
map<string, string> literal_table;
map<string, int> base_table;
vector<int> lc_table;
vector<string> machine_code;

map<string, Operand> mot = {
        {"MOV", {"MOV", {{"binary_op", "01"}, {"ins_length", "3"}, {"ins_format", "R"}}}},
        {"SUB", {"SUB", {{"binary_op", "02"}, {"ins_length", "3"}, {"ins_format", "R"}}}},
        {"CMP", {"CMP", {{"binary_op", "03"}, {"ins_length", "3"}, {"ins_format", "R"}}}},
        {"BNE", {"BNE", {{"binary_op", "04"}, {"ins_length", "3"}, {"ins_format", "I"}}}},
        {"HALT", {"HALT", {{"binary_op", "05"}, {"ins_length", "1"}, {"ins_format", "I"}}}}
};

map<string, string> pot = {{"START", "S1"}, {"END", "S2"}};

vector<string> assembly_code = {
        "START:  MOV R0, =10",
        "LOOP:   SUB R0, #1",
        "        CMP R0, #0",
        "        BNE LOOP",
        "        HALT"
};

void first_pass() {
    int lc = 0;

    for (const auto &line : assembly_code) {
        lc_table.push_back(lc);
        int label_end = line.find(':');

        if (label_end != string::npos) {
            string symbol_name = line.substr(0, label_end);
            Symbol symbol = {symbol_name, lc, 1, "R"};
            symbol_table[symbol_name] = symbol;
            base_table[symbol_name] = lc;
        }

        int literal_start = line.find('=');

        if (literal_start != string::npos) {
            string literal = line.substr(literal_start + 1);
            if (literal_table.find(literal) == literal_table.end()) {
                literal_table[literal] = to_string(lc);
            }
        }

        lc++;
    }
}

void print_symbol_table() {
    cout << "Symbol Table:" << endl;
    cout << setw(10) << "Symbol" << setw(10) << "Value" << setw(10) << "Length" << setw(15) << "Relocation" << endl;

    for (const auto &entry : symbol_table) {
        const Symbol &symbol = entry.second;
        cout << setw(10) << symbol.name << setw(10) << symbol.value << setw(10) << symbol.length << setw(15) << symbol.relocation << endl;
    }
}

void print_literal_table() {
    cout << "Literal Table:" << endl;
    for (const auto &literal : literal_table) {
        cout << literal.first << " => " << literal.second << endl;
    }
}

void print_base_table() {
    cout << "Base Table:" << endl;
    for (const auto &base : base_table) {
        cout << base.first << " => " << base.second << endl;
    }
}

void print_lc_table() {
    cout << "Location Counter (LC) Table:" << endl;
    for (size_t i = 0; i < lc_table.size(); ++i) {
        cout << "Line " << i << ": " << lc_table[i] << endl;
    }
}

void print_mot() {
    cout << "Machine Opcode Table (MOT):" << endl;
    cout << setw(10) << "Mnemonic" << setw(15) << "Binary Op" << setw(15) << "Instruction Length" << setw(15) << "Instruction Format" << endl;

    for (const auto &entry : mot) {
        const string &mnemonic = entry.first;
        const Operand &operand = entry.second;
        cout << setw(10) << mnemonic;
        for (const auto &property : operand.properties) {
            cout << setw(15) << property.second;
        }
        cout << endl;
    }
}

void print_pot() {
    cout << "Pseudo Opcode Table (POT):" << endl;
    cout << setw(10) << "Mnemonic" << setw(15) << "Opcode" << endl;
    for (const auto &entry : pot) {
        cout << setw(10) << entry.first << setw(15) << entry.second << endl;
    }
}



void second_pass() {
    for (const auto &line : assembly_code) {
        stringstream ss(line);
        string opcode, operand;
        ss >> opcode >> operand;

        if (opcode == "MOV") {
            string reg, value;
            stringstream op_ss(operand);
            getline(op_ss, reg, ',');
            getline(op_ss, value);

            if (value.find('=') != string::npos) {
                value = value.substr(1);
                machine_code.push_back("MOV " + reg + " " + literal_table[value]);
            } else {
                machine_code.push_back("MOV " + reg + " " + value);
            }
        } else if (opcode == "SUB") {
            machine_code.push_back("SUB " + operand);
        } else if (opcode == "CMP") {
            machine_code.push_back("CMP " + operand);
        } else if (opcode == "BNE") {
            machine_code.push_back("BNE " + symbol_table[operand].value);
        } else if (opcode == "HALT") {
            machine_code.emplace_back("HALT");
        }
    }
}

void print_machine_code() {
    cout << "Machine Code:" << endl;
    for (const auto &code : machine_code) {
        cout << code << endl;
    }
}

int main() {
    first_pass();

    cout << "First pass complete." << endl << endl;
    print_symbol_table();
    cout << endl;
    print_literal_table();
    cout << endl;
    print_base_table();
    cout << endl;
    print_lc_table();
    cout << endl;
    print_mot();
    cout << endl;
    print_pot();
    cout << endl;

//    second_pass();
//
//    cout << "Second pass complete." << endl << endl;
//    print_machine_code();

    return 0;
}