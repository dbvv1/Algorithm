#include<vector>
#include<queue>
#include<map>
using namespace std;

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }

};

//�����ң�����һϵ�еĻ���ʱ������������ʼ�ͽ���ʱ��[[s1,e1]��[s2,e2]����(si < ei)��ȷ��һ�����Ƿ���Բμ����л��顣
bool canAttendMeetings(vector<Interval>& intervals)
{
    //�ж�����֮���Ƿ����˳�ͻ����
     //���տ�ʼʱ���������
    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {return a.start < b.start; });
    int curEnd = intervals[0].end;
    for (int i = 1; i < intervals.size(); i++)
    {
        if (curEnd < intervals[i].start) return false;
        curEnd = max(curEnd, intervals[i].end);
    }
    return true;
}

//������2���ҵ���Ҫ�Ļ����ҵ���С����

//����һ������ + ���ȶ���ģ��

//�����������뿪ʼʱ��ͽ���ʱ��
int minMeetingRooms(vector<Interval>& intervals) {
    // Check for the base case. If there are no intervals, return 0
    if (intervals.size() == 0) {
        return 0;
    }

    vector<int> start(intervals.size());
    vector<int> end(intervals.size());

    for (int i = 0; i < intervals.size(); i++) {
        start[i] = intervals[i].start;
        end[i] = intervals[i].end;
    }

    sort(end.begin(), end.end());

    sort(start.begin(), start.end());

    int startPointer = 0, endPointer = 0;

    int usedRooms = 0;
    while (startPointer < intervals.size()) {

        if (start[startPointer] >= end[endPointer]) {
            usedRooms -= 1;
            endPointer += 1;
        }
        usedRooms += 1;
        startPointer += 1;

    }

    return usedRooms;
}


//��������ǰ׺�� ������1��������-1 ���ʣ�������������
int minMeetingRooms(vector<Interval>& intervals) {
    // Write your code here
    map<int, int> m;
    for (auto a : intervals) {
        ++m[a.start];
        --m[a.end];
    }
    int rooms = 0, res = 0;
    for (auto it : m) {
        res = max(res, rooms += it.second);
    }
    return res;
}

int mostBooked(int n, vector<vector<int>>& meetings)
{
    //���0-n-1 ������
    //ÿ�����鶼����δռ���ұ����С�Ļ����Ҿٰ�
    //���û�п��õĻ����� ����齫������

    //ʹ����С�Ѽ�¼ÿ��������
    //һ����С�Ѽ�¼���еĻ�����
    //һ����С�Ѽ�¼��ռ���еĻ�����
    vector<pair<int, long long>> room; //pair��¼ÿ������� ��� + ����ʱ��
    auto cmpByNumber = [](const auto& a, const auto& b) {return a.first > b.first; };
    auto cmpByEndTime = [](const auto& a, const auto& b) {return a.second > b.second; };
    int count[100] = { 0 };
    int max1 = 0;
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype (cmpByNumber)> q1(cmpByNumber);
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype (cmpByEndTime)> q2(cmpByEndTime);
    sort(meetings.begin(), meetings.end(), [](const auto& a, const auto& b) {return a[0] < b[0]; });
    for (int i = 0; i < n; i++) q2.push({ i,0 });

    for (int i = 0; i < meetings.size(); i++)
    {
        //�ȸ��ݿ�ʼʱ�� �ж� ��ռ�õĻ�����
        while (!q2.empty() && q2.top().second <= meetings[i][0])
        {
            q1.push(q2.top());
            q2.pop();
        }

        //û�п���Ļ����� ���еȴ�����
        if (q1.empty())
        {
            pair<int, long long> t = q2.top(); q2.pop();
            while (!q2.empty() && q2.top().second == t.second)
            {
                q1.push(q2.top());
                q2.pop();
            }
            q1.push(t);
        }
        pair<int, long long> t = q1.top(); q1.pop();
        count[t.first]++;
        if (count[t.first] == count[max1]) max1 = min(max1, t.first);
        else if (count[t.first] > count[max1]) max1 = t.first;
        long long newEnd = meetings[i][0] >= t.second ? meetings[i][1] : t.second + (meetings[i][1] - meetings[i][0]);
        q2.push({ t.first,newEnd });
    }
    return max1;

}