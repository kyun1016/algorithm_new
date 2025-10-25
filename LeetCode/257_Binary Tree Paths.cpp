/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    struct data{
        TreeNode* node;
        string str;
    };
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        // Step 1. DFS 방식으로 데이터 처리
        stack<data> st;
        data curr;
        curr.node = root;
        curr.str = to_string(root->val);
        st.push(curr);
        while(!st.empty()) {
            curr = st.top();
            st.pop();

            data next;
            if(curr.node->left != nullptr){
                next.node = curr.node->left;
                next.str = curr.str + "->" + to_string(next.node->val);
                st.push(next);
            }
            if(curr.node->right != nullptr){
                next.node = curr.node->right;
                next.str = curr.str + "->" + to_string(next.node->val);
                st.push(next);
            }
            if(curr.node->left == nullptr && curr.node->right == nullptr)
                ret.emplace_back(curr.str);
        }

        return ret;
    }
};