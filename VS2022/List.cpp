#include<vector>
#include<list>
#include<unordered_map>
#include<queue>
using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode()
		: val(0)
		, next(nullptr)
	{
	}
	ListNode(int x)
		: val(x)
		, next(nullptr)
	{
	}
	ListNode(int x, ListNode* next)
		: val(x)
		, next(next)
	{
	}
};

//求链表的长度
int getListLength(ListNode* p)
{
	int len = 0;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}

//相交链表：返回两个链表的相交结点
//方法一：哈希表  方法二：求长度的差值  方法三：双指针
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
	if (headA == nullptr || headB == nullptr)  return nullptr;
	ListNode* pA = headA, * pB = headB;
	while (pA != pB)
	{
		pA = pA == nullptr ? headB : pA->next;
		pB = pB == nullptr ? headA : pB->next;
	}
	return pA;
}


//翻转链表  三个指针 pre p post
ListNode* reverseList(ListNode* head)
{
	ListNode* pre = nullptr;
	ListNode* p = head;
	while (p)
	{
		ListNode* post = p->next;
		p->next = pre;
		pre = p;
		p = post;
	}
	return pre;

}

//回文链表  快慢指针找中点 + 翻转后半部分 + 一一比较 + 翻转回去
bool isPalindrome(ListNode* head)
{
	ListNode* f = head;
	ListNode* s = head;
	while (f->next && f->next->next)
	{
		f = f->next->next;
		s = s->next;
	}
	//翻转s之后的部分
	ListNode* p1 = head;
	ListNode* end = reverseList(s);
	ListNode* p2 = end;
	while (p1 && p2)
	{
		if (p1->val != p2->val) return false;
		p1 = p1->next;
		p2 = p2->next;
	}
	//翻转回来
	reverseList(end);
	return true;

}


//判断链表中是否存在环 利用快慢指针
bool hasCycle(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) return false;
	ListNode* f = head->next->next;
	ListNode* s = head->next;
	//如果链表中存在环 则 f 和 s 一定会相遇 否则 f会到达空
	while (f != s)
	{
		if (f == nullptr || f->next == nullptr || f->next->next == nullptr) return false;
		f = f->next->next;
		s = s->next;
	}
	return true;
}

//环形链表求入口结点 利用快慢指针第一次相遇 + 回溯快指针 + 第二次相遇
ListNode* detectCycle(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) return nullptr;
	ListNode* f = head->next->next;
	ListNode* s = head->next;
	while (f != s)
	{
		if (f == nullptr || f->next == nullptr || f->next->next == nullptr) return nullptr;
		f = f->next->next;
		s = s->next;
	}
	f = head;
	while (f != s)
	{
		f = f->next;
		s = s->next;
	}
	return f;
}

//合并两个有序链表  双指针法 + 最后的合并
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
	ListNode* newHead = new ListNode(0);
	ListNode* p = newHead;
	ListNode* p1 = list1;
	ListNode* p2 = list2;
	while (p1 && p2)
	{
		if (p1->val <= p2->val)
		{
			p->next = p1;
			p1 = p1->next;
		}
		else
		{
			p->next = p2;
			p2 = p2->next;
		}
		p = p->next;
	}
	p->next = p1 ? p1 : p2;
	ListNode* ans = newHead->next;
	delete(newHead);
	return ans;
}

//排序链表 归并排序
//归并过程
ListNode* merge(ListNode* head, ListNode* tail)
{
	if (head == tail || head->next == tail) return head;
	//快慢指针找到中点 s
	ListNode* f = head;
	ListNode* s = head;
	while (f->next && f->next->next)
	{
		f = f->next->next;
		s = s->next;
	}
	ListNode* rightPart = s->next;
	s->next = nullptr;
	//递归左右两部分 + 合并操作
	return mergeTwoLists(merge(head, s->next), merge(rightPart, tail));
}

ListNode* sortList(ListNode* head)
{
	return merge(head, nullptr);
}

//两个链表 按照顺序相加模拟进位即可
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* newHead = new ListNode();
	ListNode* p = newHead;
	int c = 0;//进位
	while (l1 || l2)
	{
		if (l1 && l2)
		{
			l1->val += l2->val + c;
			p->next = l1;
			l1 = l1->next;
			l2 = l2->next;
		}
		else if (l1)
		{
			l1->val += c;
			p->next = l1;
			l1 = l1->next;
		}
		else if (l2)
		{
			l2->val += c;
			p->next = l2;
			l2 = l2->next;
		}
		p = p->next;
		c = p->val / 10;
		p->val = p->val % 10;
	}
	if (c == 1)
	{
		p->next = new ListNode(1);
		p = p->next;
	}
	p->next = nullptr;
	return newHead->next;

}

