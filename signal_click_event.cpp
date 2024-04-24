// signal_click_event.cpp Using Boost Signal2
#include <iostream>
#include <boost/signals2.hpp>
using namespace std;
class Button {
public:
    using ClickHandler = boost::signals2::signal<void()>; 
    //alias ClickHandler for the type boost::signals2::signal<void()>     // using Handler = ...: This is a C++11 alias declaration


    // Add a handler function to the signal
    // slot_type represents the type of function object that can be connected to the signal.
    // Passing by reference avoids unnecessary copying of the function object function whle object is not modified accidentally within
    void add_handler(const ClickHandler::slot_type& handler) {
    	cout<< "In add_handler of class Button:" << &handler<< endl;
        click_signal.connect(handler);
    }

    // Remove a handler function from the signal
    void remove_handler(const ClickHandler::slot_type& handler) {
        //click_signal.disconnect(handler);
    }

    // Simulate a mouse click on the button
    void click() { 
        std::cout << "Button clicked!\n";
        click_signal();
    }

private:
    ClickHandler click_signal; // Signal for click events
};

int main() {
    // Create a button instance
    Button button;

    // Add a handler function to the button
    button.add_handler([]() {
        std::cout << "Handler Func 1: Button clicked event received\n";
    });

    // Add another handler function to the button
    button.add_handler([]() {
        std::cout << "Handler Func 2: Button clicked event received\n";
    });

    // Simulate a mouse click on the button
    button.click(); //both registered handler functions are invoked

    return 0;
}
