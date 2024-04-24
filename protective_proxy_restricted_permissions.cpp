// protective proxy restricted permissions.cpp
#include <iostream>
#include <string>
#include <vector>

// Subject interface
class DatabaseAccess {
public:
    virtual void readData() = 0;
    virtual void writeData() = 0;
    virtual ~DatabaseAccess() {}
};

// Real subject
class RealDatabaseAccess : public DatabaseAccess {
public:
    void readData() override {
        std::cout << "Reading data from the Real database" << std::endl;
    }

    void writeData() override {
        std::cout << "Writing data to the Real database" << std::endl;
    }
};

// Proxy
class ProtectiveProxy : public DatabaseAccess {
private:
    DatabaseAccess* realAccess;
    std::vector<std::string> allowedRoles;

public:
    ProtectiveProxy(DatabaseAccess* realAccess, const std::vector<std::string>& allowedRoles)
        : realAccess(realAccess), allowedRoles(allowedRoles) {}

    void readData() override {
        if (checkPermissions("read")) {
        	std::cout << "in readData checkPermissions is passed in the ProtectiveProxy" << std::endl;
            realAccess->readData();
        } else {
            std::cout << "Access denied: You don't have permission to read data" << std::endl;
        }
    }

    void writeData() override {
        if (checkPermissions("write")) {
            realAccess->writeData();
        } else {
            std::cout << "Access denied: You don't have permission to write data" << std::endl;
        }
    }

private:
    bool checkPermissions(const std::string& operation) {
        // Check if the user has permission based on their role
        if (operation == "read") {
            for (const auto& role : allowedRoles) {
                if (role == "admin" || role == "editor") {
                    return true;
                }
            }
        } else if (operation == "write") {
            for (const auto& role : allowedRoles) {
                if (role == "admin") {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    // Create a real database access object
    DatabaseAccess* realAccess = new RealDatabaseAccess();

    // Create a protective proxy with restricted permissions
    std::vector<std::string> usersimpleRoles = { "simple_user"};
    DatabaseAccess* proxy = new ProtectiveProxy(realAccess, usersimpleRoles);

    // Try to read and write data with the proxy
    proxy->readData();
    proxy->writeData();

	// Simulate user roles
	std::vector<std::string> userAdminRoles = {"admin", "editor"};
    proxy = new ProtectiveProxy(realAccess, userAdminRoles);
 	// Try to read and write data with the proxy
    proxy->readData();
    proxy->writeData();

	std::vector<std::string> usereditorRoles = {"editor"};
    proxy = new ProtectiveProxy(realAccess, usereditorRoles);
 	// Try to read and write data with the proxy
    proxy->readData();
    proxy->writeData();

    // Clean up
    delete realAccess;
    delete proxy;
    return 0;
}
