#ifndef BLOCKCHAIN_H
#define BLOCHCHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "hash.hpp"
#include "Block.hpp"
#include "json.hh"
#include "common.hpp"

using json = nlohmann::json;

class BlockChain {
    public:
    BlockChain(int genesis = 1);
    Block getBlock(int index);
    int getNoBlocks(void);
    int addBlock(int index, string prevHash, string hash, string nonce, vector<string> &merkle);
    string getLatestBlockHash(void);
    string toJSON(void);
    int replaceChain(json chain);
    private:
    vector<unique_ptr<Block>> blockchain;
};

BlockChain::BlockChain(int genesis){
    if(genesis == 0){
        vector<string> v;
        v.push_back("Genesis Block!");
        auto hash_nonce_pair = findHash(0, string("00000000000000"), v);
        this -> blockchain.push_back(std::make_unique<Block>(0, string("00000000000000"), hash_nonce_pair.first, hash_nonce_pair.second, v));
        printf("Created blockchain!\n");
    }
}

Block BlockChain::getBlock(int index){
    for(int i = 0; i < blockchain.size(); i++){
        if(blockchain[i]->getIndex() == index){
            return *(blockchain[i]);
        }
    }
    throw invalid_argument("Index does not exist!");
}

int BlockChain::getNoBlocks(void){
    return this -> blockchain.size();
}

int BlockChain::addBlock(int index, string prevHash, string hash, string nonce, vector<string> &merkle){
    string header = to_string(index) + prevHash + getMerkleRoot(merkle) + nonce;
    if((!sha256(header).compare(hash)) && (hash.substr(0,2) == "00") && (index == blockchain.size())){
        printf("Block hashes match --- Adding Block %s \n", hash.c_str());
        this->blockchain.push_back(std::make_unique<Block>(index, prevHash, hash, nonce, merkle));
        return 1;
    }
    cout << "Hash doesn't match!\n";
    return 0;
}

string BlockChain::getLatestBlockHash(void){
    return this -> blockchain[blockchain.size() - 1] -> getHash();
}

string BlockChain::toJSON() {
    json j;
    j["length"] = this -> blockchain.size();
    for(int i = 0; i < this -> blockchain.size(); i++){
        j["data"][this->blockchain[i]->getIndex()] = this->blockchain[i]->toJSON();
    }
    return j.dump(3);
}

int BlockChain::replaceChain(json chain){
    while(this -> blockchain.size() > 1){
        this -> blockchain.pop_back();
    }
    for(int i = 1; i < chain["length"].get<int>(); i++){
        auto block = chain["data"][i];
        vector<string> data = block["data"].get<vector<string>>();
        this -> addBlock(block["index"], block["previousHash"], block["hash"], block["nonce"], data);
    }
    return 1;
}

#endif