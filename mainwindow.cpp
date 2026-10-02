#include "mainwindow.h"
#include "ui_mainwindow.h"



/*
 *
 * ****************************
 * About this simulation model
 * ****************************
 *
 * Author: Alyssa Weber
 * Matrikelnummer: 13751510
 *
 *
 * *** RESEARCH QUESTION:
 *
 * How does predation from dogs affect Eurasian Oystercatcher populations within an urban green area, and how does it differ
 * when dogs are on- or off-leash all or some of the time?
 *
 *
 * *** BACKGROUND INFORMATION:
 *
 * Eurasian Oystercatchers are ground-nesting birds that have appeared in the urban landscape since their adaptation to inland breeding.
 * Their populations have been estimated to have declined about 40% over the past three generations (van de Pol et al., 2014).
 * Such decline of ground-nesting birds is likely in part due to humans and human-contributed disturbances from urban predators such as
 * corvids, cats, and dogs (Alba et al., 2025). This model focuses on the predator-prey relationship of dogs and Eurasian Oystercatchers in a
 * managed urban green area to examine how dog-driven predation affects Oystercatchers over the course of multiple breeding seasons. The effect of
 * on-leash and off-leash dogs are specifically examined as well as the impact of policy, which limits the days off-leash dogs are allowed in
 * the area.
 *
 *
 * *** ABOUT THIS PROGRAM:
 *
 * This program simulates a specified number of Eurasian Oystercatchers living within an urban green space, based off of Eilenriede Wald in Hannover,
 * along with a specified number of dogs that visit the park each day. Oystercatchers are only allowed to be present on vegetation pixels, while dogs
 * are only allowed to be present on path pixels (however dogs are implied to stray from the path when hunting in the model). Each day, individual
 * oystercatchers move around, and there is a chance that on-leash or off-leash dogs will spot, hunt, and predate Oystercatcher adults, chicks, or
 * eggs, if a nest is discovered. Dogs are varied in their prey-drive level (high or low), as well as their leash status (on-leash or off-leash),
 * which is also decided based on the selected model scenario.
 *
 * Dogs with a high prey drive have a higher chance of spotting and hunting Oystercatchers, while dogs with a low prey drive have much lower chances
 * to do so. All dogs, regardless of prey drive, have a certain chance of spotting and eating eggs, as dogs tend to attempt to eat any food object
 * they find. Regarding predation, a dog must detect an Oystercatcher or a nest within their spotting radius first. They must then fulfill the chance
 * of being interested enough to pursue the hunt. Once these conditions are met and the dog hunts the Oystercatcher, there is only a certain chance
 * that the dog will be successful in the Oystercatcher predation. The radius in which a dog may spot an Oystercatcher individual or nest is
 * adjusted based on the dog's leash status, where off-leash dogs have a much larger radius and on-leash dogs have a much smaller radius. The chance
 * of a dog taking an interest in or hunting an Oystercatcher also depends on the leash status of the dog, as owners are assumed to have more control
 * over their dog while they are on the leash. Dogs do not age in this model, as the model assumes that a certain number of dogs enters the park on
 * a daily basis, without specificity of the individual dogs.
 *
 * Oystercatchers often have lifelong mates and tend to return to the same place to breed each year, where both parents contribute to nest and
 * chick care (van de Pol et al., 2014). This is implemented in the model by immediately assigning a mate to each Oystercatcher upon their initial
 * creation or their transition from chick to adult. Each Oystercatcher pair has one nest site, which stays consistent throughout the whole
 * simulation until both parents die. Both parents are assumed to care for the eggs and chicks, which is demonstrated through parental defence
 * in the model. Since Oystercatchers also reach sexual maturity at about 3 years and have an average lifespan of 13.7 years in the wild
 * (iucnredlist.org, 2019), Oystercatchers may only mate and reproduce if they are within this age range in the model.
 *
 * The parameters that are intended to be changed within the model are the model scenarios, the initial number of dogs, and the initial number of
 * Eurasian Oystercatchers. Additional parameters, such as the chance of a dog spotting and taking an interest in an Oystercatcher and the chance
 * of the dog pursuing it in a hunt may also be adjusted within the code, although they are not available to be adjusted within the model UI. Odd
 * numbers of initial Oystercatchers are not recommended to be used in the model, as the Oystercatcher mating mechanics may not function as intended.
 *
 * The temporal extent of the model is 7 years, and the temporal grain of the model is 1 day. The spatial extent of the model is the outline of the
 * urban green area, and the estimated spatial grain is about 2 meters.
 *
 * The output of this model consists of a map of the park filled with pixel locations of nests and individuals, a graph of the number of living
 * Oystercatchers over time (in days), and the status of every Oystercatcher (alive or predated). The main analytical output, the graph, can be
 * interpreted by analysing the longterm trends of Oystercatcher population numbers within the park, resulting carrying capacities, as well as the
 * patterns in population fluctuation based on reproduction and predation.
 *
 * This simulation model could be used in a study to understand the threat of domestic dogs to Oystercatchers within an urban area, and how methods
 * of dog walking (on- or off-leash), as well as policymaking can impact the survivability and success of Eurasian Oystercatchers in an urban area.
 * Model parameters could also be adjusted and validated according to field studies of Oystercatcher predation in urban areas to better fit their
 * current survival trends. To fully understand the dynamics of urban predation of Oystercatchers, adding in dynamics of cats and corvids could also
 * improve the model to better answer the research question at hand, in terms of how much do dogs affect Oystercatcher survivability compared to
 * other urban predators. Adding migration dynamics to the model would also simulate the annual activities of Oystercatchers more realistically.
 * In addition to this, including a refuge area scenario for the Oystercatchers in the model would be beneficial to investigate how refuges
 * contribute to their survival success. Finally, adding in intraspecies competition of resources would help provide a more realistic spread and
 * number of Oystercatchers in the park over time.
 *
 * Running a simulation experiment with an enhanced version of this model would entail first parameterizing and validating the model against
 * empirical data from literature or self-attainment. With the correct parameterization, the simulation would be run multiple times for each
 * scenario. The averaged outputs and trends of each scenario would be analyzed to then draw a conclusion about the effects
 * of dogs and other urban predators on Oystercatchers, as well as potentially help shape new future policies and Oystercatcher conservation.
 *
 *
 * *** SOURCES:
 *
 * The code is structured and organized into 4 main classes: MainWindow, Dog, Oystercatcher, and Park.
 *
 * The MainWindow class handles all of the UI components, including buttons, checkboxes, the zoom slider, the Oystercatcher status reporter, the
 * QChart (graph), as well as the reporters for the time and number of current live eggs and chicks at any given time in the model. The timesteps
 * are handled in MainWindow under the start button method as well as all of the model processes being called at the appropriate time and place each
 * timestep. Many processes within the start button method are fetched from the other classes. The unit test is also contained and run within
 * MainWindow.
 *
 * The Dog class contains all arguments, parameters, and processes that dogs perform throughout the simulation. This includes spotting Oystercatchers,
 * spotting Oystercatcher nests, hunting Oystercatchers or their chicks, and eating Oystercatcher eggs. All setter and getter functions for each
 * Dog argument can be found in its respective header file.
 *
 * The Oystercatcher class contains all arguments, parameters, and processes that concern Oystercatchers within the simulation. This includes
 * reproduction, egg and chick care, parental defence, aging from year to year, hatching, and death. All setter and getter functions for each
 * Oystercatcher argument can be found in its respective header file.
 *
 * The Park class contains the image of the urban green area park, all methods that update the locations of Oystercatchers and dogs within the park
 * (although dog locations are not visually displayed), and all methods that entail the creation of the vector of Oystercatchers and the vector of
 * dogs for tracking purposes throughout the simulation. A method to add newly grown chicks into the Oystercatcher vector can be found here as well
 * as a method to reset the model, which is utilized by the reset button in the MainWindow.cpp file. There are also various functions here that
 * serve as getter functions to be utilized in MainWindow.cpp. This class utilizes pointers and references often for the purpose of updating the
 * scene for be properly displayed in the UI, as well as for the purpose of editing the Oystercatcher and Dog vectors as the simulation runs. Methods
 * from the Oystercatcher and Dog classes are also fetched to properly integrate into their respective vectors.
 *
 * The image used as the park map in this model was captured via OpenStreetMap and was hand drawn and pixelified using a python script. The entire
 * script was written with assistance from AI (ChatGPT OSS 120B), after being unable to personally achieve the desired pixelation from the image.
 * The park image is not an exact and accurate depiction of Eilenriede Wald, as only some main pathways were kept to allow pixels to exist that were
 * out of range of on-leash dogs. The script for this as well as the hand-drawn image are included within the zip file containing this project.
 *
 *
 * *** REFERENCES:
 *
 * Alba, R., Marcolin, F., Assandri, G., Ilahiane, L., Cochis, F., Brambilla, M., Rubolini, D., & Chamberlain, D. (2025).
 *  Different traits shape winners and losers in urban bird assemblages across seasons. Scientific Reports, 15(1), 16181.
 *  https://doi.org/10.1038/s41598-025-00350-6
 *
 * Eurasian Oystercatcher Haematopus Ostralegus Species Factsheet. (n.d.). BirdLife DataZone. Retrieved March 15, 2026,
 *  from https://datazone.birdlife.org/species/factsheet/eurasian-oystercatcher-haematopus-ostralegus
 *
 * van de Pol, M., Atkinson, P., Blew, J., Crowe, O., Delany, S., Duriez, O., Ens, B. J., Hälterlein, B., Hötker, H., Laursen, K.,
 *  Oosterbeek, K., Petersen, A., Thorup, O., Tjørve, K., Triplet, P., & Yésou, P. (2014). A global assessment of the conservation
 *  status of the nominate subspecies of Eurasian Oystercatcher Haematopus ostralegus ostralegus.
 *
 *
 *
 *
 *
 *
*/


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting up the scene
    scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(image));
    scene->setSceneRect(image.rect());

    // Getting initial number of Oystercatchers and setting up the oystercatcherVector
    int initialOystercatchers = park.getInitOystercatchers();
    park.createOystercatchers(initialOystercatchers);

    // Setting reference to update the scene without having to recreate a new scene each time its updated
    // (no data storage issues or needing to clear the scene before re-setting it)
    pixmap = scene->addPixmap(QPixmap::fromImage(image));

    // Setting up the pixels for the Oystercatcher locations, attaining updated image for it, then adding it to scene
    park.updateOystercatcherMap();
    QImage OystercatcherMapImage = park.getImage();
    pixmap->setPixmap(QPixmap::fromImage(OystercatcherMapImage));

    // Setting the scene into the QGraphicsView "spatialView"
    ui->spatialView->setScene(scene);

    // Standard scaling the image to the QGraphicsView window, can adjust if computer has different scaling settings
    ui->spatialView->scale(2, 2);


    // Setting up the dog vector:
    // Getting initial dogs, setting + getting the scenario number (Standard scenario = 1 when model constructs for first time), and creating vector.
    ui->onLeash_OffLeash_Scenario->setChecked(true);
    int initialDogs = park.getInitDogs();
    int scenarioNumber = park.getScenarioNumber();
    park.createDogs(scenarioNumber, initialDogs);


    // Getting the created dog and Oystercatcher vectors
    dogVector = park.getDogVector();
    oystercatcherVector = park.getOystercatcherVector();


    // Setting the standard initial dogs and Oystercatcher amounts in their respective spinboxes
    int oystercatcherNum = park.getInitOystercatchers();
    ui->numInitialDogs->setValue(initialDogs);
    ui->numInitialOystercatchers->setValue(oystercatcherNum);



    // Making new chart and series objects
    chart = new QChart();
    series = new QLineSeries();

    // Configuring the series
    series->setColor(Qt::darkGreen);
    series->setName("Oystercatcher Adult Population");

    // Configuring the chart
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setTitleText("Time (days)");
    chart->axisY()->setTitleText("# of Individuals");
    chart->setTitle("Oystercatcher population throughout time.");
    ui->graphView->setChart(chart);

}


