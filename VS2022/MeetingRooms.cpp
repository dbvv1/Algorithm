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

//会议室：给定一系列的会议时间间隔，包括起始和结束时间[[s1,e1]，[s2,e2]，…(si < ei)，确定一个人是否可以参加所有会议。
bool canAttendMeetings(vector<Interval>& intervals)
{
    //判断区间之间是否发生了冲突即可
     //按照开始时间进行排序
    sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {return a.start < b.start; });
    int curEnd = intervals[0].end;
    for (int i = 1; i < intervals.size(); i++)
    {
        if (curEnd < intervals[i].start) return false;
        curEnd = max(curEnd, intervals[i].end);
    }
    return true;
}

//会议室2：找到需要的会议室的最小数量

//方法一：排序 + 优先队列模拟

//方法二：分离开始时间和结束时间
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


//方法三：前缀和 进入是1，结束是-1 本质：求最大子数组和
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
    //编号0-n-1 会议室
    //每场会议都会在未占用且编号最小的会议室举办
    //如果没有可用的会议室 则会议将会延期

    //使用最小堆记录每个会议室
    //一个最小堆记录空闲的会议室
    //一个最小堆记录被占用中的会议室
    vector<pair<int, long long>> room; //pair记录每个房间的 编号 + 结束时间
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
        //先根据开始时间 判断 被占用的会议室
        while (!q2.empty() && q2.top().second <= meetings[i][0])
        {
            q1.push(q2.top());
            q2.pop();
        }

        //没有空余的会议室 进行等待操作
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