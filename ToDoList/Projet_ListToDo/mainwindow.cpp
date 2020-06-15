#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){}
MainWindow::~MainWindow(){}
QString id_usr, Nom_usr, Prenom_usr, TachePonctuelle, TacheLongCours, realisationAddTache, update;
QFont maPolice ("Times", 12, QFont::Bold, true);
MaFenetre::MaFenetre(){
    // activer la connexion avec la base de donnes
    connexion_db(1);
    // Bloc 1 : Connexion_________________________________________________________________________________________________
    QGroupBox *groupConnexion = new QGroupBox("Connexion utilisateur");
        resize(900, 650);
        groupConnexion->setFont(maPolice);
        Connexion_login = new QLineEdit();
            Connexion_login->setPlaceholderText(" * * * * * * * * ");
            Connexion_login->setMaxLength(8);
        Connexion_pass_word = new QLineEdit();
            Connexion_pass_word->setPlaceholderText(" * * * * ");
            Connexion_pass_word->setMaxLength(4);
        // bouton de validation de champs de connexion
        QPushButton *bouton_connexion = new QPushButton("&Connexion !");
            bouton_connexion->setToolTip("Connecter");
            // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            QObject::connect(bouton_connexion, SIGNAL(clicked()), this, SLOT(connexion_usr()));
            //QObject::connect(bouton_connexion, SIGNAL(clicked()), this, SLOT(close())); // fermer cette fenetre
        QFormLayout *connexion = new QFormLayout; // formulaire de connexion
            connexion->addRow("&Nom Utilisateur :", Connexion_login);
            connexion->addRow("&Mot de passe :", Connexion_pass_word);
            connexion->addRow(" ", bouton_connexion);
        groupConnexion->setLayout(connexion);
    // Bloc 2: Inscription   _________________________________________________________________________________________
    groupIncription = new QGroupBox("Inscription");
        groupIncription->setFont(maPolice);
        // option d'activation du bloc
        groupIncription->setCheckable(true); // option d'activation du groupbox
        groupIncription->setChecked(false); // option de desactivation du groupbox
        // creation du formulaire layout pour ajouter les attributs
        QFormLayout *inscription_utilisateur = new QFormLayout;
            // definitioon de attributs
            inscription_Nom = new QLineEdit; /// AJOUTER UN VALEUR PAR DEFAULT
                inscription_Nom->setPlaceholderText("Max 45 caracteres");
                inscription_Nom->setMaxLength(45);
            inscription_Prenom = new QLineEdit;
                inscription_Prenom->setPlaceholderText("Max 45 caracteres");
                inscription_Prenom->setMaxLength(45);
            inscription_date_naissance = new QDateEdit;
                inscription_date_naissance->setDisplayFormat("yyyy-MM-dd");
            inscription_Emploi_Fonction = new QLineEdit;
                inscription_Emploi_Fonction->setPlaceholderText("Max 45 caracteres");
                inscription_Emploi_Fonction->setMaxLength(45);
            inscription_Date_Creation_Personne = new QDateEdit;
                inscription_Date_Creation_Personne->setDisplayFormat("yyyy-MM-dd");
                inscription_Date_Creation_Personne->setDate(QDate::currentDate()); // ajouter la date courant
            inscription_Adresse = new QLineEdit;
                inscription_Adresse->setMaxLength(100);
                inscription_Adresse->setPlaceholderText("Max 100 caracteres");
            inscription_Mail = new QLineEdit;
                inscription_Mail->setPlaceholderText("Max 45 caracteres");
                inscription_Mail->setMaxLength(45);
            inscription_Tel = new QLineEdit;
                inscription_Tel->setPlaceholderText("Max 12 caracteres");
                inscription_Tel->setMaxLength(12);
            inscription_Login = new QLineEdit;
                inscription_Login->setPlaceholderText("Max 8 caracteres");
                inscription_Login->setMaxLength(8);
            inscription_Mot_de_Passe = new QLineEdit;
                inscription_Mot_de_Passe->setPlaceholderText("Max 4 caracteres");
                inscription_Mot_de_Passe->setMaxLength(4);

            inscription_valider = new QPushButton("&Valider !");
                inscription_valider->setToolTip("Valider l'inscription");
                QObject::connect(inscription_valider, SIGNAL(clicked()), this, SLOT(validerInscription()));

            // affectation des variables dans le formulaire
            inscription_utilisateur->addRow("&Nom :", inscription_Nom);
            inscription_utilisateur->addRow("&Prenom :", inscription_Prenom);
            inscription_utilisateur->addRow("&Date de naissance :", inscription_date_naissance);
            inscription_utilisateur->addRow("&Emploi :", inscription_Emploi_Fonction);
            inscription_utilisateur->addRow("&Date de Creation utilisateur :", inscription_Date_Creation_Personne);
            inscription_utilisateur->addRow("&Adresse :", inscription_Adresse);
            inscription_utilisateur->addRow("&Mail :", inscription_Mail);
            inscription_utilisateur->addRow("&Tel :", inscription_Tel);
            inscription_utilisateur->addRow("&Login :", inscription_Login);
            inscription_utilisateur->addRow("&Mot de Passe :", inscription_Mot_de_Passe);
            inscription_utilisateur->addRow(" ",inscription_valider);
            groupIncription->setLayout(inscription_utilisateur);// affecter le formulaire dans le groupbox
            // requete sql insertion des données avec bouton insert %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        QPushButton *bouton_quitter_f1_1 = new QPushButton("&Quitter");
            bouton_quitter_f1_1->setToolTip("Quitter l'application");
            bouton_quitter_f1_1->setFont(maPolice);
            bouton_quitter_f1_1->setShortcut(QKeySequence("Ctrl+Q"));
            QObject::connect(bouton_quitter_f1_1, SIGNAL(clicked()), qApp, SLOT(quit()));


        // Bloc 3: Boutons : layout horizontale bouton quitter
        QHBoxLayout *LayoutQuitter = new QHBoxLayout;
            LayoutQuitter->setAlignment(Qt::AlignRight); // alignement de boutons a droit
            LayoutQuitter->addWidget(bouton_quitter_f1_1);
        // Définition du layout principal (vertical)
        QVBoxLayout *layoutPrincipal_1 = new QVBoxLayout;
            layoutPrincipal_1->addWidget(groupConnexion);
            layoutPrincipal_1->addWidget(groupIncription);
            layoutPrincipal_1->addLayout(LayoutQuitter);

        setLayout(layoutPrincipal_1);
        setWindowTitle("List TO DO");
        setWindowIcon(QIcon("im1.jpeg"));
   this->show();
}

