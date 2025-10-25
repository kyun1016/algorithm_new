class Solution {
public:
    int totalMoney(int n) {
        static constexpr int DAY_MONEY[7] = {1, 3, 6, 10, 15, 21, 28};
        int ret = 0;
        int weekCount = n/7;
        int i = 0;
        for(i = 0; i<weekCount; ++i){
            ret += DAY_MONEY[6] + i * 7;
            n -= 7;
        }
        if(n != 0)
            ret += DAY_MONEY[n-1] + i * n;

        return ret;
    }
};