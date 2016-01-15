#ifndef parent_window_h
#define parent_window_h

#include <QWidget>
#include "checksum_data.h"
#include "checksum_window.h"

class parent_window : public QWidget
{
	Q_OBJECT

	public:
		parent_window();

	private:
		checksum_window *window;
		checksum_data data;


};



#endif