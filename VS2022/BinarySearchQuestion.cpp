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
//方法一：在两个有序数组中寻找第k个数
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) 
{
    //最关键的部分 分别取两个数组中 start下标 + k/2-1的中的元素 每次排除一半的部分
    /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
     * 这里的 "/" 表示整除
     * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
     * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
     * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
     * 这样 pivot 本身最大也只能是第 k-1 小的元素
     * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
     * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
     * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
     */

    int n = nums1.size();
    int m = nums2.size();
    int index1 = 0, index2 = 0;

    while (true) {
        // 边界情况
        if (index1 == n) return nums2[index2 + k - 1];
        if (index2 == m) return nums1[index1 + k - 1];
        if (k == 1)  return min(nums1[index1], nums2[index2]);

        // 正常情况
        int newIndex1 = min(index1 + k / 2 - 1, n - 1);
        int newIndex2 = min(index2 + k / 2 - 1, m - 1);
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


double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
    int totalLength = nums1.size() + nums2.size();
    if (totalLength % 2 == 1) {
        return getKthElement(nums1, nums2, (totalLength + 1) / 2);
    }
    else {
        return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
    }
}

//方法二：划分数组，寻找分割线
//使用一条分割线（可能是折线） 将两个数组均划分成左右两部分，要求左边所有元素严格小于右边所有元素，左边数量=右边数量
//那么中位数就是分割线左边的较大值   或者  分割线左边的较大值和右边的较小值 取中间值
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //要求数组1的数量要小于数组2的数量
    if (nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);


    int n = nums1.size();
    int m = nums2.size();
    int left = 0, right = n;
    // median1：前一部分的最大值
    // median2：后一部分的最小值
    int median1 = 0, median2 = 0;

    while (left <= right)
    {
        //在第一个数组中二分分割线的位置i，通过元素数量可以直接求得j
        // 前一部分包含 nums1[0 .. i-1] 和 nums2[0 .. j-1]
        // 后一部分包含 nums1[i .. m-1] 和 nums2[j .. n-1]
        int i = (left + right) / 2;
        int j = (n + m + 1) / 2 - i;

        // nums_im1, nums_i, nums_jm1, nums_j 分别表示 nums1[i-1], nums1[i], nums2[j-1], nums2[j]
        int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
        int nums_i = (i == n ? INT_MAX : nums1[i]);
        int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
        int nums_j = (j == m ? INT_MAX : nums2[j]);

        if (nums_im1 <= nums_j && nums_i >= nums_jm1) 
        {
            median1 = max(nums_im1, nums_jm1);
            median2 = min(nums_i, nums_j);
            break;
        }
        else if (nums_i < nums_jm1) left = i + 1;
        else
        {
            right = i - 1;
        }
    }

    return (n + m) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
}