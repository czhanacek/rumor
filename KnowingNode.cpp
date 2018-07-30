
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

void KnowingNode::printChest(void) {
    std::cout << "My address is " << this->getAddr() << std::endl;
    this->lc.print();
}