#include "parent_window.h"

parent_window::parent_window()
{
	window = new checksum_window(&data);
	window->show();
}