/*
 * MainWindow.cpp
 *
 *  Created on: 04.04.2016
 *      Author: gunit
 */

#include "MainWindow.h"

MainWindow::MainWindow(QObject *parent)
{
    Q_UNUSED(parent);

	tcpSocket = new QTcpSocket;
	connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
			this, SLOT(tcpChanged(QAbstractSocket::SocketState)));
    connect(tcpSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));


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



    lbMsg = new QLabel;
    lbMsg->setWordWrap(true);
    lbMsg->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);



    pbUp    = new QPushButton;
    pbDown  = new QPushButton;
    pbLeft  = new QPushButton;
    pbRight = new QPushButton;
    pbStop  = new QPushButton;

    QPixmap pmUp = QPixmap(":/images/up");
    pbUp->setIcon(pmUp);
    QPixmap pmDown = QPixmap(":/images/down");
    pbDown->setIcon(pmDown);
    QPixmap pmLeft = QPixmap(":/images/left");
    pbLeft->setIcon(pmLeft);
    QPixmap pmRight = QPixmap(":/images/right");
    pbRight->setIcon(pmRight);
    QPixmap pmStop = QPixmap(":/images/cross");
    pbStop->setIcon(pmStop);   
    
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

    pbUp->setMinimumHeight(pbUp->sizeHint().width());
    pbDown->setMinimumHeight(pbDown->sizeHint().width());
    pbLeft->setMinimumHeight(pbLeft->sizeHint().width());
    pbRight->setMinimumHeight(pbRight->sizeHint().width());
    pbStop->setMinimumHeight(pbStop->sizeHint().width());


    QGridLayout *glButtons = new QGridLayout;
    glButtons->addWidget(lbMsg, 0, 0);
    glButtons->addWidget(pbUp,    1, 1);
    glButtons->addWidget(pbLeft,  2, 0);
    glButtons->addWidget(pbStop,  2, 1);
    glButtons->addWidget(pbRight, 2, 2);
    glButtons->addWidget(pbDown,  3, 1);

    lbMsg->setText("Hallo");

    pbConnect = new QPushButton("Verbinde");
    connect(pbConnect, SIGNAL(clicked()), this, SLOT(connectTo()));

    pbExit = new QPushButton("Exit");
    connect(pbExit, SIGNAL(clicked(bool)), this, SLOT(close()));

    mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(lbMsg);
    mainLayout->addLayout(glButtons, 2);
    mainLayout->addWidget(pbConnect);
    mainLayout->addWidget(pbExit);

    QGroupBox *gridLayout = new QGroupBox;
    gridLayout->setLayout(mainLayout);


    setCentralWidget(gridLayout);

}


void MainWindow::slotSettings()
{
	if (dialog.exec() == QDialog::Accepted)
	{
		ip = dialog.getIP();
		port = dialog.getPort();
	}
}

void MainWindow::connectTo()
{
	if (tcpSocket->state() == QAbstractSocket::UnconnectedState)
	{
		tcpSocket->connectToHost(QHostAddress(ip), port.toInt());
        pbConnect->setText("Verbinden...");
		pbConnect->setDisabled(true);


	}

	if (tcpSocket->state() == QAbstractSocket::ConnectedState)
	{
        tcpSocket->close();
        pbConnect->setText("Verbinde");
	}

}

void MainWindow::tcpChanged(QAbstractSocket::SocketState state)
{

    if (state == QAbstractSocket::UnconnectedState)
	{
        pbConnect->setText("keine Verbindung");
		pbConnect->setDisabled(false);
		setConnected(false);
	}

    if (state == QAbstractSocket::ConnectedState)
	{
        pbConnect->setText("Verbindung beenden");
		pbConnect->setDisabled(false);
		setConnected(true);

	}

}

void MainWindow::setConnected(bool state)
{
	pbUp->setEnabled(state);
	pbDown->setEnabled(state);
	pbLeft->setEnabled(state);
	pbRight->setEnabled(state);
	pbStop->setEnabled(state);
}

void MainWindow::slotUp()
{
    tcpSocket->write("forward\n");
}

void MainWindow::slotDown()
{
    tcpSocket->write("back\n");
}

void MainWindow::slotLeft()
{
    tcpSocket->write("left\n");
}

void MainWindow::slotRight()
{
    tcpSocket->write("right\n");
}

void MainWindow::slotStop()
{
    
    tcpSocket->write("stop\n");
}

void MainWindow::readyRead()
{
    lbMsg->setText(tcpSocket->readAll());
}