//删除链表倒数第k个结点
//方法一：求链表的长度 + 确定删除的前一个位置
ListNode* removeNthFromEndF1(ListNode* head, int k)
{
	ListNode* newHead = new ListNode(0);
	newHead->next = head;
	int len = 0;
	ListNode* p = head;
	while (p) { len++; p = p->next; }
	//从虚拟的头开始移动len-k个节点 到要删除位置的前一个位置即可
	int move = len - k;
	p = newHead;
	while (move--) p = p->next;
	ListNode* pos = p->next->next;
	delete(p->next);
	p->next = pos;
	return newHead->next;
}

//方法二：递归处理
int cur = 0;
ListNode* removeNthFromEndF2(ListNode* head, int k)
{
	if (!head) return nullptr;
	head->next = removeNthFromEndF2(head->next, k);
	cur++;
	if (k == cur) return head->next;
	return head;
}


//两两交换链表中的结点：两个一组翻转链表
//方法一：直接处理
ListNode* swapPairs(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) return head;
	ListNode* pre = head;
	ListNode* p = head->next;
	ListNode* newHead = head->next;
	while (pre && p)
	{
		ListNode* pos = p->next;
		p->next = pre;
		if (pos == nullptr || pos->next == nullptr) pre->next = pos;
		else pre->next = pos->next;
		pre = pos;
		if (pos)p = pos->next;
	}
	return newHead;
}
//方法二：递归处理
ListNode* swapPairsF(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) return head;
	ListNode* newHead = head->next;
	head->next = swapPairsF(newHead->next);
	newHead->next = head;
	return newHead;
}

//k个一组翻转链表 递归 返回头和尾
pair<ListNode*, ListNode* > reverseKGroupF(ListNode* head, int k)
{
	ListNode* newHead = head;
	ListNode* tail = head;
	//先递归 再处理本层结点
	for (int i = 0; i < k - 1 && tail != nullptr; i++) tail = tail->next;
	if (tail == nullptr) return{ newHead,tail };



	return { newHead,tail };
}

ListNode* reverseKGroup(ListNode* head, int k)
{

}



//合并k个升序链表 多路归并
ListNode* mergeKLists(vector<ListNode*>& lists)
{
	ListNode* newHead = new ListNode(0);
	ListNode* p = newHead;
	auto cmp = [](const ListNode* a, const ListNode* b) {return a->val > b->val; };
	priority_queue<ListNode*, vector<ListNode*>, decltype(cmp) > q(cmp);
	for (int i = 0; i < lists.size(); i++)
	{
		if (lists[i] != nullptr)
			q.push(lists[i]);
	}
	while (!q.empty())
	{
		ListNode* t = q.top(); q.pop();
		p->next = t;
		p = p->next;
		if (t->next) q.push(t->next);
	}
	return newHead->next;
}

//LRU缓存  哈希表 + 链表   注意哈希表的键值要存储链表的迭代器
class LRUCache {
private:
	list<pair<int, int>> l;
	unordered_map<int, decltype(l.begin()) > hash;
	int cap;
public:
	LRUCache(int capacity) :cap(capacity) {}

	int get(int key)
	{
		if (!hash.count(key)) return -1;
		auto& t = hash[key];
		l.push_back({ key, (*t).second });
		l.erase(t);
		hash[key] = --l.end();
		return l.back().second;
	}

	void put(int key, int value)
	{
		if (hash.count(key))
		{
			l.erase(hash[key]);
		}
		else if (l.size() >= cap)
		{

			//淘汰掉l的头部
			hash.erase(l.front().first);
			l.erase(l.begin());

		}
		l.push_back({ key, value });
		hash[key] = --l.end();
	}
};


// Definition for a Node.
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};


class Solution {
private:
	unordered_map<Node*, Node*> hash;
public:
	//使用哈希表
	Node* copyRandomList(Node* head)
	{
		if (head == nullptr) return nullptr;
		Node* newHead = new Node(head->val);
		Node* p1 = newHead;
		hash[head] = p1;
		Node* p2 = head->next;
		while (p2)
		{
			p1->next = new Node(p2->val);
			p1 = p1->next;
			hash[p2] = p1;
			p2 = p2->next;
		}
		p1 = newHead;
		p2 = head;
		while (p1)
		{
			p1->random = hash[p2->random];
			p1 = p1->next;
			p2 = p2->next;
		}
		return newHead;

	}
};