MainWindow::~MainWindow()
{
    delete ui;
}


// Zooms in/out of the image for convenience on different systems + increased ease of viewing map
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    switch (position) {
    case -3:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(0.5, 0.5);
        break;
    case -2:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(1, 1);
        break;
    case -1:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(1.5, 1.5);
        break;
    case 0:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(2, 2);
        break;
    case 1:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(2.5, 2.5);
        break;
    case 2:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(3, 3);
        break;
    case 3:
        ui->spatialView->resetTransform();
        ui->spatialView->scale(3.5, 3.5);
        break;
    }
}

// Unit test to make sure Oystercatchers are being put on green pixels only
void MainWindow::on_unitTestButton_clicked()
{

    int counter = 0; // Counter object

    // Checks to see if the RGB values of the coordinates that the Oystercatchers are on match that of the vegetation RGB values from the blank image.
    for ( unsigned long i = 0; i < oystercatcherVector.size(); i++ ) {
        QColor pixelRGB = image.pixelColor(oystercatcherVector[i].getIndivX(), oystercatcherVector[i].getIndivY());

        // Lists the RGB values for each Oystercatcher coordinate
        ui->infoBox->append("Oystercatcher #" + QString::number(i + 1) +
                            " R: " + QString::number(pixelRGB.red()) +
                            " G: " + QString::number(pixelRGB.green()) +
                            " B: " + QString::number(pixelRGB.blue()));

        // Returns true and adds to the counter if the RGB values match
        if (pixelRGB.red() == 20 &&
            pixelRGB.green() == 106 &&
            pixelRGB.blue() == 87) {
            ui->infoBox->append("Green pixel: true");
            counter++;
        }
    }

    // Gives final state of how many Oystercatchers are on green pixels
    ui->infoBox->append("<b>" + QString::number(counter) + "/" + QString::number(oystercatcherVector.size()) + " Oystercatchers are on green pixels. </b>");
}


