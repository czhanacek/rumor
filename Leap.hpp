#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

class Leap {
    private:
        std::string f;
        std::string t;
    public:
        Leap();
        Leap(std::string from_addr, std::string to_addr);
        std::string from();
        std::string to();
        const std::string combinedAddrs();
};

class LeapNode {

    private:
        std::unique_ptr<LeapNode> left;
        std::unique_ptr<LeapNode> right;
        
    public: 
        LeapNode(std::unique_ptr<LeapNode> l, std::unique_ptr<LeapNode> r, std::unique_ptr<Leap> lp);
        bool insert(std::unique_ptr<Leap> leap);
        void print();
        bool search(std::unique_ptr<Leap> leap);
        bool cancel(std::unique_ptr<Leap> leap);
        std::unique_ptr<Leap> leap;
        static int compare(Leap * l, LeapNode * r);

    
    
};


class LeapChest {
    private:
        std::unique_ptr<LeapNode> root;
        int count;
    public:
        LeapChest();
        void print();
        bool insert(std::unique_ptr<Leap> lp);
        bool get(std::unique_ptr<Leap> lp);
        bool cancel(std::unique_ptr<Leap> lp);


};