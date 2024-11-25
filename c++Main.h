#ifndef CPP_MAIN_H
#define CPP_MAIN_H

#include <vector>
#include "c++BinaryTreeNode.h"

using namespace std;

vector<int> twoSumHash(const vector<int>& nums, int target);
vector<int> twoSumLoop(const vector<int>& nums, int target);

vector<int> simpleSortBubble(const vector<int>& nums);
vector<int> simpleSortMerge(const vector<int>& nums);
vector<int> simpleSortQuick(const vector<int>& nums);
vector<int> simpleSortSelection(const vector<int>& nums);
vector<int> simpleSortInsertion(const vector<int>& nums);

vector<int> arrayMerge(vector<int>& nums1, const vector<int>& nums2, int length1, int length2);

int binaryTreeMinimumDepthBFS(BinaryTreeNode* root);
int binaryTreeMinimumDepthDFS(BinaryTreeNode* root);

#endif