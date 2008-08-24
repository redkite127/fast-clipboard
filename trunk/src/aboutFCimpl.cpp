#include "aboutFCimpl.h"
//
AboutFCImpl::AboutFCImpl( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
	this->setModal(true);
}
//
