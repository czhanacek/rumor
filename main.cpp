#include "KnowingNode.hpp"



int main(void) {
    // "discover" a knowing node
    std::cout << "Hooray" << std::endl;
    KnowingNode thisNode = KnowingNode("HELLO");
    thisNode.insertInbound("GROUP");
    thisNode.insertOutbound("GREP");
    thisNode.insertWaypoint("GREP", "GROUP");
    thisNode.insertInbound("CHILL");
    thisNode.passRequest("HELLO", "BAH");
    thisNode.printChest();
}