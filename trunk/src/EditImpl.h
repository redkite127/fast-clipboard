#ifndef EDITIMPL_H
#define EDITIMPL_H
//
#include <QDialog>
#include <QHostInfo>

#include "ui_edit.h"
#include "FCxml.h"
//

class EditImpl : public QDialog, public Ui::Edit
{
	Q_OBJECT

public:
	EditImpl(FCxml* x,int n=1, QWidget * parent = 0, Qt::WFlags f = 0 );
	
private slots:
	void on_buttonBox_accepted();
	void on_buttonBox_rejected();

private:
	void loadItem(); // Comment faire? loadItem(FCxml, int) ou des variables comme fait ici? ...
	int num;
	FCxml *xmlDoc;
};
#endif
