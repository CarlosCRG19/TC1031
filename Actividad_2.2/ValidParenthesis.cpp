#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isOpening(char symbol) {
        return (symbol == '(' || symbol == '{' || symbol == '[');
    }

    bool isClosing(char symbol) {
        return (symbol == ')' || symbol == '}' || symbol == ']');
    }

    char getOpening(char closingSymbol){
        switch(closingSymbol){
            case '}':
                return '{';
            case ']':
                return '[';
            case ')':
                return '(';
            default:
                return '_';
        }
    }

    bool isValid(string s) {
        stack<char> myStack;

        if (s.length() < 2) {
            return false;
        }

        int i=0;
        while(i < s.length()) {
            if(isOpening(s[i])) {
                myStack.push(s[i]);
            } else {
                if(myStack.empty() || getOpening(s[i]) != myStack.top()) {
                    return false;
                } 
                myStack.pop();
            }
            i++;
        }

        return myStack.empty();
    }
};