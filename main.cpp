/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Author: Daniele Picciaia
// Project: CrossMonitor
// url: https://github.com/picciaia/crossmonitor

// This is the main file of the application and reports the entry point (the 'main' method)
// It's responsible for the creation of the Model, the View and the Controller
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

#include "model.h"
#include "controller.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model m;
    m.CrossURL = "https://www.bitstamp.net/api/v2/ticker/btceur";
    m.UpdateSec = 10;

    MainWindow v;

    Controller c(m,v);
    c.Run();

    return a.exec();
}
