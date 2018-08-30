/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QCloseEvent>

#include "cross.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddLog(const QString& str);

public slots:
    void OnCrossChanged(const Cross& cross);

signals:
    void UpdatePeriod(int seconds);
    void CloseWindowEvent();

private:
    void closeEvent(QCloseEvent *event);
    Ui::MainWindow *ui;

private slots:
    void spUpdate_changed(int v);
};

#endif // MAINWINDOW_H
