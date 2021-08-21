#pragma once
#include "tree.h"
#include <iostream> 
#include <memory>
  
class HaffmanTree public : tree {
public: 
    typedef std::shared_ptr<HaffmanTree> ptr; 
	    
    HaffmanTree(); 
    virtual ~HaffmanTree();
    
    int mkHuffmanTree(Node::data_t* datas, int data_size);

private: 
    
}; // HaffmanTree
    
