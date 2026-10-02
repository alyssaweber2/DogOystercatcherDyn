#ifndef OYSTERCATCHER_H
#define OYSTERCATCHER_H

#include <random>
#include <vector>
class Oystercatcher
{
public:
    Oystercatcher(int ID,
                  bool mated,
                  int eggNum,
                  int chickNum,
                  int age,
                  int nest_x,
                  int nest_y,
                  int indiv_x,
                  int indiv_y,
                  int matedWithID,
                  bool isDead);

    // Getter methods
    int getID() { return oystercatcherID; }
    bool getMateStatus() { return isMated; }
    int getEggNum() { return eggAmount; }
    int getChickNum() { return chickAmount; }
    int getAge() { return oystercatcherAge; }
    int getNestX() { return xcoord; }
    int getNestY() {return ycoord; }
    int getIndivX() {return indivCoordX; }
    int getIndivY() {return indivCoordY; }
    int getMateID() { return mateID; }
    int getMateIndex() { return (mateID - 1); }
    bool getIsDead() { return Dead; }


    // Setter methods
    void setID(int ID) { oystercatcherID = ID; }
    void setMateStatus(bool mated) { isMated = mated; }
    void setEggNum(int eggNum) { eggAmount = eggNum; }
    void setChickNum(int chickNum) { chickAmount = chickNum; }
    void setAge(int age) { oystercatcherAge = age; }
    void setNestCoordX(int nest_x) {  xcoord = nest_x; }
    void setNestCoordY(int nest_y) { ycoord = nest_y; }
    void setIndivX (int indiv_x) { indivCoordX = indiv_x; }
    void setIndivY (int indiv_y) { indivCoordY = indiv_y; }
    void setMateID(int matedWithID) { mateID = matedWithID; }
    void setIsDead(bool isDead) { Dead = isDead; }


    // Egg-laying -> increases number of eggs mated pair has
    void reproduction(int time, std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Increased chance for nest protection (aka parent defence) since at least one parent is present
    bool eggCare(std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Even more increased chance for protection (parent defence) due to both parents being present and everyone is mobile
    bool chickCare(std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Adult Oystercatchers attempt to ward off dogs, decreases the dogs chance of predation success
    float parentDefence(std::vector<Oystercatcher> &oystercatcherVector, int b, float predSuccessPercentage);

    // Oystercatchers age 1 year after a year has passed from their birth
    void birthday(int time, std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Oystercatcher dies, can be either from predation or aging
    void death(std::vector<Oystercatcher> &oystercatcherVector, int b);

    // Eggs hatch, turning into chicks (updates the egg and chick arguments in the Oystercatcher vector)
    void eggHatch(int time, std::vector<Oystercatcher> &oystercatcherVector, int b);


private:

    // *** VARIABLES & PARAMS:

    // Oystercatcher argument variables for getter and setter functions
    int oystercatcherID;
    bool isMated;
    int eggAmount;
    int chickAmount;
    int oystercatcherAge;
    int xcoord;
    int ycoord;
    int indivCoordX;
    int indivCoordY;
    int mateID;
    bool Dead;

    // RNG-related objects
    std::mt19937 mt;
    std::uniform_real_distribution<float> random_0_1;

};


#endif // OYSTERCATCHER_H
