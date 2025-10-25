class Solution {
public:
    int nextBeautifulNumber(int n) {
        // Step 1. 모든 초기 배열 생성
        vector<vector<int>> list;
        for(int i=1; i<8; ++i) {
            vector<int> arr(i, i);
            list.emplace_back(arr);
        }
        // Step 2. 배열 조합 생성
        vector<vector<int>> merge_list;
        for(const auto& vec1: list)
        {
            const int count = merge_list.size();
            for(int i=0; i<count; ++i)
            {
                const auto& vec2 = merge_list[i];
                vector<int> merged;
                merged.reserve(vec1.size() + vec2.size());
                merged.insert(merged.end(), vec1.begin(), vec1.end());
                merged.insert(merged.end(), vec2.begin(), vec2.end());
                if(merged.size() < 8)
                    merge_list.emplace_back(merged);
            }
            merge_list.emplace_back(vec1);
        }

        // Step 3. 배열을 숫자로 치환
        set<int> num_list;
        for(auto& vec: merge_list)
        {
            sort(vec.begin(), vec.end());
            do {
                int sum = 0;
                for (const auto& num: vec) 
                {
                    sum = sum*10 + num;
                }
                num_list.insert(sum);
            } while (next_permutation(vec.begin(), vec.end()));
        }

        // Step 4. 결과 출력
        for(const auto& num: num_list)
        {
            if(num > n)
                return num;
        }

        return -1;
    }
};