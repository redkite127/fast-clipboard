#include "NetworksXml.h"

#include <QDebug>
//
NetworksXML::NetworksXML(QHostAddress h)
{
	IP = h;
	balise="";
	//qDebug() << "debut "<< IP.toString()<< endl;
}

bool NetworksXML::startDocument ()
{
  return true;        //pas traité ici
}

bool NetworksXML::startElement ( const QString & , const QString & , const QString & qName, const QXmlAttributes &)
{
	if(qName=="item")
	{
		balise_item = "item";              //drapeau "item" pour mémorisation
	}
	else
		if (qName=="TeamName" || qName=="IP" || qName=="Mask" || qName=="SubnetMask")
			balise=qName;
		else
			balise=" ";
		
	return true;
}

bool NetworksXML::fatalError (const QXmlParseException &)
{
	qDebug() << "fatalERROR" << endl;
	return false;           //pas traité ici
}

bool NetworksXML::characters ( const QString & ch)
{
	if (balise_item=="item" && !ch.isEmpty())           //test du drapeau "item"
	{
		if(balise=="TeamName")       //test des autres drapeaux
		{
			teamName = ch;
			//qDebug() << "TT" << teamName << endl;
		}
		if(balise=="IP")
			networkAddress.setIp(QHostAddress(ch));
		if(balise=="SubnetMask")
			networkAddress.setNetmask(QHostAddress(ch));
		if(balise == "Mask")
		{
			shortMask=ch.toInt();
		}
	}
	
	return true;
}

bool NetworksXML::endDocument ()
{
	networkAddress.setIp(QHostAddress(""));
	teamName = "";
	shortMask = 0;
	
	return true;
}

bool NetworksXML::endElement ( const QString & namespaceURI, const QString &localName, const QString & qName )
{
	QString s1,s2;
	
	s1 = namespaceURI;
	s2 = localName;
	
	balise="";
		
	if (qName=="item")
	{
		balise_item="";//réinitialisation des balises
		balise="";
		
		// Verifier si ce net-id peut convenir à l'adresse IP passé en paramètre du constructeur...
		//qDebug("found\n");
		//qDebug() << "BB" << teamName << endl;
		
		if( ( (IP.toIPv4Address()) & networkAddress.netmask().toIPv4Address() )==networkAddress.ip().toIPv4Address() )
			return false; // Pour Quitter puisqu'on a trouvé le bon
			//qDebug() << "cc"<<teamName << endl;
	}
	return true;
}

QNetworkAddressEntry NetworksXML::getNetworkAddress()
{
	return networkAddress;
}

QString NetworksXML::getTeamName()
{
	return teamName;
}

int NetworksXML::getShortMask()
{
	return shortMask;
}
//
