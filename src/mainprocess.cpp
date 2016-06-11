#include "mainprocess.h"

bool MainProcess::keepRunning;

MainProcess::MainProcess(QObject *parent) : QThread(parent) {
	QString settingsFile = QCoreApplication::applicationDirPath() + "/settings.ini";
	settings = new QSettings(settingsFile, QSettings::IniFormat);
	
	parser = new LogParser(settings, this);
	ctrl = new LCDController(this);

	QString logfile = settings->value("main/logfile", "").toString();

	file = new QFile(logfile);
	if (logfile != "") {
		keepRunning = file->open(QIODevice::ReadOnly | QIODevice::Text);
	} else {
		keepRunning = false;
	}	
	
	if (!keepRunning) {
		qDebug() << "error opening file!";
		system("pause");
	}

	connect(this, SIGNAL(runAgain()), this, SLOT(run()));
	connect(this, SIGNAL(lineRead(QString)), parser, SLOT(parseLine(QString)));
	connect(parser, SIGNAL(setValues(LogParser::infopackage)), ctrl, SLOT(setValues(LogParser::infopackage)));

	//TODO: non win-specific version
	SetConsoleCtrlHandler((PHANDLER_ROUTINE) handleSIGINT, TRUE);

	qDebug() << "up and running!";
}

MainProcess::~MainProcess(){
	if (file->isOpen()) {
		file->close();
	}
}

bool WINAPI MainProcess::handleSIGINT(DWORD reason) {
	keepRunning = false;
	return false;
}

void MainProcess::stop() {
	keepRunning = false;
}

void MainProcess::run(){
	QString line;
	if (keepRunning) {

		if (file->bytesAvailable()) {
			emit lineRead(file->readLine());
		} else {
			sleep(1);
		}

		emit runAgain();
	}
	emit done();
}