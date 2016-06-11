#include "logparser.h"

LogParser::LogParser(QSettings* settings, QObject *parent) : QObject(parent) {

	QString script_ident = settings->value("main/ident", "md.XRLCDMain.XRLCD_interval").toString();
	QString regexPattern = "^\\[Scripts\\] (\\d+\\.\\d+).+Context:" + QRegularExpression::escape(script_ident) + ".+: (.+)$";
	rx = QRegularExpression(
		regexPattern,
		QRegularExpression::CaseInsensitiveOption | QRegularExpression::MultilineOption
	);
}

void LogParser::parseLine(QString line) {
	QRegularExpressionMatch match = rx.match(line);

	if (match.hasMatch()) {
		createInfoPackage(match.captured(2));
	} else {
		//qDebug() << "no match for" << line;
	}
}

void LogParser::createInfoPackage(QString values) {
	infopackage pkg;
	QStringList split = values.split(",");

	if (split.length() == 5) {
		pkg.currentShield = split[0].toDouble();
		pkg.maxShield = split[1].toDouble();
		pkg.currentHull = split[2].toDouble();
		pkg.maxHull = split[3].toDouble();
		pkg.money = split[4].toDouble();
	}

	//qDebug() << "shield: " << pkg.currentShield << " / " << pkg.maxShield;
	//qDebug() << "hull: " << pkg.currentHull << " / " << pkg.maxHull;
	//qDebug() << "money: " << pkg.money;

	emit setValues(pkg);
}