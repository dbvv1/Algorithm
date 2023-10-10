#include<vector>
using namespace std;

//题目一：搜索旋转排序数组 nums中每个值独一无二
int search(vector<int>& nums, int target)
{
    //重点：分情况讨论
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target)
        {
            //target mid 都在左半边区域
            if (target >= nums[l] || nums[mid] < nums[l]) r = mid - 1;
            else l = mid + 1;
        }
        else
        {
            //target mid 都在右半边区域
            if (nums[mid] >= nums[l] || target < nums[l]) l = mid + 1;
            else r = mid - 1;
        }

    }
    return -1;
}

//题目二：寻找旋转排序数组中的最小值
int findMin(vector<int>& nums)
{
    //重点：分情况讨论
    int l = 0, r = nums.size() - 1;
    if (nums[l] < nums[r] || l == r) return nums[l]; //数组整体有序的情况 或者数组只有一个数的情况
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        //答案一定在右半区
        if (nums[mid] >= nums[0])
        {
            l = mid + 1;
        }
        //答案一定在左半区
        else
        {
            r = mid - 1;
        }

    }
    return nums[l];
}

//题目三：寻找两个有序数组中的中位数
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
    int m = nums1.size();
    int n = nums2.size();
    int index1 = 0, index2 = 0;

    while (true) {
        // 边界情况
        if (index1 == m) {
            return nums2[index2 + k - 1];
        }
        if (index2 == n) {
            return nums1[index1 + k - 1];
        }
        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        // 正常情况
        int newIndex1 = min(index1 + k / 2 - 1, m - 1);
        int newIndex2 = min(index2 + k / 2 - 1, n - 1);
        int pivot1 = nums1[newIndex1];
        int pivot2 = nums2[newIndex2];
        if (pivot1 <= pivot2) {
            k -= newIndex1 - index1 + 1;
            index1 = newIndex1 + 1;
        }
        else {
            k -= newIndex2 - index2 + 1;
            index2 = newIndex2 + 1;
        }
    }
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int totalLength = nums1.size() + nums2.size();
    if (totalLength % 2 == 1) {
        return getKthElement(nums1, nums2, (totalLength + 1) / 2);
    }
    else {
        return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
    }
}