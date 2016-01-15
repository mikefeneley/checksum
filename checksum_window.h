#ifndef checksum_window_h
#define checksum_window_h

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QRadioButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QPlainTextEdit>
#include "checksum_data.h"
#include "file_holder.h"


class checksum_window : public QWidget
{

	Q_OBJECT

	public:
		checksum_window(checksum_data *data);


	private slots:
		void update_filename(QString filename);
		void check_checksum(bool);

	private:
		void setup_signals();

	private:
		QGridLayout *layout;
		QRadioButton *md5;
		QRadioButton *sha256;
		QRadioButton *sha512;
		QRadioButton *sha1;

		QPlainTextEdit *checksum;
		QPushButton *submit;
		QLabel *checksum_label;
		QLabel *file_label;
		QLabel *checksum_type;
		QFileDialog *selector;
		checksum_data *data;
		file_holder *file_display;
};


#endif