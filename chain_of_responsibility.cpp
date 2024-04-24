// chain_of_responsibility_pattern.cpp
#include <iostream>
#include <string>

// Base handler interface
class Approver {
public:
    virtual void setSuccessor(Approver* successor) = 0;
    virtual void processRequest(double amount) = 0;
    virtual ~Approver() {}
};

// Concrete handler
class Manager : public Approver {
private:
    Approver* successor;
    double spendingLimit;
    std::string name;

public:
    Manager(const std::string& name, double spendingLimit)
        : successor(nullptr), name(name), spendingLimit(spendingLimit) {}

    void setSuccessor(Approver* successor) override {
        this->successor = successor;
    }

    void processRequest(double amount) override {
        if (amount <= spendingLimit) {
            std::cout << name << " approves the purchase of $" << amount << std::endl;
        } else if (successor != nullptr) {
            std::cout << name << " cannot approve the purchase of $" << amount << ". Passing to the next level." << std::endl;
            successor->processRequest(amount);
        } else {
            std::cout << "No one can approve the purchase of $" << amount << ". It exceeds the spending limit." << std::endl;
        }
    }
};

int main() {
    // Create managers with different spending limits
    Manager* manager1 = new Manager("Manager 1", 1000);
    Manager* manager2 = new Manager("Manager 2", 5000);
    Manager* manager3 = new Manager("Manager 3", 10000);

    // Set up the chain of responsibility
    manager1->setSuccessor(manager2);
    manager2->setSuccessor(manager3);

    // Process purchase requests
    manager1->processRequest(800);  // Manager 1 approves
    manager1->processRequest(6000); // Manager 2 approves
    manager1->processRequest(15000);// Manager 3 approves
    manager1->processRequest(200);  // manager 1 can approve
    manager1->processRequest(20000);  // anyone can approve?

    // Clean up
    delete manager1;
    delete manager2;
    delete manager3;

    return 0;
}
