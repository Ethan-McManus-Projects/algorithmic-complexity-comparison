#include "c++Main.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>
#include "c++BinaryTreeNode.h"

using namespace std;

//hashmap is faster than loop because it has O(1) time complexity
vector<int> twoSumHash(const vector<int>& nums, int target) {
    unordered_map<int, int> hash_map;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (hash_map.find(complement) != hash_map.end()) {
            return {hash_map[complement], i};
        }
        hash_map[nums[i]] = i;
    }
    return {};
}

vector<int> twoSumLoop(const vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

//bubble is very slow, O(n^2)
vector<int> simpleSortBubble(const vector<int>& nums) {
    vector<int> sorted = nums;
    for (int i = 0; i < sorted.size(); i++) {
        for (int j = 0; j < sorted.size() - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    return sorted;
}


//insertion and selection are similar
vector<int> simpleSortInsertion(const vector<int>& nums) {
    vector<int> sorted = nums;
    for (int i = 1; i < sorted.size(); ++i) {
        int key = sorted[i];
        int j = i - 1;
        while (j >= 0 && sorted[j] > key) {
            sorted[j + 1] = sorted[j];
            --j;
        }
        sorted[j + 1] = key;
    }
    return sorted;
}

vector<int> simpleSortSelection(const vector<int>& nums) {
    vector<int> sorted = nums;
    for (int i = 0; i < sorted.size() - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < sorted.size(); ++j) {
            if (sorted[j] < sorted[min_index]) {
                min_index = j;
            }
        }
        swap(sorted[i], sorted[min_index]);
    }
    return sorted;
}

//mergesort has a helper function and is similar to quicksort in recursive nature
void merge(vector<int>& nums, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = nums[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = nums[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k] = L[i];
            ++i;
        } else {
            nums[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        nums[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        nums[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

vector<int> simpleSortMerge(const vector<int>& nums) {
    vector<int> sorted = nums;
    mergeSort(sorted, 0, sorted.size() - 1);
    return sorted;
}

int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (nums[j] < pivot) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }

    swap(nums[i + 1], nums[high]);
    return i + 1;
}

void quickSort(vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition(nums, low, high);
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}

vector<int> simpleSortQuick(const vector<int>& nums) {
    vector<int> sorted = nums;
    quickSort(sorted, 0, sorted.size() - 1);
    return sorted;
}

//simple merge of two arrays
vector<int> arrayMerge(vector<int>& nums1, const vector<int>& nums2, int length1, int length2) {
    int m = length1;
    int n = length2;

    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }

    return nums1;
}

//binary tree minimum depth search using dfs and bfs, shortest path to leaf node
int binaryTreeMinimumDepthDFS(BinaryTreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    stack<pair<BinaryTreeNode*, int>> node_stack;
    node_stack.push({root, 1});
    int min_depth = INT_MAX;

    while (!node_stack.empty()) {
        auto [node, depth] = node_stack.top();
        node_stack.pop();

        if (node->left == nullptr && node->right == nullptr) {
            min_depth = min(min_depth, depth);
        }

        if (node->right != nullptr) {
            node_stack.push({node->right, depth + 1});
        }
        if (node->left != nullptr) {
            node_stack.push({node->left, depth + 1});
        }
    }

    return min_depth;
}

int binaryTreeMinimumDepthBFS(BinaryTreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    queue<pair<BinaryTreeNode*, int>> node_queue;
    node_queue.push({root, 1});

    while (!node_queue.empty()) {
        auto [node, depth] = node_queue.front();
        node_queue.pop();

        if (node->left == nullptr && node->right == nullptr) {
            return depth;
        }

        if (node->left != nullptr) {
            node_queue.push({node->left, depth + 1});
        }
        if (node->right != nullptr) {
            node_queue.push({node->right, depth + 1});
        }
    }

    return 0;
}