// mediator_pattern

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // for sleep function

// Forward declaration of Colleague class
class Colleague;

// Mediator interface
class Mediator {
public:
    virtual void sendMessage(const std::string& message, const Colleague*) const = 0;
};

// Colleague class
class Colleague {
protected:
    Mediator* mediator;
    std::string name;

public:
    explicit Colleague(const std::string& name, Mediator* m) : name(name), mediator(m) {}

    virtual void sendMessage(const std::string& message) const = 0;
    virtual void receiveMessage(const std::string& message) const = 0;
    const std::string& getName() const { return name; }
};

// Concrete Mediator class
class ChatRoom : public Mediator {
private:
    std::vector<Colleague*> colleagues;

public:
    void addColleague(Colleague* colleague) {
        colleagues.push_back(colleague);
    }

    void sendMessage(const std::string& message, const Colleague* sender) const override {
    	std::cout << "[" << sender->getName() << "]: " << message << std::endl;
        
        for (Colleague* col : colleagues) {
            if (col != sender) {
                col->receiveMessage(message);
            }
        }
    }
};

// Concrete Colleague class
class User : public Colleague {
public:
    explicit User(const std::string& name, Mediator* m) : Colleague(name,m) {}

    void sendMessage(const std::string& message) const override {
    	std::cout << this << "\t" << this->name << "\tsend a message to others " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    void receiveMessage(const std::string& message) const override {
        std::cout << "[" << name << " received]: " << "Received message: " << message << "\tBy: " << this << std::endl;
    }
};

int main() {
    // Create mediator
    ChatRoom mediator;

    // Create colleagues
    User colleague1("Alice", &mediator);
    User colleague2("Bob", &mediator);
    User c3("User Name 3", &mediator);

    // Add colleagues to the mediator
    mediator.addColleague(&colleague1);
    mediator.addColleague(&colleague2);
    mediator.addColleague(&c3);

    // Send messages through the mediator
    colleague1.sendMessage("Hello from colleague 1");
    colleague2.sendMessage("Hi from colleague 2");
    sleep(5);
    c3.sendMessage("SALAM from colleague 3");

    return 0;
}
