#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int reverse(int x) {
      
        bool isNeg = x < 0;
        
        int reversed = 0;
        
        x = abs(x);
        while( x > 0 ) {
            if (reversed > INT_MAX/10 || reversed < INT_MIN/10){
                return 0;
            }
            reversed *= 10;
            reversed += x % 10;
            x /=10;   
        }
                
        return isNeg ? -1*reversed : reversed;
        
    }
};

