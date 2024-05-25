#include<string>
#include<vector>
using namespace std;

//ʵ��ǰ׺��
class Trie{
private:
    int pass;               //�����ýڵ�ĸ���
    int end;                //�Ըýڵ�Ϊ��β�ĸ���
    // bool isEnd (�򵥵����)
    vector<Trie*> next;   

    //��trie��㿪ʼ����ɾ����ɾ�������ӽڵ㼰������ (�ݹ�)
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

    //��ǰ׺���в����ַ���
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

    //��ǰ׺����ɾ���ַ��� (ע���ڴ����)
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

    //���Ҵ��Ƿ���������ǰ׺����
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

    //����ǰ׺�Ƿ����
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