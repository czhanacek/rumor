
#include "KnowingNode.hpp"
#include "FileSegment.hpp"

KnowingNode::KnowingNode(std::string & address, int16_t size, int16_t leaf_vault_size) {
    this->addr = address;
    this->s = size;
}
KnowingNode::KnowingNode(std::string address) : KnowingNode(address, DEFAULT_SIZE, DEFAULT_LEAP_VAULT) {
    
}

std::string & KnowingNode::getAddr() {
    return this->addr;
}


void KnowingNode::insertInbound(std::string from_addr) {
    if(this->addr != from_addr) {
        this->lc.insert(std::move(std::make_unique<Leap>(from_addr, getAddr())));
    }
}

bool KnowingNode::passRequest(std::string from_addr, std::string to_addr) {
    std::unique_ptr<Leap> testLeap = std::make_unique<Leap>(from_addr, to_addr);
    if(this->lc.get(std::move(testLeap))) {
        std::cout << "Passing request to " << to_addr << std::endl;
    }
    else {
        std::cout << "Unable to pass request to " << to_addr << std::endl;
    }
}

void KnowingNode::insertOutbound(std::string to_addr) {
    if(to_addr != this->addr) {
        this->lc.insert(std::move(std::make_unique<Leap>(getAddr(), to_addr)));
    }   
}

void KnowingNode::insertWaypoint(std::string to_addr, std::string from_addr) {
    if(to_addr != this->addr && from_addr != this->addr) {
        this->lc.insert(std::move(std::make_unique<Leap>(from_addr, to_addr)));
    }

}
std::vector<int> encryptSegmentID(std::string segmentID, std::string address) {
    int largest = std::max(segmentID.size(), address.size());
    std::vector<int> cypherNumbers;
    for(int i = 0; i < largest; i++) {
        int segiter = i;
        int additer = i;
        if(segiter >= segmentID.size()) {
            segiter = segiter % segmentID.size();
        }
        if(additer >= address.size()) {
            additer = additer % address.size();
        }
        cypherNumbers.push_back(segmentID[segiter] * address[additer]);
    }
    
    return cypherNumbers;
}

std::vector<int> weakEncryptSegmentID(std::vector<int> segmentID, std::string address) {
    int largest = std::max(segmentID.size(), address.size());
    std::vector<int> cypherNumbers;
    for(int i = 0; i < largest; i++) {
        int segiter = i;
        int additer = i;
        if(segiter >= segmentID.size()) {
            segiter = segiter % segmentID.size();
        }
        if(additer >= address.size()) {
            additer = additer % address.size();
        }
        cypherNumbers.push_back(segmentID[segiter] + address[additer]);
    }
    
    return cypherNumbers;
}

std::vector<int> weakDecryptSegmentID(std::vector<int> encryptedString, std::string address) {
    for(int i = 0; i < encryptedString.size(); i++) {
        encryptedString[i] -= address[i % address.size()];
    }
    std::cout << std::endl;
    return encryptedString;

}

std::vector<int> decryptSegmentID(std::vector<int> encryptedString, std::string address) {
    for(int i = 0; i < encryptedString.size(); i++) {
        encryptedString[i] /= address[i % address.size()];
    }
    for(int i = 0; i < encryptedString.size(); i++) {
        std::cout << (char)encryptedString[i];
    } 
    std::cout << std::endl;
    return encryptedString;

}

void KnowingNode::printChest(void) {
    std::cout << "My address is " << this->getAddr() << std::endl;
    this->lc.print();
}