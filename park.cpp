#include "park.h"



Park::Park() {

    // Loading in precreated pixelated image of the park map into the QGraphicsView
    image.load("pixelated_map.png");
    image.convertTo(QImage::Format_ARGB32);

    // Creating all pixel vectors before Oystercatcher or dog vector creation
    createPixelVectors();

}


// Creates a 2d vector of all of the dark green pixels showing vegetation within the park map
// Creates a 2d vector of all the beige pixels resembling paths in the map (same structure as greenPixelVector)
// For the first index, [0] represents the x coordinates and [1] represents the y coordinates
void Park::createPixelVectors()
{
    // Clearing vectors and resizing them to 2 (x and y vectors)
    greenPixelVector.clear();
    greenPixelVector.resize(2);

    pathPixelVector.clear();
    pathPixelVector.resize(2);

    // For each pixel in the image, check if their RGB values match that of the green vegetation or the path RGB values, and add the coordinate
    // pair to the respective vector.
    for (int y = 0; y < image.height(); y++) {

        for (int x = 0; x < image.width(); x++) {

            QColor pixelRGB = image.pixelColor(x, y); // attaining RGB characteristics of pixel

            // Assignng green pixels into greenPixelVector
            if (pixelRGB.red() == 20 &&
                pixelRGB.green() == 106 &&
                pixelRGB.blue() == 87) {

                greenPixelVector[0].push_back(x); // add x coordinate ([0] contains the x coords)
                greenPixelVector[1].push_back(y); // add y coordinate ([1] contains the y coords)
            }

            // Assigning path pixels into the pathPixelVector
            if (pixelRGB.red() == 213 &&
                pixelRGB.green() == 206 &&
                pixelRGB.blue() == 123) {

                pathPixelVector[0].push_back(x); // add x coordinate ([0] contains the x coords)
                pathPixelVector[1].push_back(y); // add y coordinate ([1] contains the y coords)
            }
        }
    }
}

// Creates the dog Vector with a certain amount of inital dogs based on a selected scenario
void Park::createDogs(int scenarioNumber, int initialDogs)
{
    // Clearing dogVector and making space for initial amount of dogs
    dogVector.clear();
    dogVector.reserve(initialDogs);

    // Creating temporary dog object to fill vector with in all vector spaces
    Dog tempDog(false, false, 0, 0);
    dogVector.assign(initialDogs, tempDog);

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

    // If the scenario is 1 (both on- and off-leash dogs), then dog has 50% chance of being off-leash
    if (scenarioNumber == 1) {
        // Randomizing the characteristics of each dog- boolean values have 50% chance of being true or false
        for (int d = 0; d < initialDogs; d++) {
            float randomNum1 = random_0_1(mt); // Random number for leashed characteristic chance
            float randomNum2 = random_0_1(mt); // Random number for prey drive characteristic chance
            // Assigning leash status arg based on random chance
            if (randomNum1 < 0.5) {
                dogVector[d].setLeashed(true);
            } else {
                dogVector[d].setLeashed(false);
            }
            //Assigning prey drive arg based on random chance
            if (randomNum2 < 0.5) {
                dogVector[d].setPreyDrive(true);
            } else {
                dogVector[d].setPreyDrive(false);
            }

            updateDogPosition(d); // Assigns a random position on a path in the map
        }
    }

    // If the scenario is 2 (on-leash dogs only), then all dogs are on-leash
    if (scenarioNumber == 2) {
        // randomizing the characteristics of prey drive (50% chance of true or false)
        for (int d = 0; d < initialDogs; d++) {
            float randomNum2 = random_0_1(mt);// Random number for prey drive characteristic chance

            dogVector[d].setLeashed(true);

            //Assigning prey drive arg based on random chance
            if (randomNum2 < 0.5) {
                dogVector[d].setPreyDrive(true);
            } else {
                dogVector[d].setPreyDrive(false);
            }


            updateDogPosition(d); // Assigns a random position on a path in the map
        }
    }
}

