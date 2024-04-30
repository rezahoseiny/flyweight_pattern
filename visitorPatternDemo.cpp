#include <iostream>
#include <vector>
#include <sstream>
// Forward declaration of classes
class Circle;
class Rectangle;
class CompoundGraphic;
// Abstract Visitor class
class Visitor {
public:
    virtual void visit(Circle* shape) = 0;
    virtual void visit(Rectangle* shape) = 0;
    virtual void visit(CompoundGraphic* graphic) = 0;
};
// Abstract Shape/Graphic class
class Shape {
public:
    virtual void accept(Visitor* visitor) = 0;
};

// Concrete Circle class
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getRadius() const {
        return radius;
    }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
// Concrete Rectangle class
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};
// Concrete CompoundGraphic class
class CompoundGraphic : public Shape {
private:
    std::vector<Shape*> graphics;

public:
    void add(Shape* graphic) {
        graphics.push_back(graphic);
    }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    const std::vector<Shape*>& getGraphics() const {
        return graphics;
    }
};

// Concrete XML Export Visitor class
class XMLExportVisitor : public Visitor {
private:
    std::stringstream xmlStream;

public:
    std::string getXML() const {
        return xmlStream.str();
    }

    void visit(Circle* shape) override {
        xmlStream << "<Circle><Radius>" << shape->getRadius() << "</Radius></Circle>\n";
    }

    void visit(Rectangle* shape) override {
        xmlStream << "<Rectangle><Width>" << shape->getWidth() << \
        "</Width><Height>" << shape->getHeight() << "</Height></Rectangle>\n";
    }

    void visit(CompoundGraphic* graphic) override {
        xmlStream << "<CompoundGraphic>\n";
        for (Shape* g : graphic->getGraphics()) {
            g->accept(this); // Delegate to accept() method of each child
        }
        xmlStream << "</CompoundGraphic>\n";
    }
};

// Client code
int main() {
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    CompoundGraphic group;
    group.add(&circle);
    group.add(&rectangle);

    XMLExportVisitor xmlVisitor;
    group.accept(&xmlVisitor);
	//XML Representation:
    std::cout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" << xmlVisitor.getXML();

    return 0;
}
