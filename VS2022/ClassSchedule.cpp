#include<queue>
#include<vector>
#include <unordered_set>
using namespace std;

//拓扑排序问题

//课程表1：一共n门课程 每门课程有先修课程  prerequisites[i]={ai,bi} 表示要想学习ai 必须先学习bi 即bi->ai有一条边
bool classSchedule1(int numCourses, vector<vector<int>>& prerequisites)
{ 
	vector<int> indegree(numCourses, 0);                   //入度表
	vector<vector<int>> m(numCourses);      //邻接表 a[b]代表  有一条a->b的边
	queue<int> q;

	//步骤一：根据prerequisites构造邻接表
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m[prerequisites[i][1]].push_back(prerequisites[i][0]);
		indegree[prerequisites[i][0]]++;
	}

	//步骤二：将indegree=0的课程加入队列中
	int studyCourse = 0;
	for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
	//步骤三：不断弹出队列
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

//课程表2： 相比较于1，要求返回学习的顺序即可 差不多一模一样
vector<int> classSchedule2(int numCourses, vector<vector<int>>& prerequisites)
{
	vector<int> indegree(numCourses, 0);                   //入度表
	vector<vector<int>> m(numCourses);      //邻接表 a[b]代表  有一条a->b的边
	queue<int> q;

	//步骤一：根据prerequisites构造邻接表
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m[prerequisites[i][1]].push_back(prerequisites[i][0]);
		indegree[prerequisites[i][0]]++;
	}

	//步骤二：将indegree=0的课程加入队列中
	int studyCourse = 0;
	for (int i = 0; i < numCourses; i++) if (indegree[i] == 0) q.push(i);
	vector<int> ans; ans.reserve(numCourses);
	//步骤三：不断弹出队列
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

//课程表3： courses[i] = [durationi,lastDayi] 表示第i门课将会上duration i 天课，并且必须在不晚于 lastDayi 的时候完成。
//返回最多可以修读的课程数目  贪心解
int classSchedule3(vector<vector<int>>& courses)
{
	//按照课程的结束时间进行排序
	sort(courses.begin(), courses.end(), [](const auto& c0, const auto& c1) {
		return c0[1] < c1[1];
		});

	priority_queue<int> q;
	// 优先队列中所有课程的总时间
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

//课程表4：题意同1,2 但是要返回 查询数组queries  queries[i,j] 用来询问 学习j之前 是否要学习i（包括直接和间接）

//答辩写法 不要参考这个
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
	vector<vector<bool>> preCondition(numCourses, vector<bool>(numCourses, false)); //记录所有点之间的情况
	vector<vector<int>> m1(numCourses);      //邻接表m1 a[b]代表  有一条a->b的边 出去的边
	vector<vector<int>> m2(numCourses);      //邻接表m2 a[b]代表  有一条b->a的边 进来的边
	//构建图
	for (int i = 0; i < prerequisites.size(); i++)
	{
		m1[prerequisites[i][1]].push_back(prerequisites[i][0]);
		m2[prerequisites[i][0]].push_back(prerequisites[i][1]);
	}
	//遍历所有点
	for (int i = 0; i < numCourses; i++)
	{
		//遍历从i指向别的点 m1[i][j]
		for (int j = 0; j < m1[i].size(); j++)
		{
			//学习m1[i][j] 之前 要学习 i课程
			//更新数据 1：直接的 2：间接的
			//同时递归地遍历所有指向i的点（包括直接和间接）  学习m1[i][j]之前 也要学习 m2[i][k]课程
			if (preCondition[m1[i][j]][i] == true) continue;
			unordered_set<int> hash;
			dfs(i, m1[i][j], m1, m2, hash, preCondition);
		}
	}

	vector<bool> ans; ans.reserve(queries.size());
	for (int k = 0; k < queries.size(); k++)
	{
		//询问 学习queries[k][1]之前是否需要学习queries[k][0]
		ans.push_back(preCondition[queries[k][0]][queries[k][1]]);
	}
	return ans;

}

// 利用拓扑排序  其实是动态规划的思路 注意prerequisites a b 表示要学习b课程 必须先学习a
vector<bool> checkIfPrerequisite_2(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
	vector<vector<int>> m(numCourses);
	vector<int> indgree(numCourses, 0);
	vector<vector<bool>> PreCondition(numCourses, vector<bool>(numCourses, false));
	//构建图
	for (auto& p : prerequisites) {
		++indgree[p[1]];
		m[p[0]].push_back(p[1]);
	}
	queue<int> q;
	//添加入度为0的点
	for (int i = 0; i < numCourses; ++i) {
		if (indgree[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		auto cur = q.front();
		q.pop();
		//遍历从cur指向别的点 ne
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
