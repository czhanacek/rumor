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
    std::vector<int> encryptment = encryptSegmentID("REDLINE", "HELLO");
    encryptment = weakEncryptSegmentID(encryptment, "GROUP");
    encryptment = weakEncryptSegmentID(encryptment, "SCHLEP");
    encryptment = weakDecryptSegmentID(encryptment, "GROUP");
    encryptment = weakDecryptSegmentID(encryptment, "SCHLEP");
    encryptment = decryptSegmentID(encryptment, "HELLO");
    thisNode.printChest();
}