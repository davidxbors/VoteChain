#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "json.hh"
using json = nlohmann::json;
using namespace std;

class Block{
    public:
    Block(int index, string prevHash, string haash, string nonce, vector<string> data);
    string getPreviousHash(void);
    string getHash(void);
    int getIndex(void);
    vector<string> getData(void);
    void printBlock(void);
    json toJSON(void);
    private:
    int index;
    string previousHash;
    string blockHash;
    string nonce;
    vector<string> data;
};

// constructor function; initialize block
Block::Block(int index, string prevHash, string hash, string nonce, vector<string> data){
    printf("\nInitializing Block: %d ---- Hash: %s \n", index, hash.c_str());
    this -> previousHash = prevHash;
    this -> data = data;
    this -> index = index;
    this -> nonce = nonce;
    this -> blockHash = hash;
}

// get the index of a block
int Block::getIndex(void){
    return this -> index;
}

// get the previous hash of a block
string Block::getPreviousHash(void){
    return this -> previousHash;
}

// get this block's hash
string Block::getHash(void){
    return this -> blockHash;
}

// get the data of the block
vector<string> Block::getData(void){
    return this -> data;
}

// print this block's data
void Block::printBlock(void){
    string dataString;
    for(int i = 0; i < data.size(); i++)
        dataString += data[i] + ", ";
    printf("\n----------------------------\n");
    printf("Block %d\nHash: %s\nPrevious Hash: %s\nContents: %s",
        index,this->blockHash.c_str(),this->previousHash.c_str(),dataString.c_str());
    printf("\n----------------------------\n");
}

// convert data to a json object and return it
json Block::toJSON(void){
    json j;
    j["index"] = this -> index;
    j["hash"] = this -> blockHash;
    j["previousHash"] = this -> previousHash;
    j["nonce"] = this -> nonce;
    j["data"] = this -> data;
    return j;
}
#endif
