#include "editimpl.h"

#include <QMessageBox>
//
EditImpl::EditImpl(FCxml * x,int n, QWidget * parent, Qt::WFlags f) : QDialog(parent, f)
{
	setupUi(this);
	this->setModal(true);
	
	//connect(buttonBox,SIGNAL(accepted()),this,SLOT(acc()));
	//connect(buttonBox,SIGNAL(rejected()),this,SLOT(rej()));
	
	//titre->setText(QString("%1").arg(n));
	
	this->num = n;
	this->xmlDoc = x;
	
	loadItem();
}

void EditImpl::loadItem()
{
	QStringList r;
	
	r = xmlDoc->lireX(num);
	if(r.size()==2)
	{
		titre->setText(r.at(0));
		texte->setPlainText(r.at(1)); // FIXME, verfifier qu'y en a bien 2 sinon crash	
	}
	else
		titre->setText("Error in the structur of the XML file !");
}

void EditImpl::on_buttonBox_accepted()
{
	//qDebug("auto_connect_ok");
	xmlDoc->writeX(num,titre->text(),texte->toPlainText());
}

void EditImpl::on_buttonBox_rejected()
{
	
}



// A ranger ailleurs, just testing
/*
void EditImpl::on_lookup_clicked()
{
	QHostInfo::lookupHost(titre->text(),this, SLOT(lookup_result(QHostInfo)));
}*/

/*
void EditImpl::lookup_result(const QHostInfo &host)
{
	if (host.error() != QHostInfo::NoError)
	{
		//qDebug() << "Lookup failed:" << host.errorString();
		texte->setPlainText("Lookup failed");
		return;
	}
	
	//foreach (QHostAddress address, host.addresses())
	//qDebug() << "Found address:" << address.toString();
	texte->setPlainText(host.addresses().first().toString());
}*/

/*
void EditImpl::acc()
{
	//xmlDoc->writeX(2,"t","tt");
	//qDebug("accept\n\r");
	
}

void EditImpl::rej()
{
	//qDebug("cancel");
}
*/
