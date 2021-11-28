class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0) return false;
        int num=x, reversed=0, digito=0; 
        while(num!=0){
            digito= num%10;
            try{
                if(reversed > INT_MAX/10) throw -1;
                reversed = (reversed * 10) + digito;
            }catch(int e){
                return false;
            }
            num= num/10;
        }
        
        if(x ==reversed) return true;
        return false;
    }
};