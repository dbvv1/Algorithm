#include<queue>
#include<vector>
#include <unordered_set>
using namespace std;

//������������

//�γ̱�1��һ��n�ſγ� ÿ�ſγ������޿γ�  prerequisites[i]={ai,bi} ��ʾҪ��ѧϰai ������ѧϰbi ��bi->ai��һ����
bool classSchedule1(int numCourses, vector<vector<int>>& prerequisites)
{ 
	vector<int> indegree(numCourses, 0);                   //��ȱ�
	vector<vector<int>> m(numCourses);      //�ڽӱ� a[b]����  ��һ��a->b�ı�
	queue<int> q;

	//����һ������prerequisites�����ڽӱ�
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m[prerequisites[i][1]].push_back(prerequisites[i][0]);
		indegree[prerequisites[i][0]]++;
	}

	//���������indegree=0�Ŀγ̼��������
	int studyCourse = 0;
	for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
	//�����������ϵ�������
	while (!q.empty())
	{
		int t = q.front(); q.pop();
		studyCourse++;
		for (int i = 0; i < m[t].size();i++)
		{
			if (--indegree[m[t][i]] == 0) q.push(m[t][i]);
		}
	}
	return studyCourse == numCourses;
}

//�γ̱�2�� ��Ƚ���1��Ҫ�󷵻�ѧϰ��˳�򼴿� ���һģһ��
vector<int> classSchedule2(int numCourses, vector<vector<int>>& prerequisites)
{
	vector<int> indegree(numCourses, 0);                   //��ȱ�
	vector<vector<int>> m(numCourses);      //�ڽӱ� a[b]����  ��һ��a->b�ı�
	queue<int> q;

	//����һ������prerequisites�����ڽӱ�
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m[prerequisites[i][1]].push_back(prerequisites[i][0]);
		indegree[prerequisites[i][0]]++;
	}

	//���������indegree=0�Ŀγ̼��������
	int studyCourse = 0;
	for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
	vector<int> ans; ans.reserve(numCourses);
	//�����������ϵ�������
	while (!q.empty())
	{
		int t = q.front(); q.pop();
		ans.push_back(t);
		studyCourse++;
		for (int i = 0; i < m[t].size(); i++)
		{
			if (--indegree[m[t][i]] == 0) q.push(m[t][i]);
		}
	}
	if (studyCourse != numCourses) return {};
	return ans;
}

//�γ̱�3�� courses[i] = [durationi,lastDayi] ��ʾ��i�ſν�����duration i ��Σ����ұ����ڲ����� lastDayi ��ʱ����ɡ�
//�����������޶��Ŀγ���Ŀ  ̰�Ľ�
int classSchedule3(vector<vector<int>>& courses)
{
	//���տγ̵Ľ���ʱ���������
	sort(courses.begin(), courses.end(), [](const auto& c0, const auto& c1) {
		return c0[1] < c1[1];
		});

	priority_queue<int> q;
	// ���ȶ��������пγ̵���ʱ��
	int total = 0;

	for (const auto& course : courses) {
		int ti = course[0], di = course[1];
		if (total + ti <= di) {
			total += ti;
			q.push(ti);
		}
		else if (!q.empty() && q.top() > ti) {
			total -= q.top() - ti;
			q.pop();
			q.push(ti);
		}
	}

	return q.size();
}

//�γ̱�4������ͬ1,2 ����Ҫ���� ��ѯ����queries  queries[i,j] ����ѯ�� ѧϰj֮ǰ �Ƿ�Ҫѧϰi������ֱ�Ӻͼ�ӣ�

//���д�� ��Ҫ�ο����
void dfs(int x, int target, vector<vector<int>>& m1, vector<vector<int>>& m2, unordered_set<int>& hash, vector<vector<bool>>& preCondition)
{
	if (hash.count(x) != 0) return;
	hash.insert(x);
	if (preCondition[target][x] == true) return;
	preCondition[target][x] = true;
	for (int k = 0; k < m2[x].size(); k++)
	{
		dfs(m2[x][k], target, m1, m2, hash, preCondition);
		preCondition[target][m2[x][k]] = true;
	}
}

vector<bool> checkIfPrerequisite_1(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
{
	vector<vector<bool>> preCondition(numCourses, vector<bool>(numCourses, false)); //��¼���е�֮������
	vector<vector<int>> m1(numCourses);      //�ڽӱ�m1 a[b]����  ��һ��a->b�ı� ��ȥ�ı�
	vector<vector<int>> m2(numCourses);      //�ڽӱ�m2 a[b]����  ��һ��b->a�ı� �����ı�
	//����ͼ
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m1[prerequisites[i][1]].push_back(prerequisites[i][0]);
		m2[prerequisites[i][0]].push_back(prerequisites[i][1]);
	}
	//�������е�
	for (int i = 0; i < numCourses; i++)
	{
		//������iָ���ĵ� m1[i][j]
		for (int j = 0; j < m1[i].size(); j++)
		{
			//ѧϰm1[i][j] ֮ǰ Ҫѧϰ i�γ�
			//�������� 1��ֱ�ӵ� 2����ӵ�
			//ͬʱ�ݹ�ر�������ָ��i�ĵ㣨����ֱ�Ӻͼ�ӣ�  ѧϰm1[i][j]֮ǰ ҲҪѧϰ m2[i][k]�γ�
			if (preCondition[m1[i][j]][i] == true) continue;
			unordered_set<int> hash;
			dfs(i, m1[i][j], m1, m2, hash, preCondition);
		}
	}

	vector<bool> ans; ans.reserve(queries.size());
	for (int k = 0; k < queries.size(); k++)
	{
		//ѯ�� ѧϰqueries[k][1]֮ǰ�Ƿ���Ҫѧϰqueries[k][0]
		ans.push_back(preCondition[queries[k][0]][queries[k][1]]);
	}
	return ans;

}

// ������������  ��ʵ�Ƕ�̬�滮��˼· ע��prerequisites a b ��ʾҪѧϰb�γ� ������ѧϰa
vector<bool> checkIfPrerequisite_2(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
	vector<vector<int>> m(numCourses);
	vector<int> indgree(numCourses, 0);
	vector<vector<bool>> PreCondition(numCourses, vector<bool>(numCourses, false));
	//����ͼ
	for (auto& p : prerequisites) {
		++indgree[p[1]];
		m[p[0]].push_back(p[1]);
	}
	queue<int> q;
	//������Ϊ0�ĵ�
	for (int i = 0; i < numCourses; ++i) {
		if (indgree[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		//������curָ���ĵ� ne
		for (auto& ne : m[cur])
		{
			PreCondition[cur][ne] = true;
			for (int i = 0; i < numCourses; ++i) 
			{ 
				if (PreCondition[i][cur]) PreCondition[i][ne] = 1;
			}
			--indgree[ne];
			if (indgree[ne] == 0) {
				q.push(ne);
			}
		}
	}
	vector<bool> res;
	for (auto& query : queries) {
		res.push_back(PreCondition[query[0]][query[1]]);
	}
	return res;
}
