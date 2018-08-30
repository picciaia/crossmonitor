/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: mainwindow.cpp
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->spUpdate, SIGNAL(valueChanged(int)), this, SLOT(spUpdate_changed(int)));
    AddLog("Application started");
}

MainWindow::~MainWindow()
{

    delete ui;
}

//Add log information with timestamp
void MainWindow::AddLog(const QString& string)
{
    QDateTime current = QDateTime::currentDateTime();
    QString timestamp = current.toString("[dd.MM.yyyy]" );
    ui->txtLog->appendPlainText(timestamp + " " + string);
}

void MainWindow::spUpdate_changed(int v)
{
    QString s = "Refresh changed to " + QString::number(v) + " seconds";
    AddLog(s);
    UpdatePeriod(v);
}

//Display the cross values. This slot is signaled by the model
void MainWindow::OnCrossChanged(const Cross& cross)
{
    ui->lcdAsk->display( cross.Ask );
    ui->lcdBid->display(cross.Bid);
    ui->lblHigh->setText( QString::number(cross.High) );
    ui->lblLast->setText( QString::number(cross.Last) );
    ui->lblLow->setText( QString::number(cross.Low) );
    ui->lblOpen->setText( QString::number(cross.Open) );
    ui->lblTime->setText( QString::number(cross.Timestamp) );
    ui->lblVol->setText( QString::number(cross.Volume) );
    ui->lblVwap->setText( QString::number(cross.Vwap) );
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    emit CloseWindowEvent();
    event->accept();
}