void MaFenetre::connexion_usr(){
    qDebug() << Connexion_login->text()<< "    "<< Connexion_pass_word->text();
    QSqlQuery req_cnx;
    if(req_cnx.exec(" SELECT id , Nom, Prenom, Login , Mot_de_Passe FROM Personne ")){
        int cnx_bool = 0;
        while (req_cnx.next()){
            if( (req_cnx.value(3) == Connexion_login->text()) && (req_cnx.value(4) == Connexion_pass_word->text())){
                qDebug() << "id user"<< req_cnx.value(0).toString();
                id_usr = req_cnx.value(0).toString(); // Mise a jour de l'identifiant utilisateur
                Nom_usr = req_cnx.value(1).toString(); // Mise a jour de nom d'utilisateur
                Prenom_usr = req_cnx.value(2).toString(); // Mise a jour de prenom d'utilisateur
                this->close(); // Fermeture de la page d'acceuil
                //QMessageBox::information(this, "Connexion", );
                QMessageBox *msgCnx = new QMessageBox();
                    msgCnx->setText("<strong> Bonjour "+req_cnx.value(1).toString()+" "+req_cnx.value(2).toString()+"</strong>");
                    msgCnx->show();
                    QTimer::singleShot(2000, msgCnx, SLOT(hide()));// le message rest quelques secondes
                Fenetre2(); // ouverture de la page utiluisateur
                cnx_bool = 1;
            }
        }
        if(cnx_bool == 0){ QMessageBox::warning(this, "Erreur", "<strong> Veillez saisir un mot de passe et Login correct ! </strong>");} // Erreur de saisir de mot de passe ou de login
    }else{QMessageBox::warning(this, "Attention", "<strong>Erreur :</strong> Connexion base de bonnées échoué ");} // Erreur de connexion base de données
}
// evenement declenche pur l'insertion d'un nouveau utilisateur
void MaFenetre::validerInscription(){
    QMessageBox *msginscript = new QMessageBox();
        msginscript->setText("<strong>Insertion d'un nouvelle utilisateur</strong> \n Nom :"+ QString(inscription_Nom->text())+ " \n Prenom :"+ QString(inscription_Prenom->text())+ \
                    " \n Date de Naissance :"+ QString(inscription_date_naissance->text())+ " \n Emploi:"+ QString(inscription_Emploi_Fonction->text())+ \
                    " \n Date inscription:"+ QString(inscription_Date_Creation_Personne->text())+ " \n Adresse:"+ QString(inscription_Adresse->text())+ \
                    " \n MAil:"+ QString(inscription_Mail->text())+ " \n Tel:"+ QString(inscription_Tel->text())+ \
                    " \n Login:"+ QString(inscription_Login->text())+ " \n Mot de passe:"+ QString(inscription_Mot_de_Passe->text()));
        msginscript->show();
        QTimer::singleShot(3500, msginscript, SLOT(hide()));
    QSqlQuery req_inscription;
        req_inscription.prepare(" INSERT INTO Personne ( Nom , Prenom , Date_de_Naissance , Emploie , Date_Inscription , Adresse , Mail , Tel , Login , Mot_de_Passe ) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ");
        req_inscription.bindValue(0, inscription_Nom->text());
        req_inscription.bindValue(1, inscription_Prenom->text());
        req_inscription.bindValue(2, inscription_date_naissance->text());
        req_inscription.bindValue(3, inscription_Emploi_Fonction->text());
        req_inscription.bindValue(4, inscription_Date_Creation_Personne->text());
        req_inscription.bindValue(5, inscription_Adresse->text());
        req_inscription.bindValue(6, inscription_Mail->text());
        req_inscription.bindValue(7, inscription_Tel->text());
        req_inscription.bindValue(8 , inscription_Login->text());
        req_inscription.bindValue(9, inscription_Mot_de_Passe->text());
    if(req_inscription.exec()){
        // nettoyer les champs de d'inscription
        inscription_Nom->clear();
        inscription_Prenom->clear();
        inscription_date_naissance->clear();
        inscription_Emploi_Fonction->clear();
        inscription_Date_Creation_Personne->clear();
        inscription_Adresse->clear();
        inscription_Mail->clear();
        inscription_Tel->clear();
        inscription_Login->clear();
        inscription_Mot_de_Passe->clear();
        groupIncription->setChecked(false); // Desactiver la saisi dans le groupe box d'inscription
    }else{
        QMessageBox *msginscript_erreur = new QMessageBox();
            msginscript_erreur->setText(" Erreur de saisi, verifier le format de variable!");
            msginscript_erreur->show();
            QTimer::singleShot(2000, msginscript_erreur, SLOT(hide()));
    }
}



