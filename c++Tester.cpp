#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <tuple>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include "c++Main.h"
#include "c++BinaryTreeNode.h"

using namespace std;

class Tester {
public:
    // generate test cases for two sum
    static vector<tuple<vector<int>, int, vector<int>>> generate_two_sum_test_cases(int num_cases = 10000) {
        vector<tuple<vector<int>, int, vector<int>>> test_cases;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist_length(2, 100);
        uniform_int_distribution<long long> dist_value(-1000000000LL, 1000000000LL);

        for (int i = 0; i < num_cases; ++i) {
            int length = dist_length(gen);
            unordered_set<long long> unique_values;
            vector<int> nums;

            // generate unique numbers
            while (nums.size() < length) {
                long long num = dist_value(gen);
                if (unique_values.find(num) == unique_values.end()) {
                    unique_values.insert(num);
                    nums.push_back(num);
                }
            }

            // generate target number
            long long num1 = dist_value(gen);
            long long num2;
            do {
                num2 = dist_value(gen);
            } while (num1 == num2 || unique_values.find(num2) != unique_values.end());
            int target = num1 + num2;

            // remove pairs that add up to target
            for (auto it = nums.begin(); it != nums.end(); ) {
                bool found = false;
                for (auto jt = it + 1; jt != nums.end(); ++jt) {
                    if (*it + *jt == target) {
                        unique_values.erase(*it);
                        unique_values.erase(*jt);
                        jt = nums.erase(jt);
                        it = nums.erase(it);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    ++it;
                }
            }

            nums.erase(remove(nums.begin(), nums.end(), num1), nums.end());
            nums.erase(remove(nums.begin(), nums.end(), num2), nums.end());
            nums.push_back(num1);
            nums.push_back(num2);
            shuffle(nums.begin(), nums.end(), gen);

            int index1 = find(nums.begin(), nums.end(), num1) - nums.begin();
            int index2 = find(nums.begin(), nums.end(), num2) - nums.begin();

            test_cases.push_back({nums, target, {min(index1, index2), max(index1, index2)}});
        }
        return test_cases;
    }

    // generate test cases for sorting
    static vector<tuple<vector<int>, vector<int>>> generate_sort_test_cases(int num_cases = 10000) {
        vector<tuple<vector<int>, vector<int>>> test_cases;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist_length(1, 300);
        uniform_int_distribution<long long> dist_value(-1000000000LL, 1000000000LL);

        for (int i = 0; i < num_cases; ++i) {
            int length = dist_length(gen);
            vector<int> nums(length);
            for (int& num : nums) {
                num = dist_value(gen);
            }
            vector<int> sorted_nums = nums;
            sort(sorted_nums.begin(), sorted_nums.end());
            test_cases.push_back({nums, sorted_nums});
        }
        return test_cases;
    }

    // generate test cases for array merge
    static vector<tuple<vector<int>, vector<int>, vector<int>, int, int>> generate_array_merge_test_cases(int num_cases = 10000) {
        vector<tuple<vector<int>, vector<int>, vector<int>, int, int>> test_cases;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist_length(1, 1000);
        uniform_int_distribution<long long> dist_value(-1000000000LL, 1000000000LL);

        for (int i = 0; i < num_cases; ++i) {
            int length1 = dist_length(gen);
            int length2 = dist_length(gen);

            vector<int> nums1(length1 + length2, 0);
            unordered_set<int> unique_values;
            for (int j = 0; j < length1; ++j) {
                int num;
                do {
                    num = dist_value(gen);
                } while (unique_values.find(num) != unique_values.end());
                unique_values.insert(num);
                nums1[j] = num;
            }

            sort(nums1.begin(), nums1.begin() + length1);

            vector<int> nums2(length2);
            for (int& num : nums2) {
                do {
                    num = dist_value(gen);
                } while (unique_values.find(num) != unique_values.end());
                unique_values.insert(num);
            }

            sort(nums2.begin(), nums2.end());

            vector<int> solution = nums1;
            solution.insert(solution.end(), nums2.begin(), nums2.end());

            auto start = solution.begin() + length1;
            auto end = solution.begin() + length1 + length2;
            solution.erase(remove(start, end, 0), end);

            sort(solution.begin(), solution.end());

            test_cases.push_back({nums1, nums2, solution, length1, length2});
        }
        return test_cases;
    }

    // generate test cases for minimum binary tree depth
    static vector<tuple<BinaryTreeNode*, int>> generate_minimum_binary_tree_depth_test_cases(int num_cases = 10000, int max_depth = 1500) {
        vector<tuple<BinaryTreeNode*, int>> test_cases;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist_depth(2, max_depth);
        uniform_int_distribution<> dist_choice(0, 1);

        for (int i = 0; i < num_cases; ++i) {
            BinaryTreeNode* root = new BinaryTreeNode(1);
            int min_depth = dist_depth(gen);

            vector<BinaryTreeNode*> current_level_nodes = {root};

            for (int depth = 2; depth <= min_depth; ++depth) {
                vector<BinaryTreeNode*> next_level_nodes;
                for (BinaryTreeNode* node : current_level_nodes) {
                    node->insertLeft(depth);
                    next_level_nodes.push_back(node->left);
                }
                current_level_nodes = next_level_nodes;
            }

            BinaryTreeNode* leaf_node = current_level_nodes[0];
            if (dist_choice(gen)) {
                leaf_node->insertLeft(min_depth);
            } else {
                leaf_node->insertRight(min_depth);
            }

            current_level_nodes.clear();

            int current_depth = min_depth + 1;
            while (current_depth <= max_depth) {
                vector<BinaryTreeNode*> next_level_nodes;
                for (BinaryTreeNode* node : current_level_nodes) {
                    if (dist_choice(gen)) {
                        node->insertLeft(current_depth);
                        next_level_nodes.push_back(node->left);
                    }
                    if (dist_choice(gen)) {
                        node->insertRight(current_depth);
                        next_level_nodes.push_back(node->right);
                    }
                }
                current_level_nodes = next_level_nodes;
                current_depth++;

                if (current_level_nodes.empty()) break;
            }

            test_cases.push_back({root, min_depth + 1});
        }

        return test_cases;
    }
    
    static void run_sort_tests(const vector<tuple<vector<int>, vector<int>>>& test_cases, vector<int> (*sort_func)(const vector<int>&), const string& func_name) {
        int passed_cases = 0;

        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < test_cases.size(); ++i) {
            const auto& [nums, expected] = test_cases[i];
            auto sorted = sort_func(nums);

            if (sorted == expected) {
                passed_cases++;
            } else {
                cout << "Test case " << i + 1 << " failed:\n";
                cout << "  Input: ";
                for (const auto& num : nums) cout << num << " ";
                cout << "\n  Expected: ";
                for (const auto& num : expected) cout << num << " ";
                cout << "\n  Sorted: ";
                for (const auto& num : sorted) cout << num << " ";
                cout << "\n";
                break;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "\nFunction: " << func_name << "\n";
        cout << "Passed " << passed_cases << " out of " << test_cases.size() << " test cases.\n";
        cout << "Total time taken: " << elapsed.count() << " seconds\n";
        cout << "Average time per test case: " << (elapsed.count() / test_cases.size()) << " seconds\n";
    }

    static void two_sum_run_tests(const vector<tuple<vector<int>, int, vector<int>>>& test_cases, vector<int> (*two_sum_func)(const vector<int>&, int), const string& func_name) {
        int passed_cases = 0;

        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < test_cases.size(); ++i) {
            const auto& [nums, target, expected] = test_cases[i];
            auto result = two_sum_func(nums, target);

            if (!result.empty() && ((result[0] == expected[0] && result[1] == expected[1]) ||
                (result[0] == expected[1] && result[1] == expected[0]))) {
                passed_cases++;
            } else {
                cout << "Test case " << i + 1 << " failed:\n";
                cout << "  Target: " << target << "\n";
                cout << "  Expected indexes: [" << expected[0] << ", " << expected[1] << "] with values: [" 
                    << nums[expected[0]] << ", " << nums[expected[1]] << "]\n";
                if (!result.empty()) {
                    cout << "  Found indexes: [" << result[0] << ", " << result[1] << "] with values: [" 
                        << nums[result[0]] << ", " << nums[result[1]] << "]\n";
                } else {
                    cout << "  No result found\n";
                }
                break;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "\nFunction: " << func_name << "\n";
        cout << "Passed " << passed_cases << " out of " << test_cases.size() << " test cases.\n";
        cout << "Total time taken: " << elapsed.count() << " seconds\n";
        cout << "Average time per test case: " << (elapsed.count() / test_cases.size()) << " seconds\n";
    }

    static void run_array_merge_tests(const vector<tuple<vector<int>, vector<int>, vector<int>, int, int>>& test_cases, vector<int> (*merge_func)(vector<int>&, const vector<int>&, int, int), const string& func_name) {
        int passed_cases = 0;

        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < test_cases.size(); ++i) {
            auto [array1, array2, expected, length1, length2] = test_cases[i];
            auto result = merge_func(array1, array2, length1, length2);

            if (result == expected) {
                passed_cases++;
            } else {
                cout << "Test case " << i + 1 << " failed:\n";
                cout << "  Input Array 1: ";
                for (const auto& num : array1) cout << num << " ";
                cout << "\n  Input Array 2: ";
                for (const auto& num : array2) cout << num << " ";
                cout << "\n  Expected: ";
                for (const auto& num : expected) cout << num << " ";
                cout << "\n  Result: ";
                for (const auto& num : result) cout << num << " ";
                cout << "\n";
                break;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "\nFunction: " << func_name << "\n";
        cout << "Passed " << passed_cases << " out of " << test_cases.size() << " test cases.\n";
        cout << "Total time taken: " << elapsed.count() << " seconds\n";
        cout << "Average time per test case: " << (elapsed.count() / test_cases.size()) << " seconds\n";
    }

    static void run_minimum_binary_tree_depth_tests(const vector<tuple<BinaryTreeNode*, int>>& test_cases, int (*minDepth)(BinaryTreeNode*), const string& func_name) {
        int passed_cases = 0;

        auto start = chrono::high_resolution_clock::now();

        for (size_t i = 0; i < test_cases.size(); ++i) {
            auto [root, expected] = test_cases[i];
            int result = minDepth(root);

            if (result == expected) {
                passed_cases++;
            } else {
                cout << "Test case " << i + 1 << " failed:\n";
                cout << "  Expected: " << expected << "\n";
                cout << "  Result: " << result << "\n";
                cout << "Test Case " << i + 1 << ", Calculated Depth (BFS) = " << binaryTreeMinimumDepthBFS(root) << endl;
                break;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "\nFunction: " << func_name << "\n";
        cout << "Passed " << passed_cases << " out of " << test_cases.size() << " test cases.\n";
        cout << "Total time taken: " << elapsed.count() << " seconds\n";
        cout << "Average time per test case: " << (elapsed.count() / test_cases.size()) << " seconds\n";
    }

    int validateMinimumDepth(BinaryTreeNode* root) {
        return binaryTreeMinimumDepthBFS(root);
    }
};

int main() {
    auto test_cases = Tester::generate_two_sum_test_cases();

    cout << "Testing two_sum_hash:\n";
    Tester::two_sum_run_tests(test_cases, twoSumHash, "two_sum_hash");

    cout << "\nTesting two_sum_loop:\n";
    Tester::two_sum_run_tests(test_cases, twoSumLoop, "two_sum_loop");

    auto sort_test_cases = Tester::generate_sort_test_cases();

    cout << "\nTesting simpleSortBubble:\n";
    Tester::run_sort_tests(sort_test_cases, simpleSortBubble, "simpleSortBubble");

    cout << "\nTesting simpleSortMerge:\n";
    Tester::run_sort_tests(sort_test_cases, simpleSortMerge, "simpleSortMerge");

    cout << "\nTesting simpleSortQuick:\n";
    Tester::run_sort_tests(sort_test_cases, simpleSortQuick, "simpleSortQuick");

    cout << "\nTesting simpleSortInsertion:\n";
    Tester::run_sort_tests(sort_test_cases, simpleSortInsertion, "simpleSortInsertion");

    cout << "\nTesting simpleSortSelection:\n";
    Tester::run_sort_tests(sort_test_cases, simpleSortSelection, "simpleSortSelection");

    auto array_merge_test_cases = Tester::generate_array_merge_test_cases();

    cout << "\nTesting array merge problem:\n";
    Tester::run_array_merge_tests(array_merge_test_cases, arrayMerge, "arrayMerge");

    auto binary_tree_test_cases = Tester::generate_minimum_binary_tree_depth_test_cases();

    cout << "\nTesting BFS:\n";
    Tester::run_minimum_binary_tree_depth_tests(binary_tree_test_cases, binaryTreeMinimumDepthBFS, "binaryTreeMinimumDepthBFS");

    cout << "\nTesting DFS:\n";
    Tester::run_minimum_binary_tree_depth_tests(binary_tree_test_cases, binaryTreeMinimumDepthDFS, "binaryTreeMinimumDepthDFS");

    system("pause");

    return 0;
}