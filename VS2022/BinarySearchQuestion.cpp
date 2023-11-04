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
//����һ������������������Ѱ�ҵ�k����
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) 
{
    //��ؼ��Ĳ��� �ֱ�ȡ���������� start�±� + k/2-1���е�Ԫ�� ÿ���ų�һ��Ĳ���
    /* ��Ҫ˼·��Ҫ�ҵ��� k (k>1) С��Ԫ�أ���ô��ȡ pivot1 = nums1[k/2-1] �� pivot2 = nums2[k/2-1] ���бȽ�
     * ����� "/" ��ʾ����
     * nums1 ��С�ڵ��� pivot1 ��Ԫ���� nums1[0 .. k/2-2] ���� k/2-1 ��
     * nums2 ��С�ڵ��� pivot2 ��Ԫ���� nums2[0 .. k/2-2] ���� k/2-1 ��
     * ȡ pivot = min(pivot1, pivot2)������������С�ڵ��� pivot ��Ԫ�ع��Ʋ��ᳬ�� (k/2-1) + (k/2-1) <= k-2 ��
     * ���� pivot �������Ҳֻ���ǵ� k-1 С��Ԫ��
     * ��� pivot = pivot1����ô nums1[0 .. k/2-1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums1 ����
     * ��� pivot = pivot2����ô nums2[0 .. k/2-1] ���������ǵ� k С��Ԫ�ء�����ЩԪ��ȫ�� "ɾ��"��ʣ�µ���Ϊ�µ� nums2 ����
     * �������� "ɾ��" ��һЩԪ�أ���ЩԪ�ض��ȵ� k С��Ԫ��ҪС���������Ҫ�޸� k ��ֵ����ȥɾ�������ĸ���
     */

    int n = nums1.size();
    int m = nums2.size();
    int index1 = 0, index2 = 0;

    while (true) {
        // �߽����
        if (index1 == n) return nums2[index2 + k - 1];
        if (index2 == m) return nums1[index1 + k - 1];
        if (k == 1)  return min(nums1[index1], nums2[index2]);

        // �������
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

//���������������飬Ѱ�ҷָ���
//ʹ��һ���ָ��ߣ����������ߣ� ��������������ֳ����������֣�Ҫ���������Ԫ���ϸ�С���ұ�����Ԫ�أ��������=�ұ�����
//��ô��λ�����Ƿָ�����ߵĽϴ�ֵ   ����  �ָ�����ߵĽϴ�ֵ���ұߵĽ�Сֵ ȡ�м�ֵ
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    //Ҫ������1������ҪС������2������
    if (nums1.size() > nums2.size())
        return findMedianSortedArrays(nums2, nums1);


    int n = nums1.size();
    int m = nums2.size();
    int left = 0, right = n;
    // median1��ǰһ���ֵ����ֵ
    // median2����һ���ֵ���Сֵ
    int median1 = 0, median2 = 0;

    while (left <= right)
    {
        //�ڵ�һ�������ж��ַָ��ߵ�λ��i��ͨ��Ԫ����������ֱ�����j
        // ǰһ���ְ��� nums1[0 .. i-1] �� nums2[0 .. j-1]
        // ��һ���ְ��� nums1[i .. m-1] �� nums2[j .. n-1]
        int i = (left + right) / 2;
        int j = (n + m + 1) / 2 - i;

        // nums_im1, nums_i, nums_jm1, nums_j �ֱ��ʾ nums1[i-1], nums1[i], nums2[j-1], nums2[j]
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