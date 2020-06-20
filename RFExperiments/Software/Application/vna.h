#ifndef VNA_H
#define VNA_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include "device.h"
#include "Traces/traceplot.h"
#include "sparamtable.h"
#include "calibration.h"
#include <QProgressDialog>
#include "Menu/menuaction.h"
#include "Traces/tracemodel.h"
#include "Traces/tracemarkermodel.h"

class VNA : public QMainWindow
{
    Q_OBJECT
public:
    VNA(QWidget *parent = nullptr);
private:
    static constexpr Protocol::SweepSettings defaultSweep = {
        .f_start = 100000000,
        .f_stop = 2000000000,
        .points = 101,
        .if_bandwidth = 1000,
        .mdbm_excitation = 0,
    };
private slots:
    void NewDatapoint(Protocol::Datapoint d);
private:
    void UpdateStatusPanel();
    Device device;
    Protocol::SweepSettings settings;
    unsigned int averages;
    void SettingsChanged();
    SParamTable dataTable;
    TraceModel traceModel;
    TraceMarkerModel *markerModel;


    // Calibration
    Calibration cal;
    Calkit calkit;
    bool calValid;
    Calibration::Measurement calMeasurement;
    bool calMeasuring;
    bool calWaitFirst;
    QProgressDialog calDialog;

    // Calibration menu
    MenuAction *mCalSOL1, *mCalSOL2, *mCalFullSOLT;

    // Status Labels
    QLabel lStart, lCenter, lStop, lSpan, lPoints, lBandwidth;
    QLabel lCalibration;
    QLabel lAverages;
signals:
    void dataChanged();
};

#endif // VNA_H
