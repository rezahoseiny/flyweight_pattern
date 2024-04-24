// event_handler_using_boost_signal.cpp

#include <iostream>
#include <boost/signals2.hpp>
#include <unistd.h>
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

// Define an interface for event data
class IEventData {
public:
    virtual void print() const = 0;
    virtual ~IEventData() {}
    virtual int getID() const = 0;
    virtual const std::string& getMessage() const= 0;
};

 

// Define an event data structure // Define a concrete implementation of the interface
struct ConcreteEventData : IEventData {
    int id;
    std::string message;
    ConcreteEventData(int idx, const std::string m) : id(idx), message(m) {}
    void print() const override
	 {
	 	std::cout << "In Concrete Event Data! ( id = " << id << " message= " << message << ")" << "\n";
	 }

	int getID() const override{
		return id;
	}

	const std::string&  getMessage() const override{
		return this->message;	
	}	 
};

// Define a type alias for the signal
using EventSignal = boost::signals2::signal<void(const IEventData*)>;

// Function to handle event
void eventHandler(const IEventData* eventData) {
	std::cout << AC_RED ;
    std::cout << "First Event Handler: Received EventData with ID " << eventData->getID() << " and message: " << eventData->getMessage() << std::endl;    
    std::cout<<AC_NORMAL;    
    eventData->print();
    sleep(2);
}

void second_eventHandler(const IEventData* eventData) {
    std::cout << AC_YELLOW ;
    std::cout << "Second Funciton for Handling EventData: event with ID " << eventData->getID() << " and message: "<< eventData->getMessage() << std::endl;
    std::cout<<AC_NORMAL;
    eventData->print();
    sleep(3);
}

void third_eventHandler(const IEventData* eventData) {
    std::cout << AC_GREEN ;
    std::cout << "Third Funciton to Handle EventData: event with ID " << eventData->getID()  << " and message: " << eventData->getMessage()  << std::endl;
    std::cout<<AC_NORMAL;
    eventData->print();
    sleep(4);
}

int main() {
    // Create an instance of the signal
    EventSignal eventSignal;

    // Connect event handler to the signal
    eventSignal.connect(&eventHandler);
    eventSignal.connect(&second_eventHandler);
    eventSignal.connect(&third_eventHandler);

    // Create event data
    IEventData * d1 = new ConcreteEventData(1, "First event");
    IEventData * d2 =  new ConcreteEventData( 2, "Second event");
    // Trigger the two events
    eventSignal(d1);    
    sleep(3);
    eventSignal(d2);
    return 0;
}
