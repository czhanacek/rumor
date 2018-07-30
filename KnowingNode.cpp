
#include "KnowingNode.hpp"
#include "FileSegment.hpp"

KnowingNode::KnowingNode(std::string address, int16_t size, int16_t leaf_vault_size) {
    this->addr = address;
    std::cout << "set addr to " << this->addr << std::endl;
    this->s = size;
    std::vector<FileSegment> filestore;
}
KnowingNode::KnowingNode(std::string address) {
    KnowingNode(address, DEFAULT_SIZE, DEFAULT_LEAP_VAULT);
}

std::string KnowingNode::getAddr() {
    return this->addr;
}


void KnowingNode::insertInbound(std::string from_addr) {
    if(this->addr != from_addr) {
        this->lc.insert(std::move(std::make_unique<Leap>(from_addr, this->addr)));
    }
}

void KnowingNode::insertOutbound(std::string to_addr) {
    if(to_addr != this->addr) {
        this->lc.insert(std::move(std::make_unique<Leap>(this->addr, to_addr)));
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