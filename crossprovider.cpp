/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File: crossprovider.cpp
// Author: Daniele Picciaia
// Project: CrossMonitor
// url: https://github.com/picciaia/crossmonitor
// CrossProvider object is used to update cross info from bitstamp site
// It uses APIv2 and parses result using JSON

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


#include "crossprovider.h"

using namespace std;


CrossProvider::CrossProvider()
{

}

void CrossProvider::Init()
{
    manager = new QNetworkAccessManager();
}

Cross& CrossProvider::GetCross(const QString& url)
{
    QSslConfiguration config = request.sslConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setRawHeader("User-Agent", "CustomAgent 0.0.0");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        QString answer = reply->errorString();
        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        answer = "Error:\n" + answer + "\n" + QString::number(statusCode);
        std::string msg = answer.toUtf8().constData();
        throw  exception(msg.c_str());
    }

    QString answer = reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["status"].toArray();

    if(jsonObject["ask"].isString())
        cross.Ask = jsonObject["ask"].toString().toDouble();
    cross.Bid = jsonObject["bid"].toString().toDouble();
    cross.High = jsonObject["high"].toString().toDouble();
    cross.Last = jsonObject["last"].toString().toDouble();
    cross.Low = jsonObject["low"].toString().toDouble();
    cross.Open = jsonObject["open"].toString().toDouble();
    cross.Timestamp = jsonObject["timestamp"].toString().toInt();
    cross.Volume = jsonObject["volume"].toString().toDouble();
    cross.Vwap = jsonObject["vwap"].toString().toDouble();

    return cross;
}

