#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>

struct Node{
    unsigned char ch;
    int freq;
    Node* left;
    Node* right;
    Node(unsigned char ch, int freq);
    Node(int f, Node* left, Node* right);
};
struct compare{
    bool operator()(Node* a, Node* b);
};

class Huffman{
    private:
        Node* root;
        std::unordered_map<unsigned char, std::string>codes;
        void buildCodes(Node* node, std::string str);
    public:
        Huffman();
        ~Huffman();
        void buildTree(const std::vector<int>& freq);
        std::unordered_map<unsigned char, std::string> getCodes() const;
        Node* getroot() const;

        void freeTree(Node* root);


};
#endif