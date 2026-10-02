#include "dog.h"



Dog::Dog(bool leashed, bool preyDrive, int dailyX, int dailyY)
{
    isLeashed = leashed;
    hasPreyDrive = preyDrive;
    xCoord = dailyX;
    yCoord = dailyY;
}

// Dog spots Oystercatcher individual with chance of taking interest, can lead to huntAdult() or huntChick()
void Dog::spotOystercatcher(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector)
{
    for (unsigned long b = 0; b < oystercatcherVector.size(); b ++) {


        // Rng objects:
        std::random_device rd;
        mt = std::mt19937(rd());
        random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

        float randomNum = random_0_1(mt);


        // Calculating pythagorean distance between each oystercatcher and each dog, then checking to see if its within the off-leash/on-leash
        // radii
        float dogPosX = dogVector[d].getDailyX(); // Getting X and Y coords for dog
        float dogPosY = dogVector[d].getDailyY();
        float oystercatcherPosX = oystercatcherVector[b].getIndivX(); // Getting X and Y coords for Oystercatcher
        float oystercatcherPosY = oystercatcherVector[b].getIndivY();

        float side1 = dogPosX - oystercatcherPosX; // Calculating the distance between the X and Y coords of the two individuals
        float side2 = dogPosY - oystercatcherPosY; // (essentially attaining lengths of sides a and b of theoretical triangle)

        float c = sqrt(pow(side1, 2) + pow(side2,2)); // Calculating distance between Oystercatcher and dog using pythagorean theorem



        // Checks if the dog is leashed and if the oystercatcher is within the on-leash radius
        if (dogVector[d].getLeashed() == true && c <= onleashRad) {
            // If on-leash dog has high prey drive and they take chance of interest in the Oystercatcher
            if (dogVector[d].getPreyDrive() == true && randomNum < onleashPreyDriveInterest) {

                if (oystercatcherVector[b].getChickNum() > 0) { // If Oystercatcher has chicks, then dog will hunt the chick
                    huntChick(dogVector, d, oystercatcherVector, b);
                } else { // If the oystercatcher has no chick, dog will hunt the adult
                    huntAdult(dogVector, d, oystercatcherVector, b);
                }
            // If the on-leash dog has low prey drive (preydrive = false) and they take chance of interest in the Oystercatcher
            } else if (dogVector[d].getPreyDrive() == false && randomNum < onleashLowPreyDriveInterest){

                if (oystercatcherVector[b].getChickNum() > 0) { // If oystercatcher has chicks, then dog will hunt a chick
                    huntChick(dogVector, d, oystercatcherVector, b);
                } else { // If the oystercatcher has no chicks, then dog will hunt the adult
                    huntAdult(dogVector, d, oystercatcherVector, b);
                }
            }
         // Checks if dog is unleashed and if the oystercatcher is located within the off-leash radius
        } else if (dogVector[d].getLeashed() == false && c <= offleashRad) {

            // If off-leash dog has high prey drive and they take chance of interest in the Oystercatcher
            if (dogVector[d].getPreyDrive() == true && randomNum < offleashPreyDriveInterest) {

                if (oystercatcherVector[b].getChickNum() > 0) { // If oystercatcher has chicks, then dog will hunt a chick
                    huntChick(dogVector, d, oystercatcherVector, b);
                } else { // If the oystercatcher has no chick, then dog will hunt the adult
                    huntAdult(dogVector, d, oystercatcherVector, b);
                }
            // If the off-leash dog has low prey drive (preydrive = false) and they take chance of interest in the Oystercatcher
            } else if (dogVector[d].getPreyDrive() == false && randomNum < offleashLowPreyDriveInterest){

                if (oystercatcherVector[b].getChickNum() > 0) { // If oystercatcher has chicks, dog will hunt a chick
                    huntChick(dogVector, d, oystercatcherVector, b);
                } else { // If the oystercatcher has no chicks, then dog will hunt the adult
                    huntAdult(dogVector, d, oystercatcherVector, b);
                }
            }
        }
    }
}

