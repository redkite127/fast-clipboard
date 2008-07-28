#include "editimpl.h"
//
EditImpl::EditImpl(int n, QWidget * parent, Qt::WFlags f) : QDialog(parent, f)
{
	setupUi(this);
	this->setModal(true);
	
	//titre->setText(QString("%1").arg(n));
	this->num = n;
}
//
