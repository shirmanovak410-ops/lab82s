//
// Created by Ксения on 26.05.2026.
//
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <fstream>

class Car {
protected:
    std::string model;
    int maxSpeed;

public:
    Car(const std::string& modelName = "", int speed = 0)
        : model(modelName), maxSpeed(speed) {}

    virtual void print() const {
        std::cout << "Car: " << model
                  << " V: " << maxSpeed;
    }

    void printStatic() const {
        std::cout << "Car: " << model
                  << " V: " << maxSpeed;
    }

    std::string getModel() const {
        return model;
    }

    int getMaxSpeed() const {
        return maxSpeed;
    }

    bool operator<(const Car& other) const {
        if (model != other.model) {
            return model < other.model;
        }
        return maxSpeed < other.maxSpeed;
    }

    bool operator==(const Car& other) const {
        return model == other.model && maxSpeed == other.maxSpeed;
    }

    virtual ~Car() {}
};

class Bus : public Car {
private:
    int passengerCapacity;

public:
    Bus(const std::string& modelName = "", int speed = 0, int capacity = 0)
        : Car(modelName, speed), passengerCapacity(capacity) {}

    void print() const override {
        Car::print();
        std::cout << " passengers: " << passengerCapacity;
    }

    void printStatic() const {
        Car::printStatic();
        std::cout << " passengers: " << passengerCapacity;
    }

    int getPassengerCapacity() const {
        return passengerCapacity;
    }
};

struct CarHasher {
    std::size_t operator()(const Car& car) const {
        std::hash<std::string> stringHasher;
        std::hash<int> intHasher;

        return stringHasher(car.getModel()) ^ (intHasher(car.getMaxSpeed()) << 1);
    }
};

int main() {
    std::set<Car> orderedCars;
    std::unordered_set<Car, CarHasher> unorderedCars;

    std::ifstream fin("input");

    if (!fin.is_open()) {
        std::cout << "File input was not opened" << std::endl;
        return 1;
    }

    std::string type;
    std::string model;
    int speed;

    while (fin >> type >> model >> speed) {
        if (type == "Car") {
            Car car(model, speed);

            orderedCars.insert(car);
            unorderedCars.insert(car);
        }
        else if (type == "Bus") {
            int capacity;
            fin >> capacity;

            Bus bus(model, speed, capacity);

            orderedCars.insert(bus);
            unorderedCars.insert(bus);
        }
    }

    fin.close();

    std::cout << "Objects from set:" << std::endl;
    for (const auto& car : orderedCars) {
        car.print();
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Objects from unordered_set:" << std::endl;
    for (const auto& car : unorderedCars) {
        car.print();
        std::cout << std::endl;
    }

    std::cout << std::endl;

    Car car("Skoda", 280);
    Bus bus("Volvo", 120, 45);
    Car* ptr;

    std::cout << "Static polymorphism:" << std::endl;

    car.printStatic();
    std::cout << std::endl;

    bus.printStatic();
    std::cout << std::endl;

    std::cout << std::endl;

    std::cout << "Dynamic polymorphism:" << std::endl;

    ptr = &car;
    ptr->print();
    std::cout << std::endl;

    ptr = &bus;
    ptr->print();
    std::cout << std::endl;

    return 0;
}