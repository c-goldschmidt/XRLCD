#include "main.h"
#include "mainprocess.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

	a.setOrganizationName("Manhattan");
	a.setOrganizationDomain("random.org");
	a.setApplicationName("XRLCD");
	
	MainProcess *task = new MainProcess(&a);

    QObject::connect(task, SIGNAL(done()), &a, SLOT(quit()));
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
