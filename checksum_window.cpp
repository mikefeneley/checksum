#include "checksum_window.h"

#include <string>


/*
 * Intialize all display widgets and setup slots/signals
 *
 * @param data Pointer to object containing current file
 *			   and the comparison checksum
 */
checksum_window::checksum_window(checksum_data *data)
{

	const QString checksum_instructions = 
		"\nPaste hex valued checksum in the text box";
	const QString label_instructions = 
		"Click in the box to select checksum file";
	const QString function_instruction = 
		"Checksum Algorithim:";
	const QString submit_instruciton= 
		"Check";

	this->data = data;
	layout = new QGridLayout(this);
	checksum_label = new QLabel(checksum_instructions, this);
	file_label = new QLabel(label_instructions);
	checksum_type = new QLabel(function_instruction);
	checksum = new QPlainTextEdit(this);

	md5 = new QRadioButton("md5", this);
	sha256 = new QRadioButton("sha256", this);
	sha512 = new QRadioButton("sha512", this);
	sha1 = new QRadioButton("sha1", this);
	submit = new QPushButton(submit_instruciton, this);
	file_display = new file_holder(this);
	this->add_widgets();
	this->setup_signals();
}

/*
 * Add all application widgets using grid layout.
 */
void checksum_window::add_widgets()
{
	layout->addWidget(file_label, 0, 0, 1, 5);
	layout->addWidget(file_display, 1, 0, 1, 5);
	layout->addWidget(checksum_label, 2, 0);
	layout->addWidget(checksum, 3, 0, 1, 6);
	layout->addWidget(checksum_type, 4, 0);
	layout->addWidget(md5, 4, 1);
	layout->addWidget(sha256, 4, 2);
	layout->addWidget(sha512, 4, 3);
	layout->addWidget(sha1, 4, 4);
	layout->addWidget(submit, 5, 0, 1, 5);
}


void checksum_window::setup_signals()
{
	connect(file_display, SIGNAL(new_file(QString)), 
			this, SLOT(update_filename(QString)));
	connect(submit, SIGNAL(clicked(bool)), 
			this, SLOT(check_checksum(bool)));
}

/*
 * Checks which widget algorithim is selected and then compares the
 * checksum of the currently selected file calculated with that 
 * algorthim against the checksum currently in the text field.
 * 
 * @param bool True if the button has been pressed, otherwise false
 */
void checksum_window::check_checksum(bool)
{
	const QString window_title = "Checksum Results";

	QString current_checksum = checksum->toPlainText();
	data->set_checksum(current_checksum);	

	algo algorithim;
	if(md5->isChecked()) {
		algorithim = Md5;
	} else if(sha256->isChecked()) {
		algorithim = Sha256;
	} else if(sha512->isChecked()) {
		algorithim = Sha512;
	} else if (sha1->isChecked()) {
		algorithim = Sha1;
	} else {
		algorithim = none;
	}

	QString hashcheck_result = data->compare_checksum(algorithim);
	QMessageBox box(this);
	box.setText(hashcheck_result);
	box.setWindowTitle(window_title);
	box.exec();
}


void checksum_window::update_filename(QString filename)
{
	data->set_filename(filename);
}

checksum_window::~checksum_window()
{
	delete layout;
	delete checksum_label;
	delete file_label;
	delete checksum_type;
	delete checksum;
	delete md5;
	delete sha256;
	delete sha512;
	delete sha1;
	delete submit;
	delete file_display;
}