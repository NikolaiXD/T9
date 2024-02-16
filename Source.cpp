#include <iostream>
#include <unordered_map>
using namespace std;
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;

    TrieNode() : is_end_of_word(false) {}
};

class Trie 
{
public:
    Trie() 
    {
        root = new TrieNode();
    }

    ~Trie() 
    {
        deleteTrie(root);
    }

    void insert(const string& word) 
    {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->is_end_of_word = true;
    }

    vector<string> search(const string& prefix) 
    {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) 
            {
                return {};
            }
            node = node->children[ch];
        }

        vector<string> suggestions;
        collectWords(node, prefix, suggestions);
        return suggestions;
    }

private:
    TrieNode* root;

    void collectWords(TrieNode* node, const string& prefix, vector<string>& suggestions) 
    {
        if (node->is_end_of_word) 
        {
            suggestions.push_back(prefix);
        }

        for (auto& entry : node->children) 
        {
            collectWords(entry.second, prefix + entry.first, suggestions);
        }
    }

    void deleteTrie(TrieNode* node) 
    {
        for (auto& entry : node->children) 
        {
            deleteTrie(entry.second);
        }
        delete node;
    }
};

int main() 
{
    // Пример словаря
    setlocale(LC_ALL, "Rus");
    vector<string> wordList = { "apple", "app", "banana", "bat", "batman", "home", "world", "hello", "work"};

    // Создаем три-бор и добавляем слова в словарь
    Trie trie;
    for (const string& word : wordList) 
    {
        trie.insert(word);
    }

    while (true) {
        string prefix;
        cout << "Введите часть слова для автодополнения (или 'exit' для выхода) (Писать только на Английском): ";
        cin >> prefix;

        if (prefix == "exit") 
        {
            break;
        }

        vector<string> suggestions = trie.search(prefix);

        if (!suggestions.empty()) {
            cout << "Подходящие варианты:" << endl;
            for (const string& suggestion : suggestions) {
                cout << suggestion << endl;
            }
        }
        else {
            cout << "Нет подходящих вариантов." << endl;
        }
    }

    return 0;
}