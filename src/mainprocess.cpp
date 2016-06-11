#include "mainprocess.h"

const QString MainProcess::LOGFILE = QString("D:\\Daten\\Documents\\Egosoft\\X Rebirth\\46897086\\debuglog.txt");
bool MainProcess::keepRunning;

MainProcess::MainProcess(QObject *parent) : QThread(parent) {
	parser = new LogParser(this);
	ctrl = new LCDController(this);
	file = new QFile(LOGFILE);

	keepRunning = file->open(QIODevice::ReadOnly | QIODevice::Text);
	
	if (!keepRunning) {
		qDebug() << "error opening file!";
	}

	connect(this, SIGNAL(runAgain()), this, SLOT(run()));
	connect(this, SIGNAL(lineRead(QString)), parser, SLOT(parseLine(QString)));
	connect(parser, SIGNAL(setValues(LogParser::infopackage)), ctrl, SLOT(setValues(LogParser::infopackage)));

	//TODO: non win-specific version
	SetConsoleCtrlHandler((PHANDLER_ROUTINE) handleSIGINT, TRUE);
}

MainProcess::~MainProcess(){
	file->close();
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
	
	if (file->bytesAvailable()) {
		emit lineRead(file->readLine());
	} else {
		sleep(1);
	}

	if (keepRunning) {
		emit runAgain();
	}
	emit done();
}