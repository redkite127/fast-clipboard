#ifndef ABOUTFCIMPL_H
#define ABOUTFCIMPL_H
//
#include <QDialog>
#include "ui_aboutFC.h"
//
class AboutFCImpl : public QDialog, public Ui::AboutFC
{
Q_OBJECT
public:
	AboutFCImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif




