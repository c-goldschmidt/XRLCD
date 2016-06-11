#pragma once
#include "main.h"
#include "logparser.h"
#include "lcdctrl.h"
#include <Windows.h>

class MainProcess : public QThread
{
    Q_OBJECT
				
public:
	MainProcess(QObject *parent = 0);
	~MainProcess();
	static bool WINAPI handleSIGINT(DWORD reason);
	static bool keepRunning;

public slots:
    void run();
	void stop();

private:
	LogParser* parser;
	LCDController* ctrl;
	QFile* file;
	const static QString LOGFILE;

signals:
	void runAgain();
	void done();
	void lineRead(QString);
};