// Runs the model until the time extent is reached
void MainWindow::on_startButton_clicked()
{
    ui->startButton->setEnabled(false); // Disabling button clicking while model runs

    simReset = false; // Setting the reset button tag back to false

    series->clear(); // Clearing any previous points from previous simulation runs

    // Resetting any old maps and reassigning the Pixmap
    QImage OystercatcherMapImage = park.getImage();
    pixmap->setPixmap(QPixmap::fromImage(OystercatcherMapImage));

    // Attaining the Oystercatcher and dog vectors
    oystercatcherVector = park.getOystercatcherVector();
    dogVector = park.getDogVector();

    // Rng objects
    std::random_device rd;
    mt = std::mt19937(rd());
    random_0_1 = std::uniform_real_distribution<float>(0.0, 1.0);

     float randomNum = random_0_1(mt);

    // Processes that run each timestep (day)
    for (int day = 0; day < temporalExtent && !simReset; day ++) {

        // If the reset button is pressed (which changes simReset to true), exit out of the function
        if (simReset) {

            return;
        }


        // Reporter variables
        int deadOystercatchers = 0;
        int liveOystercatchers = 0;
        int totalEggs = 0;
        int totalChicks = 0;
        int yr = floor(day / 365) + 1;
        int dy = day % 365;


        // All oyster methods go into this for-loop, so that they apply to every Oystercatcher each day
        for (unsigned long b = 0; b < oystercatcherVector.size(); b ++) {
            park.updateIndivPosition(b); // updates individual position
            oystercatcherVector[b].reproduction(day, oystercatcherVector, b); // Reproduce (if conditions within method are met)
            oystercatcherVector[b].eggHatch(day, oystercatcherVector, b); // Eggs hatch (if conditions within method are met)

            // Stopping model if all oystercatchers are dead - if all Oystercatchers have a true isDead arg, then model stops.
            if (oystercatcherVector[b].getIsDead() == true) {
                deadOystercatchers ++;
                if (static_cast<unsigned long>(deadOystercatchers) == oystercatcherVector.size()) {
                    ui->infoBox->append("<span style='color:red;'> All Oystercatchers have been predated. Model will stop here. </span>");
                    return;
                }
            }
        }


        // All dog methods go into this for-loop, so that the methods apply to each dog
        for (unsigned long d = 0; d < dogVector.size(); d++) {
            // If the policy scenario is checked->  On two of the seven days per week, there is a 50% chance a dog will be off-leash (reassigned arg)
            if (ui->policyScenario->isChecked()) {
                if (day % 7 == 2 ||
                    day % 7 == 5) {
                    if (randomNum < 0.5) {
                        dogVector[d].setLeashed(false); // some dogs get off leash privileges for the off-leash days
                    } else {
                        dogVector[d].setLeashed(true);
                    }
                // All the other days -> all dogs must be on leash (reassigned arg)
                } else {
                    dogVector[d].setLeashed(true);
                }
            }

            park.updateDogPosition(d); // Dog positions updated
            dogVector[d].spotOystercatcher(dogVector, d, oystercatcherVector); // Spotting individual Oystercatchers
            dogVector[d].spotNest(dogVector, d, oystercatcherVector); // Spotting Oystercatcher nests
        }


        // updates Oystercatcher map after dog and Oystercatcher processes (due to potential predation)
        park.updateOystercatcherMap();
        QImage OystercatcherMapImage = park.getImage();
        pixmap->setPixmap(QPixmap::fromImage(OystercatcherMapImage));

        // Displaying the status of each Oystercatcher (whether they are alive or predated and their IDs)
        ui->oystercatcherStatus->clear();
        for (unsigned long b = 0; b < oystercatcherVector.size(); b ++) {

            if (oystercatcherVector[b].getIsDead() == true) { // If oystercatcher is dead
                ui->oystercatcherStatus->append("Oystercatcher ID: <span style='color:blue;'>" + QString::number(oystercatcherVector[b].getID()) + "</span> , Status: <span style='color:red;'>Predated</span>");
            } else { // If oystercatcher is alive
                liveOystercatchers++;
                ui->oystercatcherStatus->append("Oystercatcher ID: <span style='color:blue;'>" + QString::number(oystercatcherVector[b].getID()) +
                                                                                       "</span>  , Status: <span style='color:green; '>Alive</span>");
            }
        }


        // Updating the series with new time and number of Oystercatchers
        chart->axisX()->setRange(0, day);
        chart->axisY()->setRange(0, static_cast<int>(oystercatcherVector.size()));
        series->append(day, liveOystercatchers);


        // Counts number of eggs and chicks each day
        for (unsigned long i = 0; i < oystercatcherVector.size(); i ++) {
            totalEggs += oystercatcherVector[i].getEggNum();
            totalChicks += oystercatcherVector[i].getChickNum();
        }

        // Divides eggs and chicks by 2 to correct double counting, as for loop runs over both parents, counting all eggs and chicks twice
        totalEggs = totalEggs/2;
        totalChicks = totalChicks/2;

        // Reporting year, day, and number of eggs and chicks each day
        ui->infoBox->setText("<b>Year: </b> " + QString::number(yr) + ", <b>Day: </b>" + QString::number(dy) +
                             " <br>Eggs laid: " + QString::number(totalEggs) +
                             " <br> Total Chicks: " + QString::number(totalChicks));

        if (day % 365 == 126) { // Fixes logixal bug: Eggs laid otherwise remains >0 when parents die during egg care
            totalEggs = 0;
        }

        // Updating the Oystercatcher vector
        oystercatcherVector = park.getOystercatcherVector();

        // If time conditions are met within method, chicks turn to adults
        // Note: This is not in above for-loop because oystercatcherVector has new Oystercatchers added
        park.chickToAdult(day, oystercatcherVector);

        // Processing the GUI to be able to see daily changes
        QCoreApplication::processEvents();
    }

    // When for-loop is over, Start button is enabled again
     ui->startButton->setEnabled(true);
}

 // If the on- and off-leash dogs secnario button is checked, uncheck all other scenario boxes, then change scenario param accordingly
