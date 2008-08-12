#include "FCxml.h"
//


FCxml::FCxml(QFile* file)
{
	loadFile(*file);
}

void FCxml::lireAll()
{
	// Lecture de tous le fichier xml et envoit un signal pour dire hop j'en ai un ! (envoyer le titre avec au lieu de lire?
	QStringList r;
	int i=1;
	
	while((r=lireX(i)).at(0)!="$Error")
	{
		emit newNode(r.at(0));
	}
}

bool FCxml::loadFile(QFile& file)
{
	// Ouverture  et chargement(lecture) du fichier
	if (!file.open(QIODevice::ReadWrite))
		return false;		// FIXME que faire quand lle fichier existe pas ou veut pas s ouvrir?
	if (!doc.setContent(&file))
	{
		file.close();
		return false;		// FIXME que faire quand le parssage ratte?
	}
	file.close();
	
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
			/*
			tab = item.childNodes();
			n = tab.item(j);
			//return n.firstChild().toText().data();
			*/
			
			ret << item.childNodes().item(0).firstChild().toText().data()  << item.childNodes().item(1).firstChild().toText().data(); // FIXME : y a pas plus simple Oo
			
			return ret;
		}
		noeud = noeud.nextSibling();
	}
	
	ret << "$Error";	
	
	return ret;
}

//
