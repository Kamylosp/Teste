#pragma once
#include <string>

class Car {
    private:
        double power;
        double price;
        double speed = 0;

    public:
        Car();
        Car(double _power, double _price);

        Car & operator=(const Car & obj);
        ~Car();
        
        double getPower ();
        double getPrice ();
        // void setPower (double pot);
        // void setPrice (double preco);

        Car &setPower (double pot);
        Car &setPrice (double preco);

        Car operator+ (const Car &obj);
        
        void printAdress();
        void showInfo () const;

        double getSpeed();
        void setSpeed(double spd);

        void acelerate(double newSpeed);
        void acelerate(int newSpeed);
        void acelerate(std::string maxmin);
        void acelerate(double timeAcell, double acellerate);
        void acelerate(char *newSpeed);

};
