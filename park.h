#ifndef PARK_H
#define PARK_H

#include <QtCharts>
#include <dog.h>
#include <oystercatcher.h>

class Park
{
public:

    // Park object for MainWindow
    Park();


    // creating initial vector of dogs and their characteristics
    void createDogs(int scenarioNumber, int initialDogs);

    //creating Oystercatcher vector
    void createOystercatchers(int initialOystercatchers);

    // Simulates daily movement of oystercatchers - reassigns their individual coords in their args
    void updateIndivPosition(int b);

    // Updates average daily movement of dogs (however this is not seen on the map as it is too messy and redundant) - reassigns their arg coords
    void updateDogPosition(int d);

    // Sets up the Oystercatcher nests and also individual Oystercatchers that move location each day
    void updateOystercatcherMap();

    // All chicks grow up, assign adult Oystercatcher args and adds them to the Oystercatcher vector
    void chickToAdult(int time, std::vector<Oystercatcher> &oystercatcherVector);

    // Resets the model
     void resetModel();


    // *** GETTER  AND SETTER FUNCTIONS FOR PARK OBJECTS

    // Gets the park image
    QImage getImage();

    // Gets and references the dog vector
    std::vector<Dog> &getDogVector();

    // Gets and references the Oystercatcher vector
    std::vector<Oystercatcher> &getOystercatcherVector();

    // Gets the initial number of dogs, used in createDogs()
    int getInitDogs();
    // Sets the initial number of dogs from the spinbox in the UI
    void setInitDogs(int number);

    // Gets the initial number of Oystercatchers, used in createOystercatchers()
    int getInitOystercatchers();
    // Sets the initial number of Oystercatchers from the spinbox in the UI
    void setInitOystercatchers(int number);

    // Gets the scenario number from the selection in the UI
    int getScenarioNumber();
    // Gets the scenario number, used in createDogs()
    void setScenarioNumber(int number);


    // *** REFERENCE OBJECTS:

    // Reference for the initial number of Oystercatchers, so spinbox actually updates the object
    int &initBirds = initialOystercatchers;

    // Reference for the initial number of dogs, so spinbox actually updates the object
    int &initDogs = numDogs;

    // Reference for the scenario, so UI selection actually updates the object
    int &dogScenario = scenarioNumber;


private:


    // *** METHODS:

    // Creates a 2d vector of all of the dark green pixels showing vegetation within the park map
    // Creates a 2d vector of all the beige pixels resembling paths in the map (same structure as greenPixelVector)
    // For the first index, [0] represents the x coordinates and [1] represents the y coordinates
    void createPixelVectors();

    // Picks random vegetation coordinate pair from the green pixel vector and assigns that as the nest location for each mated pair
    // i is the index of the OystercatcherVector
    void generateNestCoords(int i);


    // *** VARIABLES AND PARAMS:

    // image of the park/urban green areas
    QImage image;

    // Random number generator objects
    std::mt19937 mt;
    std::uniform_real_distribution<float> random_0_1;

    //Number of dogs total that go though the park everyday (also the initial number of dogs for model)
    int numDogs = 30;

    // Number of initial Oystercatchers in the model
    int initialOystercatchers = 20;

    // Scenario number for createDogs(). 1 = on- and off-leash dogs, 2 = on-leash dogs only. (Standard is 1 for the model)
    // Note: The policy scenario uses Scenario 1 and updates the args on certain days for enforce the policy
    int scenarioNumber = 1;


    // *** VECTORS:

    //dog vector containing dog IDs and characteristics
    std::vector<Dog> dogVector;

    //oystercatcher vector to keep track of all the oystercatchers
    std::vector<Oystercatcher> oystercatcherVector;

    // Vector containing all coordinate pairs of green pixels within the park map
    std::vector<std::vector<int>> greenPixelVector;

    // Vector containing all coordinate pairs of path pixels within the park map
    std::vector<std::vector<int>> pathPixelVector;



};

#endif // PARK_H
