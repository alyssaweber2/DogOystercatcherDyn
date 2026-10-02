#ifndef DOG_H
#define DOG_H

#include <random>
#include <oystercatcher.h>

class Dog
{
public:

    Dog(bool leashed,
        bool preyDrive,
        int dailyX,
        int dailyY);



    // Getter methods
    bool getLeashed() { return isLeashed; }
    bool getPreyDrive() { return hasPreyDrive; }
    int getDailyX() { return xCoord; }
    int getDailyY() { return yCoord; }

    // Setter methods
    void setLeashed(bool leashed) { isLeashed = leashed; }
    void setPreyDrive(bool preyDrive) { hasPreyDrive = preyDrive; }
    void setDailyX (int dailyX) { xCoord = dailyX; }
    void setDailyY (int dailyY) { yCoord = dailyY; }

    // Dog spots Oystercatcher individual with chance of taking interest, can lead to huntAdult() or huntChick()
    void spotOystercatcher(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector);

    // Dog spots Oystercatcher nest with chance of taking interest, can lead to eatEgg() or huntAdult()
    void spotNest(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector);


private:

    // *** METHODS

    // Dog attempts to predate on adult Oystercatcher with certain chance of succeeding
    void huntAdult(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Dog attempts to eat egg(s) in the nest, with probability that they will eat all or some, or be fought off by parent defence
    void eatEgg(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Dog attempts predation after spotting chick (not in nest anymore, but accompanied by parents)
    void huntChick(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b);


    // *** VARIABLES & PARAMS:

    // Variables directly tied to Dog arguments and getter/setter functions
    bool isLeashed;
    bool hasPreyDrive;
    int xCoord;
    int yCoord;

    // on-leash spotting radius
    int onleashRad = 5;

    //off-leash spotting radius
    int offleashRad = 25;



    // Chances of dog taking an interest in hunting Oystercatcher - important for spotOystercatcher() and spotNest()
    // Ordered from highest to lowest chances:
    float offleashPreyDriveInterest = 0.18; // off-leash dogs with high prey drive chance of interest, for adult or chick
    float onleashPreyDriveInterest = 0.15; //on-leash dogs with high prey drive chance of interest, for adult or chick
    float offleashEggInterest = 0.12; // off-leash dogs chance of interest in eggs (prey drive doesn't matter here)
    float onleashEggInterest = 0.1; // on-leash dogs chance of interest in eggs (prey drive doesn't matter here)
    float offleashLowPreyDriveInterest = 0.05; // off-leash low prey drive chance of interest, for adult or chick
    float onleashLowPreyDriveInterest = 0.02; // on-leash low prey drive chance of interest, for adult or chick



    // Chances of success of predation of an Oystercatcher/egg - important for eatEgg(), huntChick() and huntAdult()
    // These are also ordered from highest to lowest chances:
    float offleashPreyDrivePredation = 0.2; // off-leash dogs with high prey drive have highest chance of success
    float onleashPreyDrivePredation = 0.1; // on-leash dogs with high prey drive have slightly lower chance of success due to control from owner
    float offleashEggEating = 0.12; // Regardless of prey drive, off-leash dog will have certain chance to eat an egg
    float onleashEggEating = 0.1; // Regardless of prey drive, on-leash dog will have chance to eat egg
    float offleashLowPreyDrivePredation = 0.07; // Off-leash low prey drive dogs chance of success
    float onleashLowPreyDrivePredation = 0.03;// On-leash low prey drive dogs have lowest chance due to low prey drive and increased owner control



    //Random number generator objects
    std::mt19937 mt;
    std::uniform_real_distribution<float> random_0_1;



};

#endif // DOG_H
