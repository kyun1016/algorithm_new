class Solution {
public:
    string finalString(string s) {
        string ret;
        ret.reserve(s.length());
        for(const auto& c: s) {
            if(c == 'i')
                reverse(ret.begin(), ret.end());
            else
                ret.push_back(c);
        }

        return ret;
    }
};