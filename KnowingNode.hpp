#include "Leap.hpp"

#define DEFAULT_SIZE 1024 // 1 gigabyte, smallest unit is 1 megabyte
#define DEFAULT_LEAP_VAULT 100 // 100 stored leaps by default

class KnowingNode {
    private: 
        std::string addr;
        int16_t s;
    public:
        KnowingNode(std::string & address, int16_t size, int16_t leap_vault_size);
        
        KnowingNode(std::string address);
        LeapChest lc;
        void insertOutbound(std::string to_addr);
        void insertInbound(std::string from_addr);
        void insertWaypoint(std::string to_addr, std::string from_addr);
        void printChest(void);
        std::string & getAddr(void);
        bool passRequest(std::string from_addr, std::string to_addr);

        
};