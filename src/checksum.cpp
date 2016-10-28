#include <QApplication>
#include "parent_window.h"


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	parent_window *parent = new parent_window();	
 	return app.exec();

}