void MainWindow::on_onLeash_OffLeash_Scenario_toggled(bool checked)
{
    ui->onLeash_Scenario->setChecked(false);
    ui->policyScenario->setChecked(false);

    if (checked == true) {
        park.setScenarioNumber(1);
    }
}

// If the on-leash dogs only scenario box is checked, uncheck all other scenario boxes, then adjust starting param accordingly
void MainWindow::on_onLeash_Scenario_toggled(bool checked)
{
    ui->onLeash_OffLeash_Scenario->setChecked(false);
    ui->policyScenario->setChecked(false);

    if (checked == true) {
        park.setScenarioNumber(2);
    }

}

// If the policy scenario box is checked, uncheck all other scenario boxes, then adjust starting param accordingly
void MainWindow::on_policyScenario_toggled(bool checked)
{
    ui->onLeash_OffLeash_Scenario->setChecked(false);
    ui->onLeash_Scenario->setChecked(false);
    if (checked == true) {
        park.setScenarioNumber(1);
    }

}


// Reset button - clears Oystercatcher and dog vectors, then recreates them and fetches them along with re-fetching the empty map image
// Reset button unable to be clicked again until after process is done, and also re-enables the Start button
void MainWindow::on_resetButton_clicked()
{
    ui->resetButton->setEnabled(false);
    ui->infoBox->clear();
    simReset = true;

    park.resetModel();

    dogVector = park.getDogVector(); // had std::vector<Dog>
    oystercatcherVector = park.getOystercatcherVector();

    QImage OystercatcherMapImage = park.getImage();
    pixmap->setPixmap(QPixmap::fromImage(OystercatcherMapImage));

    ui->resetButton->setEnabled(true);
    ui->startButton->setEnabled(true);

}



// Spinbox that adjusts the number of initial Oystercatchers. When changed, the initial Oystercatchers amount is changed accordingly
void MainWindow::on_numInitialOystercatchers_valueChanged(int arg1)
{
    park.setInitOystercatchers(arg1);
}


// Spinbox that adjusts the number of initial dogs is changed, the initial dogs amount is changed accordingly
void MainWindow::on_numInitialDogs_valueChanged(int arg1)
{
    park.setInitDogs(arg1);
}

