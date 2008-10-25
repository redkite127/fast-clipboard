#include "QChooseGUIStyleImpl.h"
//

QChooseGUIStyleImpl::QChooseGUIStyleImpl( QWidget * parent, Qt::WFlags f) : QDialog(parent, f)
{
	setupUi(this);
	
	// Save the style used at the beginning
	beforeStyle = QApplication::style()->objectName();
	currentStyleLabel->setText( beforeStyle );
	
	// List of supported styles :
	const QStringList supportedList = QStyleFactory::keys();
	stylesList->addItems(supportedList);
	stylesList->setCurrentRow(0);
}

void QChooseGUIStyleImpl::on_tryButton_clicked()
{
	// Set the selected style
	QApplication::setStyle( QStyleFactory::create( stylesList->currentItem()->text() ) );
	currentStyleLabel->setText( stylesList->currentItem()->text() );
	
	if ( QString::compare(beforeStyle, currentStyleLabel->text(), Qt::CaseInsensitive) )
		keepButton->setEnabled(true);
	else
		keepButton->setEnabled(false);
};

void QChooseGUIStyleImpl::on_keepButton_clicked()
{
	beforeStyle = QApplication::style()->objectName();
	keepButton->setEnabled(false);
};

void QChooseGUIStyleImpl::on_quitButton_clicked()
{
	QApplication::setStyle( QStyleFactory::create( beforeStyle ) );
	this->close();
};
//
