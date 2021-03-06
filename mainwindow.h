/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in 
** accordance with the Qt Commercial License Agreement provided with
** the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgeomappingmanager.h>

#include <QMainWindow>
#include <QGraphicsView>
#include <QGeoServiceProvider>
#include <qnetworksession.h>
#include <QGeoPositionInfo>
#include <QGeoMapPixmapObject>
#include <QGeoPositionInfoSource>
#include <QPointer>
#include <QSlider>

#include <QUrl>
#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QtScript/QScriptEngine>
#include <QDebug>
#include <QScriptValueIterator>




class QResizeEvent;
class QShowEvent;

class MapWidget;

QTM_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void fetchJSON(QUrl url);
    bool processJSON(QNetworkReply* reply);

protected:
    void resizeEvent(QResizeEvent* /*event*/);
    void showEvent(QShowEvent* /*event*/);

private:
    void setupMap();
    void setupMenu();
    void setProvider(QString providerId);

private slots:
    void networkSessionOpened();
    void error(QNetworkSession::SessionError error);
    void positionUpdated(QGeoPositionInfo geoPositionInfo);
    void startStopPositionMonitor();
    void replyFinished(QNetworkReply* reply );

    void sliderValueChanged(int zoomLevel);
    void mapZoomLevelChanged(qreal zoomLevel);
    void hideShowZoom();

    void addPOI();


signals:
        void finished( bool success );

private:
    QGeoServiceProvider*        m_serviceProvider;
    QGeoMappingManager*         m_mapManager;
    MapWidget*                  m_mapWidget;

    QGraphicsView* m_qgv;

    QSlider*                m_slider;
    QNetworkSession*        m_session;
    QGeoMapPixmapObject* m_myPositionMarker;

    QPointer<QGeoPositionInfoSource> locationDataSource;
    QGeoPositionInfo myPositionInfo;

    //QHttp* m_Http;
    QTemporaryFile m_TempFile;

};

#endif // MAINWINDOW_H