// Generates coordinates for nests for mated pairs of Oystercatchers
// i is the index for a given Oysteratcher within the oystercatcherVector
void Park::generateNestCoords(int i)
{
    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    // Rng for picking a random coordinate pair within the greenPixelVector
    std::uniform_int_distribution<int> Randomizer(0, greenPixelVector[0].size() - 1);

    int randomNum = Randomizer(mt); // Random number for nest pixel index

    // If Oystercatcher is mated, then nest coords are randomly picked and set in the args for the Oystercatcher and its mate
    if (oystercatcherVector[i].getMateStatus() == true) {
        // Initially, Oystercatchers are assigned (0,0) as their nest, so if they have had their nest site truly assigned already,
        // it won't be (0,0), this prevents repeats in the for-loop for each mated pair
        if (oystercatcherVector[i].getNestX() == 0 &&
            oystercatcherVector[i].getNestY() == 0) {

            // Sets ordered pair as nest coord for target oystercatcher
            oystercatcherVector[i].setNestCoordX(greenPixelVector[0][randomNum]);
            oystercatcherVector[i].setNestCoordY(greenPixelVector[1][randomNum]);

            // Sets same ordered pair as nest coords for target oystercatcher's mate
            oystercatcherVector[oystercatcherVector[i].getMateIndex()].setNestCoordX(greenPixelVector[0][randomNum]);
            oystercatcherVector[oystercatcherVector[i].getMateIndex()].setNestCoordY(greenPixelVector[1][randomNum]);
        }
    }
}


// Updates the individual coordinates for each oystercatcher (changes each day):
// b is the index of the oystercatcher it pertains to (this method should only be run within an oystercatcherVector for-loop)
void Park::updateIndivPosition(int b)
{

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    // Rng for picking a random coordinate pair within the greenPixelVector
    std::uniform_int_distribution<int> Randomizer(0, greenPixelVector[0].size() - 1);


    int randomNum = Randomizer(mt); // For indiv pixel index


    if (oystercatcherVector[b].getIsDead() == false) { // Any updating only happens when oystercatchers are living

        // Updating map and erasing old magenta pixel
        int oldIndivX = oystercatcherVector[b].getIndivX();
        int oldIndivY = oystercatcherVector[b].getIndivY();
        image.setPixelColor(oldIndivX, oldIndivY, QColor(20, 106, 87));


        // Reassigning new individual coordinates - random ordered pairs that are green pixels from the green pixel vector (same index
        // for x and y vectors within 2d vector)
        oystercatcherVector[b].setIndivX(greenPixelVector[0][randomNum]);
        oystercatcherVector[b].setIndivY((greenPixelVector[1][randomNum]));
    }
}

// Updates dog coordinations (changes each day) - this does not show up on the map
// d is the index of the dog is pertains to (this method chould only be run within a dogVector for-loop)
void Park::updateDogPosition(int d)
{
    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    // Rng for picking a random coordinate pair within the greenPixelVector
    std::uniform_int_distribution<int> Randomizer(0, pathPixelVector[0].size() - 1);

    int randomNum = Randomizer(mt);

    // Assigning new coords to dogs position (invisible on map)
    dogVector[d].setDailyX(pathPixelVector[0][randomNum]);
    dogVector[d].setDailyY(pathPixelVector[1][randomNum]);

}


