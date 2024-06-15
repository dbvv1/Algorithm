#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <chrono>

using namespace std;

struct Point
{
    double x, y;

    Point(double _x, double _y) : x(_x), y(_y)
    {
    }
};

struct Monster
{
    Point position;
    int id; // 其他可能的属性
    Monster(int _id, double x, double y) : id(_id), position(x, y)
    {
    }
};

class QuadTreeNode
{
public:
    Point topLeft;
    Point bottomRight;
    vector<shared_ptr<Monster>> monsters;
    QuadTreeNode* children[4];
    static const int CAPACITY = 4;

    QuadTreeNode(Point _topLeft, Point _bottomRight)
        : topLeft(_topLeft), bottomRight(_bottomRight)
    {
        fill(begin(children), end(children), nullptr);
    }

    bool inBoundary(const Point& p)
    {
        return (p.x >= topLeft.x && p.x <= bottomRight.x &&
            p.y >= topLeft.y && p.y <= bottomRight.y);
    }

    bool insert(shared_ptr<Monster> monster)
    {
        if (!inBoundary(monster->position))
            return false;

        if (monsters.size() < CAPACITY)
        {
            monsters.push_back(monster);
            return true;
        }

        if (children[0] == nullptr)
            subdivide();

        for (int i = 0; i < 4; ++i)
        {
            if (children[i]->insert(monster))
                return true;
        }

        return false;
    }

    void subdivide()
    {
        double midX = (topLeft.x + bottomRight.x) / 2;
        double midY = (topLeft.y + bottomRight.y) / 2;

        children[0] = new QuadTreeNode(Point(topLeft.x, topLeft.y), Point(midX, midY));
        children[1] = new QuadTreeNode(Point(midX, topLeft.y), Point(bottomRight.x, midY));
        children[2] = new QuadTreeNode(Point(topLeft.x, midY), Point(midX, bottomRight.y));
        children[3] = new QuadTreeNode(Point(midX, midY), Point(bottomRight.x, bottomRight.y));
    }

    void queryRange(const Point& center, double range, vector<shared_ptr<Monster>>& result)
    {
        if (!inBoundary(center))
            return;

        for (const auto& monster : monsters)
        {
            double distance = sqrt(pow(monster->position.x - center.x, 2) +
                pow(monster->position.y - center.y, 2));
            if (distance <= range)
            {
                result.push_back(monster);
            }
        }

        if (children[0] != nullptr)
        {
            for (int i = 0; i < 4; ++i)
            {
                children[i]->queryRange(center, range, result);
            }
        }
    }
};


class QuadTree
{
public:
    QuadTreeNode* root;

    QuadTree(Point topLeft, Point bottomRight)
    {
        root = new QuadTreeNode(topLeft, bottomRight);
    }

    void insert(shared_ptr<Monster> monster)
    {
        if (!root->inBoundary(monster->position))
            return;
        root->insert(monster);
    }

    vector<shared_ptr<Monster>> queryRange(const Point& center, double range)
    {
        vector<shared_ptr<Monster>> result;
        root->queryRange(center, range, result);
        return result;
    }

    void clear()
    {
        delete root;
        root = nullptr;
    }
};


vector<shared_ptr<Monster>> findNearestKMonsters(const Point& playerPosition, QuadTree& qt, int k)
{
    vector<shared_ptr<Monster>> nearbyMonsters = qt.queryRange(playerPosition, numeric_limits<double>::max());

    // 使用最小堆找到前k个最近的怪物
    auto distance = [&](const shared_ptr<Monster>& m)
    {
        return sqrt(pow(m->position.x - playerPosition.x, 2) +
            pow(m->position.y - playerPosition.y, 2));
    };

    auto cmp = [&](const shared_ptr<Monster>& a, const shared_ptr<Monster>& b)
    {
        return distance(a) < distance(b);
    };

    priority_queue<shared_ptr<Monster>, vector<shared_ptr<Monster>>, decltype(cmp)> maxHeap(cmp);

    for (const auto& monster : nearbyMonsters)
    {
        if (maxHeap.size() < k)
        {
            maxHeap.push(monster);
        }
        else if (distance(monster) < distance(maxHeap.top()))
        {
            maxHeap.pop();
            maxHeap.push(monster);
        }
    }

    vector<shared_ptr<Monster>> result;
    while (!maxHeap.empty())
    {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    reverse(result.begin(), result.end()); // 按距离从近到远排序
    return result;
}


void updateMonsterPositions(vector<shared_ptr<Monster>>& monsters, QuadTree& qt, unordered_set<int>& movedMonsters)
{
    for (const int id : movedMonsters)
    {
        // 更新怪物位置的逻辑
        // 例如，monsters[id]->position.x += dx, monsters[id]->position.y += dy;
        qt.insert(monsters[id]);
    }
    movedMonsters.clear();
}
