/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: model.h
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

#ifndef MODEL_H
#define MODEL_H

#include "cross.h"
#include <QObject>
#include <QString>

class Model : public QObject
{
    Q_OBJECT


public:
    Model();

    void Cross_Set(const Cross& lastCross);

    Cross cross;
    QString CrossURL;
    int UpdateSec;

signals:
    void CrossChanged(const Cross& cross);
};

#endif // MODEL_H