// Dog spots Oystercatcher nest with chance of taking interest, can lead to eatEgg() or huntAdult()
void Dog::spotNest(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector)
{
    for (unsigned long b = 0; b < oystercatcherVector.size(); b ++) {


        // Rng objects:
        std::random_device rd;
        mt = std::mt19937(rd());
        random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

        float randomNum = random_0_1(mt);


        // Calculating pythagorean distance to between each oystercatcher and each dog, then checking to see if its within the offleash/onleash radii
        float dogPosX = dogVector[d].getDailyX(); // Getting X and Y coords of dog
        float dogPosY = dogVector[d].getDailyY();
        float nestPosX = oystercatcherVector[b].getNestX(); // Getting X and Y coords of Oystercatcher nest
        float nestPosY = oystercatcherVector[b].getNestY();

        float side1 = dogPosX - nestPosX; // Calculating the distance between the X and Y coords of the two individuals
        float side2 = dogPosY - nestPosY; // (same as in spotOystercatcher())

        float c = sqrt(pow(side1, 2) + pow(side2,2)); // Calculating distance with pythagorean theorem



        // Checks if the dog is leashed and if the oystercatcher nest is within the on-leash radius
        if (dogVector[d].getLeashed() == true && c <= onleashRad) {
            // If on-leash dog has a high prey drive, checks if there are eggs in nest and if the dog took the chance of interest in them
            if (dogVector[d].getPreyDrive() == true) {
                // If oystercatcher has eggs and dog is interested, then dog will attempt to eat the eggs
                if (oystercatcherVector[b].getEggNum() > 0 && randomNum < onleashEggInterest) {
                    eatEgg(dogVector, d, oystercatcherVector, b);
                // If the oystercatcher has no eggs, but it is assumed that the adult is sitting in the nest, then dog will hunt the adult
                } else  if (oystercatcherVector[b].getEggNum() == 0 && randomNum < onleashPreyDriveInterest){
                    huntAdult(dogVector, d, oystercatcherVector, b);
                }
            // Checks if the on-leash dog has low prey drive (preydrive = false)
            } else {
                // If oystercatcher has eggs and dog takes chance of interest, then dog will attempt to eat the eggs
                if (oystercatcherVector[b].getEggNum() > 0 && randomNum < onleashEggInterest) {
                        eatEgg(dogVector, d, oystercatcherVector, b);
                // If the oystercatcher has no eggs and dog takes chance of interest, then dog will hunt the adult
                } else if (oystercatcherVector[b].getEggNum() == 0 && randomNum < onleashLowPreyDriveInterest){
                        huntAdult(dogVector, d, oystercatcherVector, b);
                }

            }
        }

        // Checks if dog is unleashed and if the oystercatcher is located within the off-leash radius
        if (dogVector[d].getLeashed() == false && c <= offleashRad) {
            // If off-leash dog has a high prey drive, checks if there are eggs in nest and if the dog took the chance of interest
            if (dogVector[d].getPreyDrive() == true) {
                // If oystercatcher has eggs and dog takes chance of interest, then dog will attempt to eat the eggs
                if (oystercatcherVector[b].getEggNum() > 0 && randomNum < offleashEggInterest) {
                        eatEgg(dogVector, d, oystercatcherVector, b);
                // If the oystercatcher has no eggs and dog takes chance of interest, then the dog will hunt the adult
                } else if (oystercatcherVector[b].getEggNum() == 0 && randomNum < offleashPreyDriveInterest){
                        huntAdult(dogVector, d, oystercatcherVector, b);
                }
            // If the off-leash dog has low prey drive (preydrive = false), checks if there are eggs and if dog took chance of interest
            } else {
                // If Oystercatcher has eggs and dog takes chance of interest, then dog will attempt to eat eggs
                if (oystercatcherVector[b].getEggNum() > 0 && randomNum < offleashEggInterest) {
                        eatEgg(dogVector, d, oystercatcherVector, b);
                // If the oystercatcher has no eggs and dog takes chance of interest, then the dog will hunt the adult
                } else  if (oystercatcherVector[b].getEggNum() == 0 && randomNum < offleashLowPreyDriveInterest){
                        huntAdult(dogVector, d, oystercatcherVector, b);
                }
            }
        }
    }
}


// Dog hunts the adult, where there is a chance that the dog will be successful in hunting
// Factors affecting this:
//      - Prey drive
//      - Leash status
void Dog::huntAdult(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b)
{
    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

    float randomNum = random_0_1(mt);

    // Checks if dog is on-leash, whether they have a high or low prey drive, and if hunting attempt succeeds based on chance params
    if (dogVector[d].getLeashed() == true) {

        if (dogVector[d].getPreyDrive() == true && randomNum < onleashPreyDrivePredation) {
            oystercatcherVector[b].death(oystercatcherVector, b);
        } else if (dogVector[d].getPreyDrive() == false && randomNum < onleashLowPreyDrivePredation) {
            oystercatcherVector[b].death(oystercatcherVector, b);
        }
    // Checks if dog is off-leash, whether they have a high or low prey drive, and if hunting attempt succeeds based on chance params
    } else {

        if (dogVector[d].getPreyDrive() == true && randomNum < offleashPreyDrivePredation) {
            oystercatcherVector[b].death(oystercatcherVector, b);
        } else if (dogVector[d].getPreyDrive() == false && randomNum < offleashLowPreyDrivePredation) {
            oystercatcherVector[b].death(oystercatcherVector, b);
        }
    }
}



