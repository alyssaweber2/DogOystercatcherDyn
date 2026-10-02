#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <park.h>
#include <dog.h>
#include <oystercatcher.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();




private slots:

    // For zooming the map image
    void on_horizontalSlider_sliderMoved(int position);

    // Starting the simulation
    void on_startButton_clicked();

    // Conducting the unit test
    void on_unitTestButton_clicked();

    // Toggles scenario containing both on- and off-leash dogs
    void on_onLeash_OffLeash_Scenario_toggled(bool checked);

    // Toggles scenario containing only on-leash dogs
    void on_onLeash_Scenario_toggled(bool checked);

    // Toggle policy scenario - off-leash dogs only allowed two days per week
    void on_policyScenario_toggled(bool checked);

    // Resetting the model
    void on_resetButton_clicked();

    // Spinbox for changing the number of initial Oystercatchers in the model
    void on_numInitialOystercatchers_valueChanged(int arg1);

    // Spinbox for changing the number of initial dogs in the model
    void on_numInitialDogs_valueChanged(int arg1);


private:
    Ui::MainWindow *ui;

    // Park object to store/use all park data and methods
    Park park;

    // Scene pointer
    QGraphicsScene *scene;

    // Image pointer
    QGraphicsPixmapItem *pixmap;

    // Fetching image from Park class
    QImage image = park.getImage();

    // Amount of time that the model will run for. Temporal grain = 1 day. Temporal Extent = 7 years (7 * 365 = 2555 days)
    int temporalExtent = 2555;

    // Random number generator objects
    std::mt19937 mt;
    std::uniform_real_distribution<float> random_0_1;


    // Dog vector and Oystercatcher vector reference objects
    std::vector<Dog> &dogVector = park.getDogVector();
    std::vector<Oystercatcher> &oystercatcherVector = park.getOystercatcherVector();


    // Resetting the simulation boolean; true when reset button is pressed
    bool simReset = false;

    // QChart Objects for the graph
    QLineSeries *series; // Points to storage for the data points
    QChart * chart; // the chart pointer


};
#endif // MAINWINDOW_H
