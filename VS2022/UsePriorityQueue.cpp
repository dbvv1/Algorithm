#include<vector>
#include<queue>
#include<functional>
using namespace std;

class MedianFinder {
private:
    priority_queue<int, vector<int>, less<int>> maxq;      //大根堆 存储较小的部分数
    priority_queue<int, vector<int>, greater<int>> minq;   //小根堆 存储较大的部分数
public:
    //规定大根堆（较小部分）将拥有较多的数

    MedianFinder() {

    }

    void addNum1(int num)
    {
        maxq.push(num);
        if (maxq.size() >= minq.size() + 2)
        {
            minq.push(maxq.top());
            maxq.pop();
        }
        else if (!minq.empty() && maxq.top() > minq.top())
        {
            maxq.push(minq.top());
            minq.pop();
            minq.push(maxq.top());
        }
    }

    void addNum2(int num)
    {
        if (!minq.empty() && num > minq.top()) minq.push(num);
        else maxq.push(num);

        if (maxq.size() < minq.size())
        {
            maxq.push(minq.top());
            minq.pop();
        }
        if (maxq.size() - minq.size() >= 2)
        {
            minq.push(maxq.top());
            maxq.pop();
        }
    }

    double findMedian()
    {
        if (maxq.size() == minq.size())
        {
            return (double)(maxq.top() + minq.top()) / 2;
        }
        else return maxq.top();
    }
};