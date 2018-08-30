/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: controller.h
// Author: Daniele Picciaia
// Project: CrossMonitor
// url: https://github.com/picciaia/crossmonitor
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "mainwindow.h"
#include "crossprovider.h"

#include <future>
#include <QObject>
#include <thread>
#include <chrono>
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(Model& model, MainWindow& view);
    void Run();
    void Exit();

public slots:
    void OnUpdatePeriod(int seconds);
    void OnCloseWindowEvent();

private:
    Model& currentModel;
    MainWindow& currentView;
    CrossProvider crossProvider;
    bool isRunning;
    QTimer timer;

    void UpdateCross();

private slots:
    void TimerUpdate();
};

#endif // CONTROLLER_H
