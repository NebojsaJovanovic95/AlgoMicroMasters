#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
 	bool success = true;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
         opening_brackets_stack.push(Bracket(next, position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
         if (opening_brackets_stack.empty() ) {
          cout << position + 1;
          success = false;
          break;
         }
         Bracket bracket = opening_brackets_stack.top();
         if (bracket.Matchc(next) ) {
          opening_brackets_stack.pop();
         } else {
          //report the position as an error
          cout << position + 1;
          success = false;
          break;
         }
        }
    }

    // Printing answer, write your code here
 	if (opening_brackets_stack.empty() && success) {
 	cout << "Success";
    } else if (success) {
     Bracket bracket = opening_brackets_stack.top();
     cout << bracket.position + 1;
    }
    return 0;
}