// Dog attempts to eat eggs, where there is a chance that the dog will be successful and eat 1 to all the eggs,
// Factors affecting this:
//      - Parental defence
//      - Leash-status
// Note: prey drive doesn't affect this because dogs are dogs and will just eat things off the ground no matter what
void Dog::eatEgg(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b)
{

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

    float randomNum = random_0_1(mt);

    // Rng for the number of eggs inidividual Oystercatcher has (0 to all eggs)
    std::uniform_int_distribution<int> eggAmount(0, oystercatcherVector[b].getEggNum());
    int eggsEaten = eggAmount(mt);

    // If dog is on-leash, predation success is taken and adjusted from provided parameter(onleashEggEating) based on parental
    // defence. If dog manages to predate, then random number of eggs are drawn from rng and subtracted from the Oystercatcher and their mates egg
    // args
    if (dogVector[d].getLeashed() == true) {
        // Calculating predationSuccess after parental defence
        float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, onleashEggEating);
        if (randomNum < predationSuccess) {
            oystercatcherVector[oystercatcherVector[b].getMateIndex()].setEggNum(oystercatcherVector[b].getEggNum() - eggsEaten); // Changing eggNum for mate
            oystercatcherVector[b].setEggNum(oystercatcherVector[b].getEggNum() - eggsEaten); // Changing eggNum for target oystercatcher
        }
    // If dog is off-leash, predation success is taken and adjusted from provided parameter(offleashEggEating) based on parental defence.
    // If dog manages to predate, then random number of eggs are drawn from rng and subtracted from the Oystercatcher and their mates egg
    // args
    } else {
        // Calculating predationSuccess after parental defence
        float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, offleashEggEating);
        if (randomNum < predationSuccess) {
            oystercatcherVector[oystercatcherVector[b].getMateIndex()].setEggNum(oystercatcherVector[b].getEggNum() - eggsEaten); // Changing eggNum for mate
            oystercatcherVector[b].setEggNum(oystercatcherVector[b].getEggNum() - eggsEaten); // Changing eggNum for target oystercatcher
        }
    }
}


// Dog attempts to hunt a chick. Parent defence will give the dog a lower chance of success, and only 1 chick is assumed to be eaten per occurrence
// of successful hunting
// Factors affecting this:
//      - Prey drive
//      - Parental defence
//      - Leash status
void Dog::huntChick(std::vector<Dog> dogVector, int d, std::vector<Oystercatcher> &oystercatcherVector, int b)
{

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

    float randomNum = random_0_1(mt);

    // Checks if dog has high prey drive, and whether it is on- or off-leash. Predation success is then taken and adjusted from provided parameter
    // (onleashPreyDrivePredation and offleashPreyDrivePredation) based on parental defence. If dog is successful, then 1 chick is subtracted from
    // target Oystercatcher and their mate's args
    if (dogVector[d].getPreyDrive() == true) {
        if (dogVector[d].getLeashed() == true) {

            float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, onleashPreyDrivePredation);
            if (randomNum < predationSuccess) {
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for mate
                oystercatcherVector[b].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for target oystercatcher
            }
        } else { // dog off leash

            float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, offleashPreyDrivePredation);
            if (randomNum < predationSuccess) {
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chicNum for mate
                oystercatcherVector[b].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for target oystercatcher
            }
        }
    // Checks if dog has low prey drive, and whether it is on- or off-leash. Predation success is then taken and adjusted from provided parameter
    // (onleashLowPreyDrivePredation and offleashLowPreyDrivePredation) based on parental defence. If dog is successful, then 1 chick is subtracted
    // from target Oystercatcher and their mate's args
    } else {

        if (dogVector[d].getLeashed() == true) { // if dog is on leash

            float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, onleashLowPreyDrivePredation);
            if (randomNum < predationSuccess) {
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for mate
                oystercatcherVector[b].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for target oystercatcher
            }
        } else { // if dog is off leash

            float predationSuccess = oystercatcherVector[b].parentDefence(oystercatcherVector, b, offleashLowPreyDrivePredation);
            if (randomNum < predationSuccess) {
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chicNum for mate
                oystercatcherVector[b].setChickNum(oystercatcherVector[b].getChickNum() - 1); // changing chickNum for target oystercatcher
            }
        }
    }
}


