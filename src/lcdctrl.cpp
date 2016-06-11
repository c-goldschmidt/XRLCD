#include "lcdctrl.h"

LCDController::LCDController(QObject *parent) : QObject(parent) {
	LogiLcdInit((wchar_t*) "XRebirth Monitor", LOGI_LCD_TYPE_MONO);
	isInitialized = LogiLcdIsConnected(LOGI_LCD_TYPE_MONO);

	if (!isInitialized) {
		qDebug() << "no LCD panel!";
	}	
}

LCDController::~LCDController() {
	if (!isInitialized) {
		return;
	}
	LogiLcdShutdown();
}

void LCDController::setValues(LogParser::infopackage pkg) {
	if (!isInitialized) {
		return;
	}
	qDebug() << "updating lcd panel";

	wchar_t text[1024];

	swprintf_s(text, 1023, L"Hull: %s / %s\0", numberFormat(pkg.currentHull), numberFormat(pkg.maxHull));
	LogiLcdMonoSetText(0, text);
	
	swprintf_s(text, 1023, L"Shield: %s / %s\0", numberFormat(pkg.currentShield), numberFormat(pkg.maxShield));
	LogiLcdMonoSetText(1, text);
	
	swprintf_s(text, 1023, L"Money: %s\0", numberFormat(pkg.money, true));
	LogiLcdMonoSetText(2, text);

	LogiLcdUpdate();
}

const wchar_t * LCDController::qStringToWcharT(QString in) {
	int length = in.length();
	wchar_t* buffer = (wchar_t*) malloc(length + +1);

	in.toWCharArray(buffer);
	buffer[length] = L'\0';

	return const_cast<wchar_t*>(buffer);
}

const wchar_t * LCDController::numberFormat(double in, bool money) {
	QStringList prefixes;
	int max = 1000;
	QString retVal;

	if (money) {
		in /= 100; //money is in cents
		max = 1000000;
		prefixes << "Cr" << "Mio Cr" << "Mrd Cr" << "B Cr";
	} else {
		prefixes << "" << "K" << "M" << "T";
	}
	
	int currentIndex = 0;

	if (in > max) {
		in /= max;
		currentIndex++;
	}

	while (in > 1000) {
		in /= 1000;
		currentIndex++;
	}

	retVal.sprintf("%.2f", in);
	
	//qDebug() << retVal + " " + prefixes.takeAt(currentIndex);

	return qStringToWcharT(retVal + " " + prefixes.takeAt(currentIndex));
}