#ifndef file_holder_h
#define file_holder_h

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QString>



class file_holder : public QLabel
{
	Q_OBJECT

	public:
		file_holder(QWidget *parent);
		
	protected:
		void mousePressEvent(QMouseEvent *event);

	signals:
		void new_file(QString filename);


};



#endif