/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: cross.h
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

#ifndef CROSS_H
#define CROSS_H


class Cross
{
public:
    Cross();

    double High;
    double Last;
    long Timestamp;
    double Bid;
    double Vwap;
    double Volume;
    double Low;
    double Ask;
    double Open;
};

#endif // CROSS_H
