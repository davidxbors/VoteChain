# VoteChain

## TODO
* add readme sections for blockchain.h, common.h, hash.h
* modify common/findHash() to be able to find nonce for any difficulty
* p2p adjustable difficulty updated to the power of the network

## Abstract

An online voting system, that uses blockchain to ensure the security and transparency of the election being made using it.

It will use a peer-to-peer PoW blockchain similar to bitcoin's. The network timestamps transactions by hashing them into an ongoing chain of
hash-based proof-of-work, forming a record that cannot be changed without redoing the proof-of-work. The longest chain not only serves as proof of the sequence of events witnessed, but proof that it came from the largest pool of CPU power. As long as a majority of CPU power is controlled by nodes that are not cooperating to attack the network, they'll generate the longest chain and outpace attackers. The
network itself requires minimal structure.


## BlockChain

### Block

A block is a chunk of data. Each block has in it an index, the hash of a previous block from the blockchain, the data it's created to contain, a nonce for mining reasons and the hash of the block.

A block contains a given number of vote actions. Each vote action needs to be signed by the voters.

### BlockChain

### Hash

### Common

## More to come

I just started to work on this project, more will come as I'm working on it.

## Contact

For any suggestions don't hesitate to commit to this project or contact me @ daviddvd267@gmail.com.
