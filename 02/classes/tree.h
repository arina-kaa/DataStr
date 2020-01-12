#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace ::std;

enum class NodeType
{
    AND,
    OR,
    LIST
};

template <typename T>
class Tree
{
  private:
    struct Node
    {
        Node(const T &value, int level, NodeType type)
            : value(value), level(level), type(type){};

        T value;
        int level;
        NodeType type;
        shared_ptr<Node> parent = nullptr;
        vector<shared_ptr<Node>> childs;
        vector<string> gen;
    };
    shared_ptr<Node> top;
    shared_ptr<Node> current;
    vector<shared_ptr<Node>> nodes;

    void printElement(shared_ptr<Node> el)
    {
        cout << string(el->level, '.') << el->value << endl;
        if (!el->childs.empty())
        {
            for (const auto &child : el->childs)
                printElement(child);
        }
    }
    vector<shared_ptr<Node>> getNotListNodes()
    {
        vector<shared_ptr<Node>> notListNodes;
        for (const auto &node : nodes)
        {
            if (node->type != NodeType::LIST)
            {
                notListNodes.push_back(node);
            }
            else
            {
                node->gen.push_back(node->value);
            }
        }
        reverse(notListNodes.begin(), notListNodes.end());
        return notListNodes;
    }
    void setNodeGens(const vector<vector<string>> &nodeGens, size_t index, string str, vector<string> &resultGen)
    {
        if (index >= nodeGens.size())
        {
            resultGen.push_back(str);
            return;
        }
        for (const auto &ch : nodeGens[index])
            setNodeGens(nodeGens, index + 1, str + ch, resultGen);
    }
    void setGensForNodes(vector<shared_ptr<Node>> &notListNodes)
    {
        for (const auto &node : notListNodes)
        {
            vector<string> resultGen;
            if (node->type == NodeType::OR)
            {
                for (const auto &child : node->childs)
                {
                    resultGen.insert(resultGen.end(), child->gen.begin(), child->gen.end());
                }
            }
            else
            {
                vector<vector<string>> nodeGens;
                for (const auto &child : node->childs)
                {
                    nodeGens.push_back(child->gen);
                }
                setNodeGens(nodeGens, 0, "", resultGen);
            }
            node->gen = resultGen;
        }
    }
    void printTreeElements()
    {
        size_t c = 1;
        for (const auto &gen : top->gen)
        {
            cout << " " << c++ << ")" << endl;
            vector<shared_ptr<Node>> v;
            for (const auto &ch : gen)
            {
                auto node = *find_if(nodes.begin(), nodes.end(), [=](const auto &node) {
                    return node->value == string(1, ch);
                });
                do
                {
                    v.push_back(node);
                    node = node->parent;
                } while (node);
            }
            vector<shared_ptr<Node>> res;
            copy_if(nodes.begin(), nodes.end(), back_inserter(res), [=](const auto &node) {
                return find_if(v.begin(), v.end(), [=](const auto a) {
                           return a->value == node->value;
                       }) != v.end();
            });
            for (const auto r : res)
            {
                cout << "  " << string(r->level, '.') << " " << r->value << endl;
            }
            cout << endl;
        }
    }

  public:
    Tree() : top(nullptr), current(nullptr) {}
    ~Tree() {}
    void insert(const T &value, int level, NodeType type)
    {
        shared_ptr<Node> newNode = make_shared<Node>(value, level, type);
        nodes.push_back(newNode);
        if (top == nullptr)
        {
            top = newNode;
        }
        if (current != nullptr)
        {
            if (newNode->level == current->level)
            {
                newNode->parent = current->parent;
                current->parent->childs.push_back(newNode);
            }
            if (newNode->level > current->level)
            {
                current->childs.push_back(newNode);
                newNode->parent = current;
            }
            if (newNode->level < current->level)
            {
                while (current->parent)
                {
                    if (current->level == newNode->level)
                    {
                        newNode->parent = current->parent;
                        current->parent->childs.push_back(newNode);
                        break;
                    }
                    else
                    {
                        current = current->parent;
                    }
                }
            }
        }
        current = newNode;
    }
    void print()
    {
        printElement(top);
    }
    void generate()
    {
        vector<shared_ptr<Node>> notListNodes = getNotListNodes();
        setGensForNodes(notListNodes);
        cout << endl
             << "Count of elements: " << top->gen.size() << endl
             << endl;
        printTreeElements();
    }
};
