/*
 * SettingsDialog.cpp
 *
 *  Created on: 04.04.2016
 *      Author: gunit
 */

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QObject *parent)
{

    Q_UNUSED(parent);

	QLabel *labelIP = new QLabel("IP");
	QLabel *labelPort = new QLabel("Port");

 	leIP = new QLineEdit("192.168.1.1");
	lePort = new QLineEdit("22");


	QGridLayout *labelLayout = new QGridLayout;
	labelLayout->addWidget(labelIP, 0, 0);
	labelLayout->addWidget(leIP, 0, 1);
	labelLayout->addWidget(labelPort, 1, 0);
	labelLayout->addWidget(lePort, 1, 1);


	pbOK  = new QPushButton("OK");
	pbESC = new QPushButton("ESC");


	connect(pbOK, SIGNAL(clicked()), this, SLOT(accept()));
	connect(pbESC, SIGNAL(clicked()), this, SLOT(reject()));

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(pbESC);
	buttonLayout->addWidget(pbOK);


	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(labelLayout);
	mainLayout->addLayout(buttonLayout);



	setLayout(mainLayout);

    this->setWindowState(Qt::WindowFullScreen);

}

QString SettingsDialog::getIP()
{
	return leIP->text();
}

QString SettingsDialog::getPort()
{
	return lePort->text();
}

