/*
 * SettingsDialog.h
 *
 *  Created on: 04.04.2016
 *      Author: gunit
 */

#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include <QBoxLayout>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>


class SettingsDialog: public QDialog
{

	Q_OBJECT


public:
	SettingsDialog(QObject *parent = 0);
	QString getIP();
	QString getPort();


private:
	QLineEdit *leIP, *lePort;
	QPushButton *pbOK, *pbESC;

};

#endif /* SETTINGSDIALOG_H_ */
