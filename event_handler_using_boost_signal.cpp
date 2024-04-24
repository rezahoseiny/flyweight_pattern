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

// Define an event data structure
struct EventData {
    int id;
    std::string message;
};

// Define a type alias for the signal
using EventSignal = boost::signals2::signal<void(EventData*)>;

// Function to handle event
void eventHandler(EventData* eventData) {
	std::cout << AC_RED ;
    std::cout << "Event Handler: Received EventData with ID " << eventData->id << " and message: " << eventData->message << std::endl;
    std::cout<<AC_NORMAL;
}

void second_eventHandler(EventData* eventData) {
    std::cout << AC_YELLOW ;
    std::cout << "Another Funciton for Handling EventData: We Received event with ID " << eventData->id << " and message: " << eventData->message << std::endl;
    std::cout<<AC_NORMAL;
}

void third_eventHandler(EventData* eventData) {
    std::cout << AC_GREEN ;
    std::cout << "Third Funciton to Handle EventData: event with ID " << eventData->id << " and message: " << eventData->message << std::endl;
    std::cout<<AC_NORMAL;
}

int main() {
    // Create an instance of the signal
    EventSignal eventSignal;

    // Connect event handler to the signal
    eventSignal.connect(&eventHandler);
    eventSignal.connect(&second_eventHandler);
    eventSignal.connect(&third_eventHandler);

    // Create event data
    EventData eventData { 1, "First event" };
    EventData d2 { 2, "Second event" };

    // Trigger the event
    eventSignal(&eventData);
    std::cout<<std::endl;
    sleep(3);
    eventSignal(&d2);

    return 0;
}
