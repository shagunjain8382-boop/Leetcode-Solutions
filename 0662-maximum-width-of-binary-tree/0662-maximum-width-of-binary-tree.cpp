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
    int widthOfBinaryTree(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        queue<pair<TreeNode*, long long>> q;
        q.push({root, 0});

        int maxWidth = 0;

        while (!q.empty()) {
            int currLevelSize = q.size();

            long long startIndex = q.front().second;
            long long endIndex = q.back().second;

            maxWidth = max(maxWidth,
                           (int)(endIndex - startIndex + 1));

            for (int i = 0; i < currLevelSize; i++) {
                auto curr = q.front();
                q.pop();

                TreeNode* node = curr.first;
                long long index = curr.second - startIndex;

                if (node->left) {
                    q.push({node->left, index * 2 + 1});
                }

                if (node->right) {
                    q.push({node->right, index * 2 + 2});
                }
            }
        }

        return maxWidth;
    }
};
