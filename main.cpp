#include "KnowingNode.hpp"



int main(void) {
    // discover a knowing node
    std::cout << "Hooray" << std::endl;
    std::unique_ptr<KnowingNode> thisNode = std::make_unique<KnowingNode>("HELLO");
    thisNode->insertInbound("GROUP");
    thisNode->insertOutbound("GREP");
    thisNode->insertWaypoint("GREP", "GROUP");
    thisNode->insertInbound("CHILL");
    thisNode->printChest();
    thisNode.reset();
}