#ifndef QCHOOSEGUISTYLEIMPL_H
#define QCHOOSEGUISTYLEIMPL_H
//
#include <QDialog>
#include "ui_QChooseGUIStyle.h"

#include <QStyleFactory>

#include <QSettings>
//
class QChooseGUIStyleImpl : public QDialog, public Ui::QChooseGUIStyle
{
	Q_OBJECT
	
public:
	QChooseGUIStyleImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	
private slots:
	void on_keepButton_clicked();
	void on_tryButton_clicked();
	void on_quitButton_clicked();
	
private:
	QString beforeStyle;
};
#endif




