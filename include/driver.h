#ifndef __DRIVER_H
#define __DRIVER_H

class Driver {
public:
    Driver();
    ~Driver();

    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();

};

class DriverManager {
public:
    DriverManager();
    void AddDriver(Driver* );
    void ActivateAll();

    Driver* drivers[256];
    int numDrivers;
};
#endif
