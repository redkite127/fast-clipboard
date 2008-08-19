#include "FCxml.h"
#include <QTextStream>
#include <QFile>

#include <QDebug>
//


FCxml::FCxml(QFile *file)
{
	loadFile(file);
}

void FCxml::lireAll()
{
	// Lecture de tous le fichier xml et envoit un signal pour dire hop j'en ai un ! (envoyer le titre avec au lieu de lire?
	QStringList r;
	int i=1;
	//qDebug("Debut de lire all");
	while((r=lireX(i)).at(0)!="$Error")
	{
		emit newNode(r.at(0));
		i++;
	}
}

bool FCxml::loadFile(QFile *file)
{
	qDebug("Loading xml file ...");
	// Ouverture  et chargement(lecture) du fichier
	if (!file->open(QIODevice::ReadWrite))
	{
		qDebug("open didn't succeed");
		return false;		// FIXME que faire quand lle fichier existe pas ou veut pas s ouvrir?
	}
		
	if (!doc.setContent(file))
	{
		qDebug("setContent returned false");
		file->close();
		return false;		// FIXME que faire quand le parssage ratte?
	}
	file->close();
	qDebug("ok");
	return true;
}

QStringList FCxml::lireX(int i)
{
	int j=0;
	QStringList ret;
	QDomNodeList tab;
	QDomElement item;
	QDomNode n;
	QDomElement racine = doc.documentElement();	//renvoie la balise racine
	QDomNode noeud = racine.firstChild();	//renvoie la 1ere balise, ici fast-clipboard


	while(!noeud.isNull() && j<i)
	{
		item = noeud.toElement();
		if(item.tagName()=="item" && ++j==i)	// Comme ça on ne compte que le nombre d item
		{
			// FIXME au lieu de dire je prend le 0 puis le 1 ça serait mieux de prendre balise titre puis balise texte 
			ret << item.childNodes().item(0).firstChild().toText().data()  << item.childNodes().item(1).firstChild().toText().data(); // FIXME : y a pas plus simple Oo
			
			return ret;
		}
		noeud = noeud.nextSibling();
	}
	
	ret << "$Error";	// Mouais...	
	
	return ret;
}

void FCxml::writeX(int i,QString titre,QString texte)
{
	int j=0;
	QDomElement item, racine = doc.documentElement();	//renvoie la balise racine
	QDomNode noeud = racine.firstChild();	//renvoie la 1ere balise, ici fast-clipboard
	
	while(!noeud.isNull() && j<i)
	{
		item = noeud.toElement();
		if(item.tagName()=="item" && ++j==i)	// Comme ça on ne compte que le nombre d item
		{
			//item.childNodes().item(0).toElement().text() = titre;
		//item.childNodes().item(1).toElement().text() = texte;
			
			QDomText f1;
			f1.setData(QString("coucou"));
			item.childNodes().item(1).toElement().appendChild(f1);

		}
		
		noeud = noeud.nextSibling();
	}
	
	return;
}

int FCxml::addNode(QString titre,QString texte)
{
	  
	QDomElement item = doc.createElement("item");
	QDomElement title = doc.createElement("titre");
	QDomElement text = doc.createElement("texte");
	
	text.appendChild(doc.createTextNode(texte));
	title.appendChild(doc.createTextNode(titre));

	item.appendChild(title);
	item.appendChild(text);
	
	doc.documentElement().appendChild(item);
	
	//Ajout d'une ligne avec les boutons :
	emit newNode(titre);

	save();

	return 0;
}

void FCxml::save()
{
	QFile file( "pp2DB.xml" );
	if( !file.open( QIODevice::WriteOnly ) )
		return;



	QTextStream ts(&file);
//	ts << doc.toString(4);
	doc.save(ts,4);
	file.close();
	
	return;
}

//
