

#include "Leap.hpp"

LeapNode::LeapNode(std::unique_ptr<LeapNode> l, std::unique_ptr<LeapNode> r, std::unique_ptr<Leap> lp) {
    this->left = std::move(l);
    this->right = std::move(r);
    this->leap = std::move(lp);
}
int factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int count_smaller_than_cur(std::string & s, int ind) {
    int count = 0;
    for(int i = ind+1; i < s.size(); ++i)
        if(s[i] < s[ind])
            count++;
    return count;
}


const std::string Leap::combinedAddrs() {
    return std::string(this->t + this->f);
}

int LeapNode::compare(Leap *l, LeapNode *right) {
    int lscore = 0;
    int rscore = 0;

    int r = 1;
    int len = l->combinedAddrs().size();
    int f = factorial(len);

    for(int i=0; i < len; ++i) {
        f /= (len-i);
        std::string s = l->combinedAddrs();
        int t = count_smaller_than_cur(s, i);
        r += t*f;
    }

    lscore = r;
    
    r = 1;
    len = right->leap->combinedAddrs().size();
    f = factorial(len);

    for(int i=0; i < len; ++i) {
        f /= (len-i);
        std::string s = right->leap->combinedAddrs();
        int t = count_smaller_than_cur(s, i);
        r += t*f;
    }

    rscore = r;

    return lscore - rscore; // should rank earlier scores higher left to right;
}


bool LeapNode::insert(std::unique_ptr<Leap> leap) {
    if(compare(leap.get(), this) > 0) {
        if(this->left == nullptr) {
            this->left = std::make_unique<LeapNode>(nullptr, nullptr, std::move(leap));
        }
        else {
            this->left->insert(std::move(leap));
        }
    }
    else if(compare(leap.get(), this) < 0) {
        if(this->right == nullptr) {
            this->right = std::make_unique<LeapNode>(nullptr, nullptr, std::move(leap));
        }
        else {
            this->right->insert(std::move(leap));
        }
    }
    else if(compare(leap.get(), this) == 0 || this->leap == nullptr) {
        this->leap = std::move(leap);
    }
    
} 

bool LeapNode::search(std::unique_ptr<Leap> leap) {
    if(LeapNode::compare(leap.get(), &(*this)) == 0) {
        return true;
    }
    else if(LeapNode::compare(leap.get(), &(*this)) < 0) {
        if(this->right == nullptr) {
            return false;
        }
        else {
            return this->right->search(std::move(leap));
        }
        if(this->left == nullptr) {
            return false;
        }
        else {
            return this->left->search(std::move(leap));
        }
    }
    
}

bool LeapNode::cancel(std::unique_ptr<Leap> leap) {
    if(this->left != nullptr && LeapNode::compare(leap.get(), this->left.get()) == 0) {
        this->left.release();
    } else if(this->left != nullptr && LeapNode::compare(leap.get(), this->left.get()) > 0){
        this->left->cancel(std::move(leap));
    }

    if(this->right != nullptr && LeapNode::compare(leap.get(), this->right.get()) == 0) {
        this->right.release();
    } else if(this->right != nullptr && LeapNode::compare(leap.get(), this->right.get()) < 0){
        this->right->cancel(std::move(leap));
    }
    return true;
}

std::string Leap::from() {
    return this->f;
}

std::string Leap::to() {
    return this->t;
}

Leap::Leap(std::string from_addr, std::string to_addr) {
    this->f = from_addr;
    this->t = to_addr;
}

Leap::Leap() {
    this->f = "null";
    this->t = "null";
}

void LeapNode::print() {
    if(this->left != nullptr) {
        this->left->print();
    }
    std::cout << "---------------------------" << std::endl;
    std::cout << "From: " << this->leap->from() << std::endl;
    std::cout << "To: " << this->leap->to() << std::endl;
    std::cout << "---------------------------" << std::endl;
    if(this->right != nullptr) {
        this->right->print();
    }
    
}

LeapChest::LeapChest() {
    this->root = nullptr;
    
}

bool LeapChest::insert(std::unique_ptr<Leap> leap) {
    if(this->root == nullptr) {
        this->root = std::make_unique<LeapNode>(nullptr, nullptr, std::move(leap));
    }
    else {
        this->root->insert(std::move(leap));
    }
    count += 1;
}

bool LeapChest::get(std::unique_ptr<Leap> leap) {
    if(this->root == nullptr) {
        return false;
    }
    else {
        this->root->search(std::move(leap));
    }
}

void LeapChest::print() {
    this->root->print();
}

bool LeapChest::cancel(std::unique_ptr<Leap> leap) {
    if(this->root != nullptr && LeapNode::compare(leap.get(), this->root.get()) == 0) {
        this->root.release();
    }
    else {
        this->root->cancel(std::move(leap));
    }
    count += 1;
}