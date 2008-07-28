#include "mainwindowimpl.h"
//
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
	setupUi(this);
	
	this->nombre = 5;

	// Quitter le programme par le menu
	connect(action_Quitter,SIGNAL(triggered()),this,SLOT(close()));
	
	// Création du signalMapper et connection de son signal mapped au slot désiré : http://doc.trolltech.com/qq/qq10-signalmapper.html
	signalMapper = new QSignalMapper(this);
	connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(editerX(int)));
	signalMapper2 = new QSignalMapper(this);
	connect(signalMapper2,SIGNAL(mapped(int)),this,SLOT(copierX(int)));
	
	 /*
	 /
	 / Création d'un certain nombre de ligne et connection au signal mapper
	 /
	*/

	// Récupération du layout central de la fenètre
	QLayout *cLayout = this->centralWidget()->layout();
	
	for(int i=1; i<=nombre; i++)
	{
		QHBoxLayout *hLayout = new QHBoxLayout();
		QPushButton *button1 = new QPushButton(lire(i,0),centralwidget);
		
		QPushButton *button2 = new QPushButton(QIcon(":/images/icon/pencil.png"),QString(""),centralwidget);
		button2->setMaximumWidth(32);
		button2->setIconSize(QSize(22,22));
		
		hLayout->addWidget(button1);
		hLayout->addWidget(button2);
		
		cLayout->addItem(hLayout);
		
		// Indication du mapping à faire (correspondance objet, information)
		signalMapper2->setMapping(button1,i);
		signalMapper->setMapping(button2, i);
		
		// Lie clicked au mapper
		connect(button1, SIGNAL(clicked()), signalMapper2, SLOT(map()));
		connect(button2, SIGNAL(clicked()), signalMapper, SLOT(map()));
		
	}
	
	((QBoxLayout*)cLayout)->addStretch();

}

void MainWindowImpl::editerX(int i)
{
	EditImpl *e = new EditImpl(i ,this);
	
	///Bordel XML, c le constucteur de editerX qui doit aller lire !
	e->titre->setText(lire(i,0));
	e->texte->insertPlainText(lire(i,1));
	////////

	e->show();	
}

void MainWindowImpl::copierX(int i)
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(lire(i,1));
}

// Refaire ...
QString MainWindowImpl::lire(int i, int j)			// i pour la ligne, j pour titre ou texte 0=titre 1=texte
{
	
	///////////////////////////////////////////
	// Bordel de lecture XML ... a réaranger vite fait pour que ça marche
	QFile file("pp2DB.xml");
	if (!file.open(QIODevice::ReadOnly))
		return "Error";
	if (!doc.setContent(&file))
	{
		file.close();
		return "Error";
	}
	file.close();
	

	QDomNodeList tab;
	QDomElement item;
	QDomNode n;
	QDomElement racine = doc.documentElement();	//renvoie la balise racine
	QDomNode noeud = racine.firstChild();	//renvoie la 1ere balise, icifast-clipboard
	///////////////////1ere fin bordel XML

		///////////// suite bordel XML  :
		
		
		while(!noeud.isNull())
		{
			item = noeud.toElement();
			if(item.tagName()=="item"  && item.attribute("num")==QString("%1").arg(i))
			{
				tab = item.childNodes();
				n = tab.item(j);
				return n.firstChild().toText().data();
			}
			noeud = noeud.nextSibling();
		}
		//////////////// derniere fin bordel XML
		
		return "Error";
}


void MainWindowImpl::on_actionPlus_triggered()
{
/*	
	// Récupération du layout central de la fenètre
	QLayout *cLayout = this->centralWidget()->layout();	
	
	QHBoxLayout *hLayout = new QHBoxLayout();
	QPushButton *button1 = new QPushButton(QString("Titre"),centralwidget);
	
	QPushButton *button2 = new QPushButton(QIcon(":/images/icon/pencil.png"),QString(""),centralwidget);
	button2->setMaximumWidth(32);
	button2->setIconSize(QSize(22,22));
	
	hLayout->addWidget(button1);
	hLayout->addWidget(button2);
	
	((QBoxLayout*)cLayout)->insertLayout(2,hLayout);
	
	// Indication du mapping à faire (correspondance objet, information)
	signalMapper->setMapping(button2, 9);
	
	// Lie clicked au mapper
	connect(button2, SIGNAL(clicked()), signalMapper, SLOT(map()));
	
	
	cLayout->update();
	*/
}

//
