/* Write a program to design handwritten lexical analyzer using programming  language.
(Display keyword, identifier, symbols] */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>
#include<regex>

using namespace std;

// Keywords
unordered_set<string> keywords{
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"};






// Returns true if the character is a symbol
bool is_symbol(char c)
{
  return ( c == '~'  || c == ',' ||
          c == ';' || c == ':' || c == '(' || c == ')' || c == '[' ||
          c == ']' || c == '{' || c == '}' || c == '?' || c == '#'||c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
          c == '<' || c == '>' || c == '=' || c == '&' || c == '|' ||
          c == '!' || c == '^');
}

// Returns true if the string is a keyword
bool is_keyword(const string &str)
{
  return keywords.count(str) > 0;
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
        if (is_keyword(token))
        {
          cout << "Keyword: " << token << endl;
        }
  
        else if (is_identifier(token))
        {
          cout << "Identifier: " << token << endl;
        }

        else
        {
          cout << "Symbol:" << token << endl;
        }
        token.clear();
      }
      
       if (is_symbol(c))
      {
        // Output symbol
        cout << "Symbol: " << c << endl;
      }
      
    }
    else
    {
      token += c;
    }
  }
  // Output last token
if (!token.empty()) {
    if (is_keyword(token)) {
        cout << "Keyword: " << token << endl;
    } else if (is_identifier(token)) {
        cout << "Identifier: " << token << endl;
    }  else {
        cout << "Symbol: " << token << endl;
    }
}

return 0;
}

