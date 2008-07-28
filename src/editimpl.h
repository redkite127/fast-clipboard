#ifndef EDITIMPL_H
#define EDITIMPL_H
//
#include <QDialog>
#include "ui_edit.h"
//

//Le fichier change pas à chaque fois, trouver comment le mettre en "global"? ou pas ?... car c du gaspillage de passer ça en parametre tt le tps

//Séparer la lecture de l'XML dans une autre classe, garder l XML en  mémoire et passer un ptr vers le texte à Edit?
// Le lire dans le main. avoir un objet gglobale? representant le XML

class EditImpl : public QDialog, public Ui::Edit
{
	Q_OBJECT

public:
	EditImpl(int n, QWidget * parent = 0, Qt::WFlags f = 0 );

private:
	int num;
	
};
#endif
