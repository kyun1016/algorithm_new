class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int last = -100000;
        int last2 = -100000;
        int cnt = 0;
        for(const auto& num: nums)
        {
            if(last > num){
                cnt++;
                // case 1. 현재 숫자를 이전 값과 동일한 값으로 치환 
                if(last2 > num)
                    last = last;
                // case 2. 현재 값을 last 값으로 치환
                else{
                    last = num;
                    last2 = num;
                }
                    
            }
            else{
                last2 = last;
                last = num;
            }
        }
        
        if(cnt < 2)
            return true;
        return false;
    }
};