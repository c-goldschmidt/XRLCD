#pragma once
#include "main.h"

class LogParser : public QObject
{

	Q_OBJECT

public:
	LogParser(QSettings* settings, QObject *parent = 0);

	struct infopackage {
		double currentShield = 0;
		double maxShield = 0;
		double currentHull = 0;
		double maxHull = 0;
		double money = 0;
	};

private:
	QRegularExpression rx;
	QSettings* settings;
	void createInfoPackage(QString match);

public slots:
	void parseLine(QString);

signals:
	void setValues(LogParser::infopackage);

};