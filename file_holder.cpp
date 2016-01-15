#include "file_holder.h"


file_holder::file_holder(QWidget *parent) 
	: QLabel("File:", parent)
{
	this->setFrameStyle(QFrame::Box);
}

/*
 * Responds to click events in the filename box by giving
 * user the option to select a file they want to check.
 */
void file_holder::mousePressEvent(QMouseEvent *event)
{	
	QString file_name = QFileDialog::getOpenFileName(this, 
										tr("Select Checksum File"));

	if(file_name != NULL) {
		emit new_file(file_name);
		this->setText("File: " + file_name);
	} else {
		this->setText("File: ");
	}

}