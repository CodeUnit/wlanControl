/*
 * MainWindow.cpp
 *
 *  Created on: 04.04.2016
 *      Author: gunit
 */

#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent)
{

	tcpSocket = new QTcpSocket;
	connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
			this, SLOT(tcpChanged(QAbstractSocket::SocketState)));


	SettingsDialog dialog(this);
	ip = dialog.getIP();
	port = dialog.getPort();


    QMenu *fileMenu = menuBar()->addMenu(tr("&Settings"));
//    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&Settings"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Settings"));
    connect(newAct, &QAction::triggered, this, &MainWindow::slotSettings);
    fileMenu->addAction(newAct);
//    fileToolBar->addAction(newAct);





    pbUp    = new QPushButton(" UP  ");
    pbDown  = new QPushButton("DOWN ");
    pbLeft  = new QPushButton("LEFT ");
    pbRight = new QPushButton("RIGHT");
    pbStop  = new QPushButton("STOP ");

    connect(pbUp, SIGNAL(clicked()), this, SLOT(slotUp()));
    connect(pbDown, SIGNAL(clicked()), this, SLOT(slotDown()));
    connect(pbLeft, SIGNAL(clicked()), this, SLOT(slotLeft()));
    connect(pbRight, SIGNAL(clicked()), this, SLOT(slotRight()));
    connect(pbStop, SIGNAL(clicked()), this, SLOT(slotStop()));

	pbUp->setEnabled(false);
	pbDown->setEnabled(false);
	pbLeft->setEnabled(false);
	pbRight->setEnabled(false);
	pbStop->setEnabled(false);


    QGridLayout *glButtons = new QGridLayout;
    glButtons->addWidget(pbUp,    0, 1);
    glButtons->addWidget(pbLeft,  1, 0);
    glButtons->addWidget(pbStop,  1, 1);
    glButtons->addWidget(pbRight, 1, 2);
    glButtons->addWidget(pbDown,  2, 1);



    pbConnect = new QPushButton("Verbinde");
    connect(pbConnect, SIGNAL(clicked()), this, SLOT(connectTo()));

    pbExit = new QPushButton("Exit");
    connect(pbExit, SIGNAL(clicked(bool)), this, SLOT(close()));



    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(pbConnect);
    mainLayout->addLayout(glButtons);
    mainLayout->addWidget(pbExit);

    QGroupBox *gridLayout = new QGroupBox;
    gridLayout->setLayout(mainLayout);


    setCentralWidget(gridLayout);

    qDebug() << dialog.getIP();
}


void MainWindow::slotSettings()
{


	if (dialog.exec() == QDialog::Accepted)
	{
		ip = dialog.getIP();
		port = dialog.getPort();
	}
	qDebug() << ip << port;
}

void MainWindow::connectTo()
{
	if (tcpSocket->state() == QAbstractSocket::UnconnectedState)
	{
		qDebug() << __FUNCTION__ << "verbinde";
		tcpSocket->connectToHost(QHostAddress(ip), port.toInt());
		pbConnect->setText("versuche zu verbinden...");
		pbConnect->setDisabled(true);
	}

	if (tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
		qDebug() << __FUNCTION__ << "BEENDEN";
		tcpSocket->close();
		pbConnect = new QPushButton("Verbinde");
	}

}

void MainWindow::tcpChanged(QAbstractSocket::SocketState state)
{
	qDebug() << __FUNCTION__ ;
	if (state == QAbstractSocket::UnconnectedState)
	{
		qDebug() << state;
		pbConnect->setText("Verbindung beendet");
		pbConnect->setDisabled(false);
		setConnected(false);
	}

	if (state == QAbstractSocket::ConnectedState)
	{
		qDebug() << state;
		pbConnect->setText("Verbindung beenden");
		pbConnect->setDisabled(false);
		setConnected(true);
		pbConnect->setText("Verbindung beenden");
	}



}

void MainWindow::setConnected(bool state)
{
	qDebug() << __FUNCTION__;
	pbUp->setEnabled(state);
	pbDown->setEnabled(state);
	pbLeft->setEnabled(state);
	pbRight->setEnabled(state);
	pbStop->setEnabled(state);
}

void MainWindow::slotUp()
{
	tcpSocket->write("v");
}

void MainWindow::slotDown()
{
	tcpSocket->write("b");
}

void MainWindow::slotLeft()
{
	tcpSocket->write("l");
}

void MainWindow::slotRight()
{
	tcpSocket->write("r");
}

void MainWindow::slotStop()
{
	tcpSocket->write("s");
}
