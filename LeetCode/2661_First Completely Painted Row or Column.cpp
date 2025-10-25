class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        // Step 1. 빠른 탐색을 위해 num -> {col, row} 반환 배열 설계
        int size_col = mat.size();
        int size_row = mat[0].size();
        unordered_map<int, pair<int, int>> um;
        for(int i=0; i<size_col; ++i){
            for(int j=0; j<size_row; ++j)
                um[mat[i][j]] = {i, j};
        }

        // Step 2. 앞 단계부터 하나씩 카운팅 시작
        vector<int> rows(size_row, 0);
        vector<int> cols(size_col, 0);

        for(int i=0; i<arr.size(); ++i) {
            if(++cols[um[arr[i]].first] == size_row)
                return i;
            if(++rows[um[arr[i]].second] == size_col)
                return i;
        }

        return -1;
    }
};