void MaFenetre::Fenetre2(){
    // Activer la connexion avec la base de données
    connexion_db(1);
    fenetre2 = new QWidget;
        fenetre2->setFont(maPolice);
        QTabWidget *onglets = new QTabWidget(fenetre2); // Création de QTabWidget pour qu'on peut creer dees fenetres
       //Page 1 : Liste des tach a faire & ajouter une tache __________________________________________________
        QWidget *page1 = new QWidget;
            // affichage des données
            Add_tache_Titre_Tache = new QLineEdit();
                Add_tache_Titre_Tache->setPlaceholderText(" Titre de tache ");
                Add_tache_Titre_Tache->setMaxLength(75);
            Add_tache_Classe_Categorie = new QComboBox();
                // selection des classes des taches a partir de tableau categories
                QSqlQueryModel *modelAdd_tache_Classe_Categorie = new QSqlQueryModel();
                    modelAdd_tache_Classe_Categorie->setQuery("SELECT Classe_Categorie FROM Categorie ");
                Add_tache_Classe_Categorie->clear();
                //Add_tache_Classe_Categorie->setEditable(true);
                Add_tache_Classe_Categorie->setModel(modelAdd_tache_Classe_Categorie);
            Add_tache_Tache_Ponctuelle = new QCheckBox("Tache ponctuel", this); // insertio 0 ou 1
            Add_tache_Tache_Long_cours = new QCheckBox("Tache long cours", this); // insertio 0 ou 1
            Add_tache_Description = new QLineEdit();
                Add_tache_Description->setFixedHeight(35);
                Add_tache_Description->setPlaceholderText(" Description ");
            Add_tache_Date_Echeance = new QDateEdit;
                Add_tache_Date_Echeance->setDate(QDate::currentDate());
                Add_tache_Date_Echeance->setDisplayFormat("yyyy-MM-dd");
            Add_tache_Realisation = new QCheckBox("Realisation", this); // insertion 0 ou 1
            QPushButton *validerTache = new QPushButton("&Valider"); // Validation de la tache
                validerTache->setToolTip("Ajouter une tache");
                validerTache->setFont(maPolice);
                validerTache->setShortcut(QKeySequence("Ctrl+V"));
                QObject::connect(validerTache, SIGNAL(clicked()), this, SLOT(Insert_NewTache()));
            //Chargement de tous les elements du groupe ajout tache
            QGroupBox *groupAjoutTache = new QGroupBox("Ajouter une tache ");
                QFormLayout *AjoutTache = new QFormLayout; // formulaire pour ajouter une nouvelle tache
                    QHBoxLayout *LH1 = new QHBoxLayout;
                        LH1->addWidget(Add_tache_Titre_Tache);
                        LH1->addWidget(Add_tache_Classe_Categorie);
                    AjoutTache->addRow("Titre et classe de tache:", LH1);
                       QHBoxLayout *LH2 = new QHBoxLayout;
                            LH2->addWidget(Add_tache_Date_Echeance);
                            LH2->addWidget(Add_tache_Tache_Ponctuelle);
                            LH2->addWidget(Add_tache_Tache_Long_cours);
                            LH2->addWidget(Add_tache_Realisation);
                       AjoutTache->addRow("Date d'echeance ", LH2);
                            AjoutTache->addRow(Add_tache_Description);
                            AjoutTache->addRow(validerTache);
                groupAjoutTache->setLayout(AjoutTache);

            // Vue de tableau de base de données
            QSqlRelationalTableModel *model_1 = new QSqlRelationalTableModel();  // QSqlRelationalDelegate, QSqlTableModel, QSqlRelationalTableModel, QSqlQueryModel
                model_1->setEditStrategy(QSqlTableModel::OnFieldChange); // (QSqlTableModel::OnManualSubmit) changer les donneés sans enregistrer
                //model0->setQuery("SELECT id , id_Personne , Titre_Tache , Categorie , Tache_Ponctuelle , Tache_Long_cours , Description , Date_Creation , Date_Echeance , Realisation FROM Taches WHERE (Date_Echeance > DATE(NOW())) and (Realisation = 0) " );
                model_1->setTable("Taches");
                model_1->setFilter("id_Personne ="+QString(id_usr));
                model_1->select();
                model_1->setHeaderData(0, Qt::Horizontal, "id");
                model_1->setHeaderData(1, Qt::Horizontal, "id_Personne");
                model_1->setHeaderData(2, Qt::Horizontal, "Titre_Tache");
                model_1->setHeaderData(3, Qt::Horizontal, "Categorie");
                model_1->setHeaderData(4, Qt::Horizontal, "Tache_Ponctuelle");
                model_1->setHeaderData(5, Qt::Horizontal, "Tache_Long_cours");
                model_1->setHeaderData(6, Qt::Horizontal, "Description");
                model_1->setHeaderData(7, Qt::Horizontal, "Date_Creation");
                model_1->setHeaderData(8, Qt::Horizontal, "Date_Echeance");
                model_1->setHeaderData(9, Qt::Horizontal, "Realisation");
            //%%**

            for (int i = 0; i < model_1->rowCount(); i++){
                if (model_1->record(i).value("Realisation").toInt() == 1){
                    QModelIndex index = model_1->index(i, 9);
                    qDebug()<<index.row();
                    model_1->setData(index, QVariant(QBrush (QColor(Qt::red))), Qt::BackgroundRole);
                    //table_view_1->setItemDelegateForRow(i, QStyledItemDelegate::paint(painter, option, index););
                }
            }
            model_1->submitAll();

            //%%**
            table_view_1 = new QTableView();
                table_view_1->setModel(model_1);
                table_view_1->setItemDelegate(new QSqlRelationalDelegate(table_view_1)); // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                table_view_1->setEditTriggers(QAbstractItemView::DoubleClicked); // L'édition commence apres double-cliqué , QAbstractItemView::NoEditTriggers ==> n'accepte pas les modifications
                table_view_1->sortByColumn(8, Qt::AscendingOrder); //DescendingOrder /// Tri selon la date d'echeance croissant
                table_view_1->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                table_view_1->setAlternatingRowColors(true);
                table_view_1->setSelectionBehavior(QAbstractItemView::SelectRows);
                table_view_1->setSelectionMode(QAbstractItemView::MultiSelection);
                /*
                QBrush yellow;
                yellow.setColor(Qt::red);
                for (int i = 0; i < model_1->rowCount(); i++){
                    if (model_1->record(i).value("Realisation").toInt() == 1){
                        QModelIndex index = model_1->index(i, 9);
                        //QModelIndex index = table_view_1->currentIndex();
                        table_view_1->model()->setData(index, yellow, Qt::ForegroundRole);
                        qDebug()<<index.row();
                    }
                }
                */
                //%%%%**SetItemForegroundColor
                //setItemDelegateForRow(5,  new TableStyleDelegate());
                //table_view_1->setItemDelegateForColumn(TaskFutureModel::COL_PROGRESS, new ProgressBarItemDelegate(ui->tableView));
            QGroupBox *groupTACHES_ToDo = new QGroupBox("Taches à faire");
                QFormLayout *TACHES_ToDo = new QFormLayout; // formulaire pour ajouter une nouvelle tache
                    TACHES_ToDo->addRow(table_view_1);
                groupTACHES_ToDo->setLayout(TACHES_ToDo);

            // groupe boutons
            // Bouton quitter a partir de la fernetre 2 pagfe 1
            QPushButton *bouton_quitter_f2_1 = new QPushButton("&Quitter");
                bouton_quitter_f2_1->setToolTip("Quitter l'application (Ctrl+Q)");
                bouton_quitter_f2_1->setFont(maPolice);
                bouton_quitter_f2_1->setShortcut(QKeySequence("Ctrl+Q"));
                QObject::connect(bouton_quitter_f2_1, SIGNAL(clicked()), qApp, SLOT(quit()));
            // Retour a la page d'acceuil %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            QPushButton *retour_page_connexion_f2_1 = new QPushButton("&Page d'acceuil");
                retour_page_connexion_f2_1->setToolTip("&Retour a la page d'acceuil ( Ctrl+P) ");
                retour_page_connexion_f2_1->setShortcut(QKeySequence("Ctrl+P"));
                connect(retour_page_connexion_f2_1, SIGNAL(clicked()), this, SLOT(Fenetre_Deconnexion())); // Deconnexion de la base de données & Message de sortie
                connect(retour_page_connexion_f2_1, SIGNAL(clicked()), fenetre2, SLOT(hide())); // Fermeture de la page actuel
                connect(retour_page_connexion_f2_1, SIGNAL(clicked()), this, SLOT(show())); // ouverture de la page d'acceuil
            // bouton actualiser de liste des taches
            QPushButton *actualiserTaches_f2_1 = new QPushButton("&Actualiser");
                 actualiserTaches_f2_1->setToolTip("&Retour a la page d'acceuil ( Ctrl+A) ");
                 actualiserTaches_f2_1->setShortcut(QKeySequence("Ctrl+A"));
                    connect(actualiserTaches_f2_1, SIGNAL(clicked()), this, SLOT(Actualiser_ListTaches()));


            QGridLayout *grid_groupBoutonsTACHESToDo = new QGridLayout();
                grid_groupBoutonsTACHESToDo->addWidget(bouton_quitter_f2_1, 0, 0);
                grid_groupBoutonsTACHESToDo->addWidget(retour_page_connexion_f2_1, 0, 2 );
                grid_groupBoutonsTACHESToDo->addWidget(actualiserTaches_f2_1, 0, 4 );

            QGroupBox *groupBoutonsTACHESToDo = new QGroupBox();
                groupBoutonsTACHESToDo->setLayout(grid_groupBoutonsTACHESToDo);
            // Layout principal (vertical)
           QGridLayout *layoutPrincipal_2 = new QGridLayout;
                layoutPrincipal_2->addWidget(groupAjoutTache);
                layoutPrincipal_2->addWidget(groupTACHES_ToDo);
                layoutPrincipal_2->addWidget(groupBoutonsTACHESToDo); // boutons quitter et retour a la page d'acceuil
        page1->setLayout(layoutPrincipal_2);

        // PAge 2 : ____________________________________________________________________________________________________
        QWidget *page2 = new QWidget;
            QTableView *table_view_2 = new QTableView(); // creation de view
                QSqlRelationalTableModel *model_2 = new QSqlRelationalTableModel();
                    model_2->setEditStrategy(QSqlTableModel::OnFieldChange);
                    model_2->setTable("Personne");
                    model_2->select();
                table_view_2->setModel(model_2);
                table_view_2->setEditTriggers(QAbstractItemView::DoubleClicked);
                table_view_2->sortByColumn(0, Qt::AscendingOrder); //DescendingOrder //Tri
                table_view_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                table_view_2->setAlternatingRowColors(true);
                table_view_2->setSelectionBehavior(QAbstractItemView::SelectRows);
                table_view_2->setSelectionMode(QAbstractItemView::SingleSelection);

            // group boutons
            QPushButton *bouton_quitter_f2_2 = new QPushButton("&Quitter");
                bouton_quitter_f2_2->setToolTip("Quitter l'application");
                bouton_quitter_f2_2->setFont(maPolice);
                bouton_quitter_f2_2->setShortcut(QKeySequence("Ctrl+Q"));
                QObject::connect(bouton_quitter_f2_2, SIGNAL(clicked()), qApp, SLOT(quit()));
            // Retour a la page d'acceuil    _________________________________________%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            QPushButton *retour_page_connexion_f2_2 = new QPushButton("&Page d'acceuil");
                retour_page_connexion_f2_2->setToolTip("&Retour a la page d'acceuil");
                retour_page_connexion_f2_2->setShortcut(QKeySequence("Ctrl+P"));
                connect(retour_page_connexion_f2_2, SIGNAL(clicked()), this, SLOT(Fenetre_Deconnexion())); // Deconnexion de la base de données & Message de sortie
                connect(retour_page_connexion_f2_2, SIGNAL(clicked()), fenetre2, SLOT(hide())); // Fermeture de la page actuel
                connect(retour_page_connexion_f2_2, SIGNAL(clicked()), this, SLOT(show())); // ouverture de la page d'acceuil

            QGridLayout *BoutonsF2P2 = new QGridLayout;
                BoutonsF2P2->addWidget(bouton_quitter_f2_2, 0, 0);
                BoutonsF2P2->addWidget(retour_page_connexion_f2_2, 0, 2 );
            QGroupBox *groupBoxBoutonsF2P2 = new QGroupBox();
                groupBoxBoutonsF2P2->setLayout(BoutonsF2P2);
            QGridLayout *Gbox_Page2 = new QGridLayout;
                Gbox_Page2->addWidget(table_view_2, 0, 0);
                Gbox_Page2->addWidget(groupBoxBoutonsF2P2);
            page2->setLayout(Gbox_Page2);
        // Page 3 : Taches deja fait ou histourique des taches  __________________________________________________________
        QWidget *page3 = new QWidget;
            // Vue de tableau des taches deja fait
            QSqlTableModel *model_3 = new QSqlTableModel();
                model_3->setEditStrategy(QSqlTableModel::OnFieldChange);
                model_3->setTable("Taches");
                // jointure pour ajouter le nom de la personne    %%%%%%%%%%%%%
                model_3->setFilter("id_Personne ="+QString(id_usr)+" and Realisation = 1");
                model_3->select();
            QTableView *table_view_3 = new QTableView();
                table_view_3->setModel(model_3);
                table_view_3->setItemDelegate(new QSqlRelationalDelegate(table_view_3));
                table_view_3->setEditTriggers(QAbstractItemView::DoubleClicked);
                table_view_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                table_view_3->setAlternatingRowColors(true);
                table_view_3->setSelectionBehavior(QAbstractItemView::SelectRows);
                table_view_3->setSelectionMode(QAbstractItemView::SingleSelection);

                //table_view_3->sortByColumn(8, Qt::AscendingOrder);
            QGroupBox *groupTachesDejaFait = new QGroupBox("Taches deja fait");
                QFormLayout *TachesDejaFait = new QFormLayout; // formulaire pour ajouter une nouvelle tache
                    TachesDejaFait->addRow(table_view_3);
                groupTachesDejaFait->setLayout(TachesDejaFait);
             // boutons page 3
            QPushButton *bouton_quitter_f2_3 = new QPushButton("&Quitter");
                bouton_quitter_f2_3->setToolTip("Quitter l'application");
                bouton_quitter_f2_3->setFont(maPolice);
                bouton_quitter_f2_3->setShortcut(QKeySequence("Ctrl+Q"));
                QObject::connect(bouton_quitter_f2_3, SIGNAL(clicked()), qApp, SLOT(quit()));
            // Bouton retour a la page de connexion           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            QPushButton *retour_page_connexion_f2_3 = new QPushButton("&Page d'acceuil");
                retour_page_connexion_f2_3->setToolTip("&Retour a la page d'acceuil");
                retour_page_connexion_f2_3->setShortcut(QKeySequence("Ctrl+P"));
                connect(retour_page_connexion_f2_3, SIGNAL(clicked()), this, SLOT(Fenetre_Deconnexion())); // Deconnexion de la base de données & Message de sortie
                connect(retour_page_connexion_f2_3, SIGNAL(clicked()), fenetre2, SLOT(hide())); // Fermeture de la page actuel
                connect(retour_page_connexion_f2_3, SIGNAL(clicked()), this, SLOT(show())); // ouverture de la page d'acceuil
            QGridLayout *BoutonsF2P3 = new QGridLayout;
                BoutonsF2P3->addWidget(bouton_quitter_f2_3, 0, 0);
                BoutonsF2P3->addWidget(retour_page_connexion_f2_3, 0, 2 );
            QGroupBox *groupBoxBoutonsF2P3 = new QGroupBox();
                 groupBoxBoutonsF2P3->setLayout(BoutonsF2P3);
        // Layout principal (vertical)
        QGridLayout *layoutPrincipal_3 = new QGridLayout;
            layoutPrincipal_3->addWidget(groupTachesDejaFait);
            layoutPrincipal_3->addWidget(groupBoxBoutonsF2P3);
        page3->setLayout(layoutPrincipal_3);

    // Page 4 : Categories ____________________________________________________________________________________
        QWidget *page4 = new QWidget;
            QSqlTableModel *model_4 = new QSqlTableModel();//QSqlRelationalTableModel();
                model_4->setEditStrategy(QSqlTableModel::OnFieldChange);
                model_4->setTable("Categorie");
                model_4->select();
            table_view_4 = new QTableView();
                table_view_4->setModel(model_4);
                table_view_4->setItemDelegate(new QSqlRelationalDelegate(table_view_4));
                table_view_4->setEditTriggers(QAbstractItemView::DoubleClicked);
                table_view_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                table_view_4->setAlternatingRowColors(true);
                table_view_4->setSelectionBehavior(QAbstractItemView::SelectRows);
                table_view_4->setSelectionMode(QAbstractItemView::SingleSelection);
             // boutons page 4
            QPushButton *bouton_quitter_f2_4 = new QPushButton("&Quitter");
                bouton_quitter_f2_4->setToolTip("Quitter l'application");
                bouton_quitter_f2_4->setFont(maPolice);
                bouton_quitter_f2_4->setShortcut(QKeySequence("Ctrl+Q"));
                QObject::connect(bouton_quitter_f2_4, SIGNAL(clicked()), qApp, SLOT(quit()));
            // Bouton retour a la page de connexion %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            QPushButton *retour_page_connexion_f2_4 = new QPushButton("&Page d'acceuil");
                retour_page_connexion_f2_4->setToolTip("&Retour a la page d'acceuil");
                retour_page_connexion_f2_4->setShortcut(QKeySequence("Ctrl+P"));
                connect(retour_page_connexion_f2_4, SIGNAL(clicked()), this, SLOT(Fenetre_Deconnexion())); // Deconnexion de la base de données & Message de sortie
                connect(retour_page_connexion_f2_4, SIGNAL(clicked()), fenetre2, SLOT(hide())); // Fermeture de la page actuel
                connect(retour_page_connexion_f2_4, SIGNAL(clicked()), this, SLOT(show())); // ouverture de la page d'acceuil

            QPushButton *bouton_AddCategorie = new QPushButton("&Ajouter");
                bouton_AddCategorie->setToolTip("Ajouter une nouvelle categorie (Ctrl+A)");
                bouton_AddCategorie->setFont(maPolice);
                bouton_AddCategorie->setShortcut(QKeySequence("Ctrl+A"));
                QObject::connect(bouton_AddCategorie, SIGNAL(clicked()), this, SLOT(AddCategorie()));
            QGridLayout *BoutonsF2P4 = new QGridLayout;
                BoutonsF2P4->addWidget(bouton_quitter_f2_4, 0, 0);
                BoutonsF2P4->addWidget(retour_page_connexion_f2_4, 0, 2 );
                BoutonsF2P4->addWidget(bouton_AddCategorie, 0, 4 );

            QGroupBox *groupBoxBoutonsF2P4 = new QGroupBox();
                 groupBoxBoutonsF2P4->setLayout(BoutonsF2P4);
        // Layout principal (vertical)
        QGridLayout *layoutPrincipal_4 = new QGridLayout;
            layoutPrincipal_4->addWidget(table_view_4);
            layoutPrincipal_4->addWidget(groupBoxBoutonsF2P4);
        page4->setLayout(layoutPrincipal_4);
    // ajout des pages dans la fenetre principal ____________________________________________________________
    onglets->addTab(page1, "Taches a faire");
    if(id_usr == '1'){ // s'ouvre seulement pour l'utilisateur numero 1
        onglets->addTab(page2, "Utilisateurs");
    }
    onglets->addTab(page3, "Taches deja fait");
    onglets->addTab(page4, "Categorie");

    QVBoxLayout *vbox = new QVBoxLayout; // creation de layout vertical
        vbox->addWidget(onglets);
    fenetre2->setLayout(vbox);
    fenetre2->setWindowTitle("List TO DO");
    fenetre2->setWindowIcon(QIcon("im1.jpeg"));
    //fenetre2->resize(900, 650);
    fenetre2->show();
}
void MaFenetre::Fenetre_Deconnexion(){
    connexion_db(0);
    id_usr = '0';
    QMessageBox *msgRetour = new QMessageBox();
        msgRetour->setText("<strong> Déconnexion Veillez reconnecter </strong>");
        msgRetour->show();
    QTimer::singleShot(2500, msgRetour, SLOT(hide()));
}
int MaFenetre::connexion_db(int i){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("BDD_ListToDo");
        db.setUserName("phpmyadmin");
        db.setPassword("0000");
    if((i == 1) &&(!db.open())){
        db.open();
    }
    if(i == 0){
        db.open();
    }
    return 0;
}
void MaFenetre::Insert_NewTache(){
    if (Add_tache_Tache_Ponctuelle->isChecked()){
        TachePonctuelle = '1';
    }
    else{
        TachePonctuelle = '0';
    }
    if (Add_tache_Tache_Long_cours->isChecked()){
        TacheLongCours = '1';
    }
    else{
        TacheLongCours = '0';
    }
    if (Add_tache_Realisation->isChecked()){
        realisationAddTache = '1';
    }
    else{
        realisationAddTache = '0';
    }
    QMessageBox *msgAddTache = new QMessageBox();
        msgAddTache->setText("<strong> Ajout d'une nouvelle Tache </strong> ( \
                                 id = " + QString(id_usr) \
                             +", Nom = " + QString(Nom_usr) \
                             +", Prenom = " + QString(Prenom_usr) \
                             +", Titre Tache = " + QString(Add_tache_Titre_Tache->text()) \
                             +", Categorie = " + QString(Add_tache_Classe_Categorie->currentText()) \
                             +", Tache pnctuelle = " + QString(TachePonctuelle) \
                             +", Tache Long cours = " + QString(TacheLongCours) \
                             +", Description = " + QString(Add_tache_Description->text()) \
                             +", Date d'Echeance = " + QString(Add_tache_Date_Echeance->text()) \
                             +", Realisation = " + QString(realisationAddTache) + " )" );
        msgAddTache->show();
        QTimer::singleShot(3000, msgAddTache, SLOT(hide()));
    QSqlQuery req_addTache;
        req_addTache.prepare(" INSERT INTO Taches ( id_Personne , Titre_Tache , Categorie , Tache_Ponctuelle , Tache_Long_cours , Description , Date_Creation , Date_Echeance , Realisation ) VALUES ( ? , ? , ? , ? , ? , ? , ? , ? , ? ) ");
        req_addTache.bindValue(0, id_usr);
        req_addTache.bindValue(1, Add_tache_Titre_Tache->text());
        req_addTache.bindValue(2, Add_tache_Classe_Categorie->currentText());
        req_addTache.bindValue(3, TachePonctuelle);
        req_addTache.bindValue(4, TacheLongCours);
        req_addTache.bindValue(5, Add_tache_Description->text());//toPlainText());
        QDateEdit *dateNow = new QDateEdit; // date de creation de la tache == date courant
            dateNow->setDisplayFormat("yyyy-MM-dd");
            dateNow->setDate(QDate::currentDate());
        req_addTache.bindValue(6, dateNow->text());
        req_addTache.bindValue(7, Add_tache_Date_Echeance->text());
        req_addTache.bindValue(8, realisationAddTache);
    if(req_addTache.exec()){
        Add_tache_Titre_Tache->clear();
        Add_tache_Classe_Categorie->clear();
        if (Add_tache_Tache_Ponctuelle->isChecked()){
            Add_tache_Tache_Ponctuelle->setChecked(false);
        }
        if (Add_tache_Tache_Long_cours->isChecked()){
            Add_tache_Tache_Long_cours->setChecked(false);
        }
        Add_tache_Description->clear();
        dateNow->clear();
        if (Add_tache_Realisation->isChecked()){
            Add_tache_Realisation->setChecked(false);
        }
        // mise a jour du tableau taches
        QSqlRelationalTableModel *model = new QSqlRelationalTableModel();
            model->setEditStrategy(QSqlTableModel::OnFieldChange);
            model->setTable("Taches");
            model->setFilter("id_Personne ="+QString(id_usr));
            model->select();
            model->setHeaderData(0, Qt::Horizontal, "id");
            model->setHeaderData(1, Qt::Horizontal, "id_Personne");
            model->setHeaderData(2, Qt::Horizontal, "Titre_Tache");
            model->setHeaderData(3, Qt::Horizontal, "Categorie");
            model->setHeaderData(4, Qt::Horizontal, "Tache_Ponctuelle");
            model->setHeaderData(5, Qt::Horizontal, "Tache_Long_cours");
            model->setHeaderData(6, Qt::Horizontal, "Description");
            model->setHeaderData(7, Qt::Horizontal, "Date_Creation");
            model->setHeaderData(8, Qt::Horizontal, "Date_Echeance");
            model->setHeaderData(9, Qt::Horizontal, "Realisation");
        table_view_1->setModel(model);
    }
    else{
        QMessageBox *msgaddtache_erreur = new QMessageBox();
            msgaddtache_erreur->setText(" Erreur de saisi, verifier le format de variable!");
            msgaddtache_erreur->show();
            QTimer::singleShot(3000, msgaddtache_erreur, SLOT(hide()));
        }
}
void MaFenetre::AddCategorie(){
    QWidget *pageAddCategorie = new QWidget();
        // Ajouter une nouvelle categorie
        nomCathgorie = new QLineEdit();
            nomCathgorie->setPlaceholderText(" Titre de tache ");
            nomCathgorie->setMaxLength(75);
        // Bouton de validation
        QPushButton *validerAddCategorie = new QPushButton("&Valider"); // Validation de la tache
            validerAddCategorie->setToolTip("Valider l'ajout d'une nouvelle categorie");
            validerAddCategorie->setFont(maPolice);
            validerAddCategorie->setShortcut(QKeySequence("Ctrl+V"));
            QObject::connect(validerAddCategorie, SIGNAL(clicked()), this, SLOT(Insert_NewCategorie()));
            QObject::connect(validerAddCategorie, SIGNAL(clicked()), pageAddCategorie, SLOT(close()));
            //QObject::connect(validerAddCategorie, SIGNAL(clicked()), Fenetre2, SLOT(hide()));
            //QObject::connect(validerAddCategorie, SIGNAL(clicked()), this, SLOT(Fenetre2()));
            // Chargement de tous les elements
        QFormLayout *AjoutCategorie = new QFormLayout; // formulaire pour ajouter une nouvelle tache
            QHBoxLayout *LVAjoutCategorie = new QHBoxLayout;
                LVAjoutCategorie->addWidget(nomCathgorie);
                LVAjoutCategorie->addWidget(validerAddCategorie);
            AjoutCategorie->addRow("Ajouter une nouvelle Categorie :", LVAjoutCategorie);
        pageAddCategorie->setLayout(AjoutCategorie);
        pageAddCategorie->show();
}

