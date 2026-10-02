#include "oystercatcher.h"



Oystercatcher::Oystercatcher(int ID,
                             bool mated,
                             int eggNum,
                             int chickNum,
                             int age,
                             int nest_x,
                             int nest_y,
                             int indiv_x,
                             int indiv_y,
                             int matedWithID,
                             bool isDead)
{
    oystercatcherID = ID;
    isMated = mated;
    eggAmount = eggNum;
    chickAmount = chickNum;
    oystercatcherAge= age;
    xcoord= nest_x;
    ycoord = nest_y;
    indivCoordX = indiv_x;
    indivCoordY = indiv_y;
    mateID = matedWithID;
    Dead = isDead;

}


// If the Oystercatchers are mated and one is at least 3 years, then once per year (avg April time = approx 100 days into the year),
// 2-4 eggs will be laid, and eggNum args are updated for each Oystercatcher and their mate
void Oystercatcher::reproduction(int time, std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);


    if (time % 365 == 100) { // if it is around April time each year

        float randomNum = random_0_1(mt);

        // Oystercatchers can only start to reproduce by 3 years of age
        if (oystercatcherVector[b].getAge() >= 3 &&
            oystercatcherVector[b].getIsDead() == false && // Making sure Oystercatcher is still living
            oystercatcherVector[oystercatcherVector[b].getMateIndex()].getIsDead() == false && // Making mate is still alive
            oystercatcherVector[oystercatcherVector[b].getMateIndex()].getEggNum() == 0 && // Making sure they haven't already laid eggs with mate (prevents repeats in for-loop)
            oystercatcherVector[b].getMateStatus() == true) { // Making sure Oystercatcher is mated to be able to reproduce
            if (randomNum < 0.33) { // 33% chance to lay 2 eggs
                oystercatcherVector[b].setEggNum(2);
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setEggNum(2);
            } else if (randomNum < 0.67) { // 33% chance (33% =< x < 67%) to lay 3 eggs
                oystercatcherVector[b].setEggNum(3);
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setEggNum(3);
            } else { // 33% chance ( 67% =< x =< 100%) to lay 4 eggs
                oystercatcherVector[b].setEggNum(4);
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setEggNum(4);
            }
        }

    }
}


// Checks if Oystercatcher has eggs and if they aren't dead, then returns true or false accordingly
// - important for parentDefence()
bool Oystercatcher::eggCare(std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    if (oystercatcherVector[b].getEggNum() > 0 &&
        oystercatcherVector[b].getIsDead() == false) {
        return true;
    } else {
        return false;
    }

}


// Checks if there are no eggs to care for but only chicks as well as if the parent is still living, then returns true or false accordingly
// - important for parentDefence()
bool Oystercatcher::chickCare(std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    if (oystercatcherVector[b].getEggNum() == 0 &&
        oystercatcherVector[b].getChickNum() > 0  &&
        oystercatcherVector[b].getIsDead() == false) {
        return true;
    } else {
        return false;
    }

}


// Adult Oystercatchers attempt to ward off dogs, has some percentage of being successful.
// If unsuccessful then dogs can eat eggs or predate chicks based on the situation.
// Chances of success depend on if there is a presence of eggs (increased success), or if there is a presence of chicks (decreased success),
// there cannot be eggs and chicks at the same time as eggs hatch synchronously altogether.
float Oystercatcher::parentDefence(std::vector<Oystercatcher> &oystercatcherVector, int b, float predSuccessPercentage) {
    if (eggCare(oystercatcherVector, b) == true) {
        // Decreasing predation success certain amount, as 1 parent is assumed to be there to defend the nest
        predSuccessPercentage = predSuccessPercentage * 0.5;
    }
    if (chickCare(oystercatcherVector, b) == true) {
        // Decrease predation success certain amount, since parents are with chicks to defend and there is a possibility of chicks
        // escaping as they are mobile
        predSuccessPercentage = predSuccessPercentage * 0.33;
    }
    return predSuccessPercentage;
}


// Each oystercatcher ages 1 year at the time of hatching (Avg 25 days after laying), and dies once they age over
// 13 (Avg lifespan of Oystercatchers in the wild)
void Oystercatcher::birthday(int time, std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    if (time % 365 == 125) {
        oystercatcherVector[b].setAge(oystercatcherVector[b].getAge()+1);
    }

    if( oystercatcherVector[b].getAge() > 13) {
        death(oystercatcherVector, b);
    }
}


// Kills off Oystercatcher, but doesn't remove them from the Oystercatcher vector to prevent mating mechanic bugs
void Oystercatcher::death(std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    // setting the oystercatcher to dead
    oystercatcherVector[b].setIsDead(true);

    // If both the target oystercatcher and its mate are dead, then no more eggs or chicks an survive, otherwise the mate still keeps the eggs and
    // chicks along with the target for correct egg and chick-counting in the model
    if (oystercatcherVector[oystercatcherVector[b].getMateID()].getIsDead() == true) {

        oystercatcherVector[oystercatcherVector[b].getMateID()].setEggNum(0);
        oystercatcherVector[oystercatcherVector[b].getMateID()].setChickNum(0);

        oystercatcherVector[b].setEggNum(0);
        oystercatcherVector[b].setChickNum(0);
    }
}


// Eggs hatch into chicks 25 days after hatching (100 + 25 = 125), args for Oystercatcher are updated accordingly
void Oystercatcher::eggHatch(int time, std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    if (time % 365 == 125) {
        oystercatcherVector[b].setChickNum(oystercatcherVector[b].getEggNum());
        oystercatcherVector[b].setEggNum(0);
    }
}





