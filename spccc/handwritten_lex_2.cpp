/*Write a program to design handwritten lexical analyzer using programming  language.
(Display numbers, identifier, preprocessor directives]*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>
#include<regex>

using namespace std;



// Preprocessor directives
unordered_set<string> directives{
    "#define", "#include", "#ifdef", "#ifndef", "#endif"};





// Returns true if the string is a preprocessor directive
bool is_directive(const string &str)
{
  return directives.count(str) > 0;
}
bool is_symbol(char c)
{
  return ( c == '~'  || c == ',' ||
          c == ';' || c == ':' || c == '(' || c == ')' || c == '[' ||
          c == ']' || c == '{' || c == '}' || c == '?' || c == '#'||c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
          c == '<' || c == '>' || c == '=' || c == '&' || c == '|' ||
          c == '!' || c == '^');
}


// Returns true if the string is a valid identifier
bool is_identifier(const string &str)
{
  if (!isalpha(str[0]) && str[0] != '_')
  {
    return false;
  }
  for (char c : str)
  {
    if (!isalnum(c) && c != '_')
    {
      return false;
    }
  }
  return true;
}

// Returns true if the string is a valid number
const regex number_regex(R"([-+]?\d*\.?\d+)");
bool is_number(const string &str)
{
  return regex_match(str, number_regex);
}

int main(int argc, char* argv[])
{
  // Open input file
  // ifstream input_file("input.txt");
  // if (!input_file)
  // {
  //   cerr << "Error: could not open input file" << endl;
  //   return 1;
  // }
  if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: could not open file " << argv[1] << endl;
        return 1;
    }

  // Loop through file, extracting tokens
  string token;
  char c;
  while (infile.get(c))
  {
    if (isspace(c) || is_symbol(c))
    {

      if (!token.empty())
      {
        // Determine token type and output
     
         if (is_directive(token))
        {
          cout << "Directive: " << token << endl;
        }
        else if (is_identifier(token))
        {
          cout << "Identifier: " << token << endl;
        }
        else if (is_number(token))
        {
          cout << "Number: " << token << endl;
        }
        else
        {
         continue;;
        }
        token.clear();
      }
      if (c == '#')
      {
        // Output preprocessor directive
        string directive;
        getline(infile, directive);
        cout << "Directive: " << token << directive << endl;
      }
     
      
    }
    else
    {
      token += c;
    }
  }
  // Output last token
if (!token.empty()) {
      if (is_directive(token)) {
        cout << "Directive: " << token << endl;
    } else if (is_identifier(token)) {
        cout << "Identifier: " << token << endl;
    } else if (is_number(token)) {
        cout << "Number: " << token << endl;
    }   
}

return 0;
}