// Method for creating initial batch of Oytercatchers based on the specified initial number of Oystercatchers
void Park::createOystercatchers(int initialOystercatchers)
{
    // Clearing and reserving proper space for amount of initial oystercatchers
    oystercatcherVector.clear();
    oystercatcherVector.reserve(initialOystercatchers);

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float> (0.0, 1.0);
    // Rng for initial ages (random assignment)
    std::uniform_int_distribution<int> ageRandomizer(0, 13);

    // For each Oystercatcher, temporary Oystercatcher is first assigned to vector, then args are updated to proper values
    for (int b = 0; b < initialOystercatchers; b++) {  

        float randomAge = ageRandomizer(mt); // For random age assignment

        oystercatcherVector.emplace_back(b + 1, // Method attained from AI (Qwen Instruct) to fix a vector initialization bug
                                         true,
                                         0,
                                         0,
                                         randomAge,
                                         0,
                                         0,
                                         0,
                                         0,
                                         0,
                                         false);

        // Setting IDs for each Oystercatcher (Lowest ID = 1, not 0)
        oystercatcherVector[b].setID(b + 1);
        oystercatcherVector[b].setMateStatus(true);

        // Setting temporary initial individual coords so that updateIndivPosition() can correctly function
        oystercatcherVector[b].setIndivX(greenPixelVector[0][0]);
        oystercatcherVector[b].setIndivY(greenPixelVector[1][0]);

        updateIndivPosition(b);

        // Setting mate for target Oystercatcher (Method: folding the vector in half and matching IDs ->  ID 1 with ID 20, ID 2 with ID 19, etc.)
        // If mateID (standard initial value) is 0, then update it and update the mateID arg for the mate too.
        // If-condition prevents already-mated oystercatchers from being repeated (If Oystercatcher already has mate assigned, then they get skipped)
        if (oystercatcherVector[b].getMateID() == 0) {
            oystercatcherVector[b].setMateID(initialOystercatchers - b);
            oystercatcherVector[oystercatcherVector[b].getMateIndex()].setMateID(b + 1); // getting the mated oystercatchers index and setting its mate to the current target oystercatcher's ID. THis only works because the ID initially matches the vector index + 1
        }

        // Assigning random nest coords for each mated pair
        generateNestCoords(b);

    }


}


// After avg of 4 months after hatching (~120 days, so 125 + 120 = 245), chicks go off on their own, so they become adults and get added to
// the oystercatcherVector
// time is the timestep (aka days in MainWindow), and the oystercatcherVector is referenced as an input
void Park::chickToAdult(int time, std::vector<Oystercatcher> &oystercatcherVector)
{
    if (time % 365 == 245) {
        int totalChicks = 0; // counting object

        // Getting total number of chicks to add to oysercatcherVector
        for (unsigned long b = 0; b < oystercatcherVector.size(); b++) {
            totalChicks += oystercatcherVector[b].getChickNum();
        }

        totalChicks = totalChicks/2; // Divide by 2 to correct double counting chicks, since each parent gets counted in for-loop

        int prevVectorSize = oystercatcherVector.size(); // Value needed for proper indexing and for-loop

        // Adds in the new temporary adults into the oystercatcherVector, and reassigns their values properly
        for (int i = 0; i < totalChicks; i++) {
            // Adding in the temporary Oystercatchers
            Oystercatcher tempBird(0, false, 0, 0, 0, 0, 0, 0, 0, 0, false);
            oystercatcherVector.push_back(tempBird);
        }

        // Setting the other oystercatcher chick numbers back to 0
        for (int b = 0; b < prevVectorSize; b ++) {
            oystercatcherVector[b].setChickNum(0);
        }


        // Mating mechanics: Oystercatcher X mates with Oystercatcher X + 1. If there is an  od number of new Oystercatchers, then the last one
        // doesn't mate (assumed occurrence in nature as well)
        for (unsigned long b = prevVectorSize; b < oystercatcherVector.size(); b += 2) {
            if (b + 1 < oystercatcherVector.size()) { //Making sure its not the last Oystercatcher in the vector, then mating b with b + 1
                oystercatcherVector[b].setMateStatus(true); // Setting target Oystercatcher mating status as true
                oystercatcherVector[b].setMateID(b + 2); // Mating with index of b + 1, but the ID is index + 1, so b + 2

                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setMateStatus(true); // Setting mate's mate status as true
                oystercatcherVector[oystercatcherVector[b].getMateIndex()].setMateID(b + 1); // because ID is index + 1 so b + 1
            } else { // Last Oystercatcher doesn't get to mate
                oystercatcherVector[b].setMateStatus(false);
                oystercatcherVector[b].setMateID(0);
            }
        }


        // Assigning standard values to all new Oystercatchers in the vector from the point of new additions until the end of the vector
        for (unsigned long b = prevVectorSize; b < oystercatcherVector.size(); b++) {
            oystercatcherVector[b].setID(b + 1);
            oystercatcherVector[b].setEggNum(0);
            oystercatcherVector[b].setChickNum(0);
            oystercatcherVector[b].setAge(0);

            // Creating nest coordinates per mated pair (default to (0,0) to work with generateNestCoords() function)
            oystercatcherVector[b].setNestCoordX(0);
            oystercatcherVector[b].setNestCoordY(0);

            // Setting initial individual coords so that updateIndivPosition can correctly function
            oystercatcherVector[b].setIndivX(greenPixelVector[0][0]);
            oystercatcherVector[b].setIndivY(greenPixelVector[1][0]);

            updateIndivPosition(b);
            generateNestCoords(b);
        }
    }
}


