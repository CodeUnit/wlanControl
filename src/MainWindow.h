/*
 * MainWindow.h
 *
 *  Created on: 04.04.2016
 *      Author: gunit
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_



#include <QAbstractSocket>
#include <QAction>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QHostAddress>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QTcpSocket>
#include <QToolBar>
#include <QVBoxLayout>


#include "SettingsDialog.h"

class MainWindow : public QMainWindow
{

	Q_OBJECT

public:
	MainWindow(QObject *parent = 0);

private:
	SettingsDialog dialog;
	QTcpSocket *tcpSocket;

    QVBoxLayout *mainLayout;
    QPushButton *pbExit, *pbUp, *pbDown, *pbLeft, *pbRight, *pbStop, *pbConnect;
    QLabel *lbMsg;

	QString ip, port;
    bool verbunden;


signals:


public slots:
    void readyRead();


private slots:
	void connectTo();
    void slotSettings();
    void tcpChanged(QAbstractSocket::SocketState);
    void setConnected(bool state);
    void slotUp();
    void slotDown();
    void slotLeft();
    void slotRight();
    void slotStop();


};

#endif /* MAINWINDOW_H_ */
