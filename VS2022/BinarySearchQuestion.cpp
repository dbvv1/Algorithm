#include<vector>
using namespace std;

//��Ŀһ��������ת�������� nums��ÿ��ֵ��һ�޶�
int search(vector<int>& nums, int target)
{
    //�ص㣺���������
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] > target)
        {
            //target mid ������������
            if (target >= nums[l] || nums[mid] < nums[l]) r = mid - 1;
            else l = mid + 1;
        }
        else
        {
            //target mid �����Ұ������
            if (nums[mid] >= nums[l] || target < nums[l]) l = mid + 1;
            else r = mid - 1;
        }

    }
    return -1;
}

//��Ŀ����Ѱ����ת���������е���Сֵ
int findMin(vector<int>& nums)
{
    //�ص㣺���������
    int l = 0, r = nums.size() - 1;
    if (nums[l] < nums[r] || l == r) return nums[l]; //���������������� ��������ֻ��һ���������
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        //��һ�����Ұ���
        if (nums[mid] >= nums[0])
        {
            l = mid + 1;
        }
        //��һ���������
        else
        {
            r = mid - 1;
        }

    }
    return nums[l];
}

//��Ŀ����Ѱ���������������е���λ��
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
    int m = nums1.size();
    int n = nums2.size();
    int index1 = 0, index2 = 0;

    while (true) {
        // �߽����
        if (index1 == m) {
            return nums2[index2 + k - 1];
        }
        if (index2 == n) {
            return nums1[index1 + k - 1];
        }
        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        // �������
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