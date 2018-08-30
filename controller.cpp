/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: controller.cpp
// Author: Daniele Picciaia
// Project: CrossMonitor
// url: https://github.com/picciaia/crossmonitor
// Controller class that is responsible to create signal/slots to interfa with the View and the CrossProvider
// object to update cross information
// For more information please refer to 'readme.md' file

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

#include "controller.h"

using namespace std;

Controller::Controller(Model& model, MainWindow& view) :
    currentModel {model}, currentView {view}, isRunning{false}
{
}

void Controller::Run()
{
    //Configure signals/slots
    connect(&currentModel, SIGNAL(CrossChanged(const Cross&)),
            &currentView, SLOT(OnCrossChanged(const Cross&)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(TimerUpdate()));
    connect(&currentView, SIGNAL(UpdatePeriod(int)), this, SLOT(OnUpdatePeriod(int)));
    connect(&currentView, SIGNAL(CloseWindowEvent()), this, SLOT(OnCloseWindowEvent()));

    //start the timer to update cross info, by supporting signals/slots
    timer.start(currentModel.UpdateSec * 1000);
    timer.setInterval(currentModel.UpdateSec * 1000);

    crossProvider.Init();
    isRunning = true;

    currentView.show();

    //First cross info reading
    UpdateCross();
}

//This method (slot) is called by the view, when the application is closing
void Controller::Exit()
{
    isRunning = false;
    timer.stop();

    disconnect(&currentModel, SIGNAL(CrossChanged(const Cross&)),
            &currentView, SLOT(OnCrossChanged(const Cross&)));
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(TimerUpdate()));
    disconnect(&currentView, SIGNAL(UpdatePeriod(int)), this, SLOT(OnUpdatePeriod(int)));
    disconnect(&currentView, SIGNAL(CloseWindowEvent()), this, SLOT(OnCloseWindowEvent()));
}

//This method (slot) is called by the view, to update the refresh period
void Controller::OnUpdatePeriod(int seconds)
{
    currentModel.UpdateSec = seconds;
    timer.setInterval(seconds * 1000);
}

//This method (slot) is called by the internal timer to execute a cross reading operation
void Controller::TimerUpdate()
{
    UpdateCross();
}

//get cross data (by using CrossProvider) and update the Model
void Controller::UpdateCross()
{
    try
    {
        auto cross = this->crossProvider.GetCross(this->currentModel.CrossURL);
        currentModel.Cross_Set(cross);
    }
    catch (exception& e)
    {
        this->currentView.AddLog(e.what());
    }
    catch (...)
    {
        this->currentView.AddLog("Error on server communication");
    }

}

void Controller::OnCloseWindowEvent()
{
    Exit();
}
