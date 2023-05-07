#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>

using namespace std;

// Define a struct to hold quadruple information
struct Quadruple {
    string op;
    string arg1;
    string arg2;
    string result;
};

// Define a struct to hold triple information
struct Triple {
    string op;
    string arg1;
    string arg2;
};

// Define a function to generate three-address code from a postfix expression
vector<Quadruple> generateQuadruples(vector<string> postfix) {
    stack<string> s;
    vector<Quadruple> code;
    int temp_count = 0;
    for (string token : postfix) {
        if (isalnum(token[0])) {
            s.push(token);
        } else {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();
            string result = "t" + to_string(++temp_count);
            code.push_back({token, arg1, arg2, result});
            s.push(result);
        }
    }
    return code;
}

// Define a function to generate triples from a postfix expression
vector<Triple> generateTriples(vector<string> postfix) {
    stack<string> s;
    vector<Triple> code;
    for (string token : postfix) {
        if (isalnum(token[0])) {
            s.push(token);
        } else {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();
            code.push_back({token, arg1, arg2});
            s.push("t" + to_string(code.size()));
        }
    }
    return code;
}

// Define a function to generate three-address code from a postfix expression
string generateThreeAddressCode(vector<string> postfix) {
    stack<string> s;
    int temp_count = 0;
    for (string token : postfix) {
        if (isalnum(token[0])) {
            s.push(token);
        } else {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();
            string result = "t" + to_string(++temp_count);
            s.push(result);
            cout << result << " = " << arg1 << " " << token << " " << arg2 << endl;
        }
    }
    return s.top();
}

// Define a function to convert an infix expression to postfix notation
vector<string> infixToPostfix(string expression) {
    stack<char> s;
    vector<string> postfix;
    map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}};
    for (char c : expression) {
        if (isalnum(c)) {
            postfix.push_back(string(1, c));
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (s.top() != '(') {
                postfix.push_back(string(1, s.top()));
                s.pop();
            }
            s.pop(); // Pop the left parenthesis
        } else {
            while (!s.empty() && s.top() != '(' && precedence[c] <= precedence[s.top()]) {
                postfix.push_back(string(1, s.top()));
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix.push_back(string(1, s.top()));
        s.pop();
    }
    return postfix;
}

int main() {
    // Read in an arithmetic expression from the user
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    // Convert the expression to postfix notation
    vector<string> postfix = infixToPostfix(expression);
    // cout << "Postfix notation: ";
    // for (string token : postfix) {
    //     cout << token << " ";
    // }
    // cout << endl;

    // Generate and output the quadruples
    vector<Quadruple> quadruples = generateQuadruples(postfix);
    cout << "Quadruples:" << endl;
    for (Quadruple q : quadruples) {
        cout << "(" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.result << ")" << endl;
    }

    // Generate and output the triples
    vector<Triple> triples = generateTriples(postfix);
    cout << "Triples:" << endl;
    for (Triple t : triples) {
        cout << "(" << t.op << ", " << t.arg1 << ", " << t.arg2 << ")" << endl;
    }

    // Generate and output the three-address code
    cout << "Three-address code:" << endl;
    generateThreeAddressCode(postfix);

    return 0;
}