void MaFenetre::Insert_NewCategorie(){
    QMessageBox *msgAddTache = new QMessageBox();
        msgAddTache->setText("<strong> Nouvelle Categorie ajouté </strong> \n Nom Catgorie = "+QString(nomCathgorie->text()));
        msgAddTache->show();
        QTimer::singleShot(3000, msgAddTache, SLOT(hide()));
    QSqlQuery req_addCategorie;
        req_addCategorie.prepare(" INSERT INTO Categorie ( Classe_Categorie ) VALUES ( ? ) ");
        req_addCategorie.bindValue(0, nomCathgorie->text());
    if(req_addCategorie.exec()){
        nomCathgorie->clear(); // Vider le formulaire
        // mettre a jour trableau Categorie
        QSqlTableModel *model = new QSqlTableModel();
            model->setEditStrategy(QSqlTableModel::OnFieldChange);
            model->setTable("Categorie");
            model->select();
        table_view_4->setModel(model);
    }
    else{
        QMessageBox *msgaddCategorie_erreur = new QMessageBox();
            msgaddCategorie_erreur->setText(" Erreur de saisi, verifier le format de variable ou la connexion avec la base de données !");
            msgaddCategorie_erreur->show();
            QTimer::singleShot(3000, msgaddCategorie_erreur, SLOT(hide()));
        }
}
// bouton d'actualisation de la vue des données de taches a faire
void MaFenetre::Actualiser_ListTaches(){
    QSqlRelationalTableModel *model5 = new QSqlRelationalTableModel();
        model5->setEditStrategy(QSqlTableModel::OnFieldChange);
        model5->setTable("Taches");
        model5->setFilter("id_Personne ="+QString(id_usr));
        model5->select();
        model5->setHeaderData(0, Qt::Horizontal, "id");
        model5->setHeaderData(1, Qt::Horizontal, "id_Personne");
        model5->setHeaderData(2, Qt::Horizontal, "Titre_Tache");
        model5->setHeaderData(3, Qt::Horizontal, "Categorie");
        model5->setHeaderData(4, Qt::Horizontal, "Tache_Ponctuelle");
        model5->setHeaderData(5, Qt::Horizontal, "Tache_Long_cours");
        model5->setHeaderData(6, Qt::Horizontal, "Description");
        model5->setHeaderData(7, Qt::Horizontal, "Date_Creation");
        model5->setHeaderData(8, Qt::Horizontal, "Date_Echeance");
        model5->setHeaderData(9, Qt::Horizontal, "Realisation");
    table_view_1->setModel(model5);
}

