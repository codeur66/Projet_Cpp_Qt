#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTableWidget>
#include <QtGui>
#include <QThread>
#include <QtSql>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriverPlugin>
#include <QSqlRelationalDelegate>

#include <iostream>
#include <fstream>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QtWidgets>
#include <QFont>
#include <QIcon>
#include <iostream>
#include <iterator>
#include <QProgressBar>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QStackedLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QString>
#include <QSpinBox>
#include <QLabel>
#include<string>

#include <QItemDelegate>

class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
};
class MaFenetre : public QWidget{  /// On hérite de QWidget (IMPORTANT)
    Q_OBJECT
    public:
        MaFenetre();
        int connexion_db(int i);
        QLineEdit *Connexion_login;
        QLineEdit *Connexion_pass_word;
        QPushButton *retour_page_connexion;
        QLineEdit *inscription_Nom;
        QLineEdit *inscription_Prenom;
        QDateEdit *inscription_date_naissance;
        QLineEdit *inscription_Emploi_Fonction;
        QDateEdit *inscription_Date_Creation_Personne;
        QLineEdit *inscription_Adresse;
        QLineEdit *inscription_Mail;
        QLineEdit *inscription_Tel;
        QLineEdit *inscription_Login;
        QLineEdit *inscription_Mot_de_Passe;
        QPushButton *inscription_valider;
        QGroupBox *groupIncription;
        QLineEdit *Add_tache_Titre_Tache;
        QCheckBox *Add_tache_Tache_Ponctuelle;
        QCheckBox *Add_tache_Tache_Long_cours;
        QLineEdit *Add_tache_Description;
        QDateEdit *Add_tache_Date_Echeance;
        QCheckBox *Add_tache_Realisation;
        QComboBox *Add_tache_Classe_Categorie;
        QLineEdit *nomCathgorie;
        QTableView *table_view_1;
        QTableView *table_view_4;
        QWidget *fenetre2;

    signals:
        void signal_cnx(int i = 1);
    public slots:
        void Fenetre2();
        void connexion_usr();
        void Fenetre_Deconnexion();
        void validerInscription();
        void AddCategorie();
        void Insert_NewTache();
        void Insert_NewCategorie();
        void Actualiser_ListTaches();



};
//void page1();
//class connexion_db(){}

#endif // MAINWINDOW_H
