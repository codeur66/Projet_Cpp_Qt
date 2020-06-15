#include "mainwindow.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MaFenetre w;
    w.show();
    return a.exec();
}
/*iurhgiuorheogjhtrou*/
/*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("DB_TP1");
    db.setUserName("phpmyadmin");
    db.setPassword("0000");
    qDebug() << db.open();

    QSqlQuery sql_query;
    if(sql_query.exec("SELECT Reference_Personne , Nom , Prenom , Date_de_Naissance , Emploi_Fonction , Date_Creation_Personne , Adresse , Mail , Tel , Login , Mot_de_Passe FROM Personne ")){
        qDebug()<< sql_query.size();
       //QList<int> id_list;
        while (sql_query.next()){
            int Reference_Personne = sql_query.value(0).toInt();
            QString Nom = sql_query.value(1).toString();
            QString Prenom = sql_query.value(2).toString();
            QDate Date_de_Naissance = sql_query.value(3).toDate();
            QString Emploi_Fonction = sql_query.value(4).toString();
            QDate Date_Creation_Personne = sql_query.value(5).toDate();
            QString Adresse = sql_query.value(6).toString();
            QString Mail = sql_query.value(7).toString();
            int Tel = sql_query.value(8).toInt();
            QString Login = sql_query.value(9).toString();
            int Mot_de_Passe = sql_query.value(10).toInt();
            qDebug() <<Reference_Personne<<" "<<Nom<<" "<<Prenom<<" "<<Date_de_Naissance\
                     <<" "<<Emploi_Fonction<<" "<<Date_Creation_Personne<<" "<<Adresse<<" "\
                     <<Mail<<" "<<Tel<<" "<<Login<<" "<< Mot_de_Passe;
        }
    }

    QSqlQueryModel *model = new QSqlQueryModel;//QSqlRelationalTableModel();
    model->setQuery("SELECT Reference_Personne , Nom , Prenom , Date_de_Naissance , Emploi_Fonction , Date_Creation_Personne , Adresse , Mail , Tel , Login , Mot_de_Passe FROM Personne ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Reference_Personne"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_de_Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Emploi_Fonction"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date_Creation_Personne"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Tel"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Login"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Mot_de_Passe"));
    QTableView *view = new QTableView;
        view->setModel(model);
        view->show();
    //db.close();
*/

