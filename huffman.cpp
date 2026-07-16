#include"huffman.hpp"
Node:: Node(unsigned char ch, int freq)
{
    this->ch = ch;
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int freq, Node* left, Node* right)
:ch(0), freq(freq),left(left), right(right){}

bool compare::operator()(Node* a, Node* b)
{
    return a->freq > b->freq;
}

Huffman::Huffman()
:root(nullptr){}

Huffman::~Huffman()
{
    freeTree(root);
}

void Huffman::buildTree(const std::vector<int>& freq)
{
    std::priority_queue<Node*, std::vector<Node*>, compare>pq;

    for(int i = 0;i<256;i++)
    {
        if(freq[i] > 0)
            pq.push(new Node((unsigned char)i,freq[i]));
    }
    // edges of only one unqiue character
    if(pq.size()==1)
    {
        Node* only = pq.top();pq.pop();
        this->root = new Node(only->freq, only,nullptr);
        buildCodes(root,"");
        return;
    }

    while(pq.size() > 1)
    {
        Node* first = pq.top();pq.pop();
        Node* second = pq.top();pq.pop();
        Node* merge = new Node(first->freq + second->freq,first, second);
        pq.push(merge);
    }

    this->root = pq.top();
    buildCodes(root, "");
}

void Huffman::buildCodes(Node* node, std::string str)
{
    if(!node)return;

    if(!node->left && !node->right)
        codes[node->ch] = str;
    
    buildCodes(node->left,str+"0");
    buildCodes(node->right, str+"1");

}

std::unordered_map<unsigned char, std::string> Huffman::getCodes() const
{
    return codes;
}

Node* Huffman::getroot() const{
    return this->root;
}

void Huffman::freeTree(Node* root)
{
    if(!root)return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}