#pragma once
#include "main.h"
#include "logparser.h"
#include "LogitechLCDLib.h"

class LCDController : public QObject
{

	Q_OBJECT

public:
	LCDController(QObject *parent = 0);
	~LCDController();

private:
	bool isInitialized;
	const wchar_t * numberFormat(double in, bool money = false);
	const wchar_t * qStringToWcharT(QString in);

public slots:
	void setValues(LogParser::infopackage);

};