class Solution {
public:
    bool hasSameDigits(string s) {
        // Step 1. 문자를 숫자로 효율적으로 변경
        for(auto& c: s)
            c -= '0';
        while(s.length() > 2) {
            for(int i=1; i<s.length(); ++i)
                s[i-1] = (s[i-1] + s[i]) % 10;
            s.pop_back();
        }
        if(s[0] == s[1])
            return true;
        return false;
    }
};