// Taking the oystercatcher vector indivX and indivY values and assigning those pixels magenta in the map
// Taking the oystercatcher nest coords and assigning those pixels yellow in the map
void Park::updateOystercatcherMap()
{

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);




    for (unsigned long b = 0; b < oystercatcherVector.size(); b++) {
        // All Oystercatchers must be living to be displayed on the map
        if (oystercatcherVector[b].getIsDead() == false) {
            // Oystercatcher is mated, set the nest pixels in the map as yellow
            if (oystercatcherVector[b].getMateStatus() == true){
                int xNest = oystercatcherVector[b].getNestX();
                int yNest = oystercatcherVector[b].getNestY();
                image.setPixelColor(xNest, yNest, Qt::yellow);
            }

            // Getting inividual coordinates for each Oystercatcher
            int xCoord = oystercatcherVector[b].getIndivX();
            int yCoord = oystercatcherVector[b].getIndivY();

            // Preventing nest pixels from being overpainted (assumed that even if individuals are on a nest coord at a point in time,
            // that it just won't show on the map as the nest coord location is more important)
            if (image.pixelColor(xCoord, yCoord) != Qt::yellow) {
                image.setPixelColor(xCoord, yCoord, Qt::magenta); // assigning Oystercatcher individual coords on the map in magenta
            }
        // If the oystercatcher AND its mate are dead, then set the nest pixel back to green
        } else if ( oystercatcherVector[b].getIsDead() == true &&
                   oystercatcherVector[oystercatcherVector[b].getMateIndex()].getIsDead() == true) {
            int xNest = oystercatcherVector[b].getNestX();
            int yNest = oystercatcherVector[b].getNestY();
            image.setPixelColor(xNest, yNest, QColor(20, 106, 87)); // Setting nest back to green
        // If Oystercatcher is dead (but not the mate), set the indiv pixel back to green.
        } else {
            int xIndiv = oystercatcherVector[b].getIndivX();
            int yIndiv = oystercatcherVector[b].getIndivY();
            image.setPixelColor(xIndiv, yIndiv, QColor(20, 106, 87));
        }
    }
}


// Resetting the model by resetting the vectors and image
void Park::resetModel()
{
    // Clearing the dog and Oystercatcher vectors
    oystercatcherVector.clear();
    dogVector.clear();

    // Reloading in the blank map
    image.load("pixelated_map.png");
    image.convertTo(QImage::Format_ARGB32);

    // Recreating the vectors
    createOystercatchers(initialOystercatchers);
    createDogs(scenarioNumber, numDogs);
}




// ** GETTER AND SETTER METHODS:

// Fetches the park image
QImage Park::getImage()
{
    return image;
}

// Fetches and references the dog Vector
std::vector<Dog> &Park::getDogVector()
{
    return dogVector;
}

// Fetches and references the Oystercatcher vector
std::vector<Oystercatcher> &Park::getOystercatcherVector()
{
    return oystercatcherVector;
}

// Fetches the initial number of dogs
int Park::getInitDogs()
{
    return initDogs;
}

// Sets the initial number of dogs a new number, specified from the spinbox in the GUI
void Park::setInitDogs(int number)
{
    initDogs = number;
}

// Fetches the initial Oystercatcher number
int Park::getInitOystercatchers()
{
    return initBirds;
}

// Sets the initial number of Oystercatchers, specified from the spinbox in the GUI
void Park::setInitOystercatchers(int number)
{
    initBirds = number;
}

// Fetches the scenario number
int Park::getScenarioNumber()
{
    return scenarioNumber;
}

// Sets teh scenario number value, selected in the GUI
void Park::setScenarioNumber(int number)
{
    dogScenario = number;
}


