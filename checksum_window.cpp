#include "checksum_window.h"

#include "iostream"

#include <string>


checksum_window::checksum_window(checksum_data *data)
{

	this->data = data;
	layout = new QGridLayout(this);
	checksum_label = new QLabel("\nPaste checksum in the text box", this);
	file_label = new QLabel("Click in the box or drag file to box to select checksum file");
	checksum_type = new QLabel("Checksum Algorithim:");
	checksum = new QPlainTextEdit(this);

	md5 = new QRadioButton("md5", this);
	sha256 = new QRadioButton("sha256", this);
	sha512 = new QRadioButton("sha512", this);
	sha1 = new QRadioButton("sha1", this);
	submit = new QPushButton("Check", this);
	file_display = new file_holder(this);

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

	this->setup_signals();
	
}

void checksum_window::setup_signals()
{
	connect(file_display, SIGNAL(new_file(QString)), 
			this, SLOT(update_filename(QString)));
	connect(submit, SIGNAL(clicked(bool)), this, SLOT(check_checksum(bool)));

}


// Remove trailing whitespace in checksum to correct for user mistake????
void checksum_window::check_checksum(bool)
{

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
	box.setWindowTitle("Checksum Results");
	box.exec();
}
void checksum_window::update_filename(QString filename)
{
	data->set_filename(filename);
}
