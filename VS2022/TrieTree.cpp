#include<string>
#include<vector>
using namespace std;

//实现前缀树
class Trie{
private:
    int pass;               //经过该节点的个数
    int end;                //以该节点为结尾的个数
    // bool isEnd (简单的情况)
    vector<Trie*> next;   

    //从trie结点开始进行删除，删除所有子节点及其自身 (递归)
    void deleteTrie(Trie* trie)
    {
        if (trie == nullptr) return;
        for (int i = 0; i < 26; i++)
        {
            deleteTrie(trie->next[i]);
        }
        delete(trie);
    }

public:
    Trie() :pass(0), end(0), next(26) {}

    //向前缀树中插入字符串
    void insert(string word) 
    {
        Trie* cur = this;
        for (int i = 0; i < word.size(); i++)
        {
            cur->pass++;
            if (cur->next[word[i] - 'a'] == nullptr) cur->next[word[i] - 'a'] = new Trie();
            cur = cur->next[word[i] - 'a'];
        }
        cur->pass++; cur->end++;
    }

    //向前缀树中删除字符串 (注意内存管理)
    void deleteWord(string word)
    {
        if (!search(word)) return;
        Trie* cur = this; cur->pass--;
        for (int i = 0; i < word.length(); i++)
        {
            cur = cur->next[word[i] - 'a'];
            if (--cur->pass == 0)
            {
                deleteTrie(cur);
                return;
            }
        }
        cur->end--;
    }

    //查找串是否完整地在前缀树中
    bool search(string word)
    {
        Trie* cur = this;
        for (int i = 0; i < word.size(); i++)
        {
            if (cur->next[word[i] - 'a']==nullptr) return false;
            cur = cur->next[word[i] - 'a'];
        }
        return cur->end != 0;
    }

    //查找前缀是否存在
    bool startsWith(string prefix) 
    {
        Trie* cur = this;
        for (int i = 0; i < prefix.size(); i++)
        {
            if (cur->next[prefix[i] - 'a'] == nullptr) return false;
            cur = cur->next[prefix[i] - 'a'];
        }
        return true;
    }
};