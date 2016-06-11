#include "main.h"
#include "mainprocess.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
	
	MainProcess *task = new MainProcess(&a);

    // This will cause the application to exit when
    // the task signals finished.    
    QObject::connect(task, SIGNAL(done()), &a, SLOT(quit()));
	
    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
