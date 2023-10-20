#include<vector>
#include<set>
#include <stack>
using namespace std;

//����һ���������� nums �������й��� n ��������132 ģʽ�������� ���������� nums[i]��nums[j] �� nums[k] ��ɣ���ͬʱ���㣺i < j < k �� nums[i] < nums[k] < nums[j] �� ��ߵ���С���ұߵ���  �ұߵ���С���м����

//����һ��ö���м��Ǹ�����ֵ ʹ�����򼯺� multiset
bool find132patternF1(vector<int>& nums) {
	int n = nums.size();
	if (n < 3) return;
	// �����Сֵ
	int left_min = nums[0];
	// �Ҳ�����Ԫ��
	multiset<int> right_all;

	for (int k = 2; k < n; ++k) {
		right_all.insert(nums[k]);
	}

	for (int j = 1; j < n - 1; ++j) {
		if (left_min < nums[j]) {
			auto it = right_all.upper_bound(left_min);
			if (it != right_all.end() && *it < nums[j]) {
				return true;
			}
		}
		left_min = min(left_min, nums[j]);
		right_all.erase(right_all.find(nums[j + 1]));
	}

	return false;
}

//����������������ö����Сֵ ά��һ���ݼ��ĵ���ջ ͬʱ��¼��ջ�����ֵk (k����132�е�2)
bool find132pattern(vector<int>& nums)
{
	//k���Ѿ���ջ��Ԫ�أ�˵���� k�����һ���б�kҪ���Ԫ��  ��� j k �������
	//ֻҪ����nums[i]< k ˵��������132�Ľṹ
	//ΪʲôkҪ�ǳ�ջ�����Ԫ���أ� ��ΪҪ�����ܵ�����kҪ��nums[i]Ҫ��
	int n = nums.size();
	stack<int> s;
	int k = INT_MIN;
	s.push(nums[n - 1]);
	for (int i = n - 1; i >= 0; i--)
	{
		if (nums[i] < k) return true;
		while (!s.empty() && nums[i] > s.top())
		{
			k = max(k, s.top());
			s.pop();
		}
		if (!s.empty() && nums[i] == s.top()) continue;

		s.push(nums[i]);

	}
	return false;

}

//���������ַ�������pattern��value�� pattern�ַ�������ĸ"a"��"b"��ɣ����������ַ����е�ģʽ�����磬�ַ���"catcatgocatgo"ƥ��ģʽ"aabab"������"cat"��"a"��"go"��"b"�������ַ���Ҳƥ����"a"��"ab"��"b"������ģʽ������ע��"a"��"b"����ͬʱ��ʾ��ͬ���ַ�������дһ�������ж�value�ַ����Ƿ�ƥ��pattern�ַ�����  ���ݷ�ΧΪ10^3
bool patternMatching(string pattern, string value)
{
	//pattern��ֻ���� a b ��ʾ��ʽ
	//����ö�� a �����п���
	int counta = 0;
	int countb = 0;
	int ak = -1; int prea1 = 0, preb1 = 0;//a��һ�γ��ֵ�λ�� ͬʱ��¼֮ǰ�м���a b
	int bk = -1; int prea2 = 0, preb2 = 0;//b��һ���ֵ�λ��   ͬʱ��¼֮ǰ�м���a b
	for (int i = 0; i < pattern.size(); i++)
	{
		if (pattern[i] == 'a')
		{
			if (ak == -1)
			{
				prea1 = counta;
				preb1 = countb;
				ak = i;
			}
			counta++;
		}
		else
		{
			if (bk == -1)
			{
				prea2 = counta;
				preb2 = countb;
				bk = i;
			}
			countb++;
		}

	}
	if (value == "") return counta == 0 || countb == 0; //���пմ������
	for (int i = 0; i <= value.size(); i++)
	{
		//a�ĳ���Ϊi �����Ƴ�b�ĳ���
		int lena = i;
		int lenb;
		if (countb != 0 && lena * counta > value.size()) break; //����Ī��������������ǰ�ж��Ƿ��ݵ���b
		if (countb == 0) lenb = 0;
		else lenb = (value.size() - lena * counta) / countb;
		//����ʵ�ʵ�ƥ�����
		string a; string b; a.reserve(lena); b.reserve(lenb);
		if (ak != -1)
		{
			//�����a
			int start = lena * prea1 + lenb * preb1;
			a = value.substr(start, lena);
		}
		if (bk != -1)
		{
			//�����b
			int start = lena * prea2 + lenb * preb2;
			b = value.substr(start, lenb);
		}
		if (a == b) continue;
				string ans; ans.reserve(value.size());
		for (int j = 0; j < pattern.size(); j++)
		{
			//ģ�����ɵĽ��
			if (pattern[j] == 'a') ans += a;
			else ans += b;
		}
		if (ans == value) return true;
	}
	return false;
}


bool patternMatching2(string pattern, string value) {
	int count_a = 0, count_b = 0;
	for (char ch : pattern) {
		if (ch == 'a') {
			++count_a;
		}
		else {
			++count_b;
		}
	}
	if (count_a < count_b) {
		swap(count_a, count_b);
		for (char& ch : pattern) {
			ch = (ch == 'a' ? 'b' : 'a');
		}
	}
	if (value.empty()) {
		return count_b == 0;
	}
	if (pattern.empty()) {
		return false;
	}
	for (int len_a = 0; count_a * len_a <= value.size(); ++len_a) {
		int rest = value.size() - count_a * len_a;
		if ((count_b == 0 && rest == 0) || (count_b != 0 && rest % count_b == 0)) {
			int len_b = (count_b == 0 ? 0 : rest / count_b);
			int pos = 0;
			bool correct = true;
			string value_a, value_b;
			for (char ch : pattern) {
				if (ch == 'a') {
					string sub = value.substr(pos, len_a);
					if (!value_a.size()) {
						value_a = move(sub);
					}
					else if (value_a != sub) {
						correct = false;
						break;
					}
					pos += len_a;
				}
				else {
					string sub = value.substr(pos, len_b);
					if (!value_b.size()) {
						value_b = move(sub);
					}
					else if (value_b != sub) {
						correct = false;
						break;
					}
					pos += len_b;
				}
			}
			if (correct && value_a != value_b) {
				return true;
			}
		}
	}
	return false;
}
