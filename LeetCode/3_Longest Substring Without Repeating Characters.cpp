class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int lo = 0;
        int hi = 0;
        int ret = 0;
        vector<bool> visited(1000, false);
        for (hi = 0; hi < s.size(); ++hi) {
            if (!visited[s[hi]])
                ret = ret > (hi - lo + 1) ? ret : (hi - lo + 1);
            else
                while (visited[s[hi]])
                    visited[s[lo++]] = false;
            visited[s[hi]] = true;
        }

        return ret;
    }
};