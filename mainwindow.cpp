



#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "mythread.h"
#include <QDebug>
//#include <eca-control-interface.h>

#include <QFileDialog>

#include <QLineEdit>
#include <QFile>

#include <QApplication>
#include <QProcess>

#include <QMessageBox>

#include <QCloseEvent>

#include <signal.h>

#include <QPalette>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

//sql
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

//QSqlDatabase db;
//QSqlDatabase notesdb;

//alsa

int mrid;
int mrport;

QList<QString> nameAr;
QList<QString> clientAr;
QList<QString> portAr;
QList<QString> fullAr;

static int queue;

//ALSA
//install libasound2 and libasound2-dev

#include <err.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <alsa/asoundlib.h>
#include "asoundlib.h"
#include <config.h.in>
#include <version.h>

#include <linux/soundcard.h>


//#include <QProcess>

#include <cstdio>
#include <ctime>
#include <cmath>

#include <vector>

//

int disconandexit = 0;



//#include <QMutex>
int quitvalue;

// ui->label->setText();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->statusBar->setStyleSheet("color: red");
    ui->statusBar->showMessage("Midi Status: Press '>'.");

  //write sh files/check if sh files are already there...

QString HomePathT = QDir::homePath();

QString trm8ttsyspathshe1 = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_exit.sh";
QString trm8ttsyspathshe2 = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_exit2.sh";

QString trm8ttsyspathshr1 = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_restart.sh";
QString trm8ttsyspathshr2 = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_restart2.sh";


QString trm8tts_exepath = HomePathT + "/GUI_TRM8TT/GUI_TRM8TT";






QString textofshe1_line1 = "#!/bin/sh";
QString textofshe1_line2 = trm8ttsyspathshe2;

QFile chfile1(trm8ttsyspathshe1);



               if(QFileInfo::exists(trm8ttsyspathshe1))
               {

                  qDebug() << "...11111111111.....GUI_xTRM8TT_exit.sh......sh file exists.........." ;

                  //
//                  QMessageBox msgBox;
//                  msgBox.setText("GUI_xTRM8TT_exit.sh......sh file exists");
//                  msgBox.exec();
               }
               else
               {

                   if (!chfile1.open(QIODevice::WriteOnly | QIODevice::Text))
                   {
      qDebug() << "..............restart error can't write file..........";
                   }
                        // return;
                   else
                   {
                     QTextStream outh(&chfile1);
                     outh << textofshe1_line1 << endl;
                      outh << textofshe1_line2 << endl;
                     qDebug() << "writing to file before restarting...recmode.. ." << textofshe1_line1;
                      qDebug() << "writing to file before restarting...recmode.. ." << textofshe1_line2;
                    }

                     chfile1.close();


                     //
                     QMessageBox msgBox;
                     msgBox.setText("New .sh file in /home/[username]/GUI_TRM8TT created. Please restart PC, mark all GUI_xTRM8TT_exit.sh or GUI_xTRM8TT_restart.sh files as executables and restart the program.");
                     msgBox.exec();




               }

               //exit2

               QString textofshe2_line1 = "#!/bin/sh";
                QString textofshe2_line2 = "if pgrep GUI_TRM8TT; then pkill GUI_TRM8TT; fi";
                  QString textofshe2_line3 = "if pgrep ecasound; then pkill ecasound; fi";
                    QString textofshe2_line4 = "sleep 1s";
                      QString textofshe2_line5 = "if pgrep GUI_TRM8TT; then pkill GUI_TRM8TT; fi";
                        QString textofshe2_line6 = "if pgrep ecasound; then pkill ecasound; fi";






               QFile chfile2(trm8ttsyspathshe2);



                              if(QFileInfo::exists(trm8ttsyspathshe2))
                              {

                                 qDebug() << "........GUI_xTRM8TT_exit2.sh......sh file exists.........." ;

                                 //
//                                 QMessageBox msgBox;
//                                 msgBox.setText("GUI_xTRM8TT_exit2.sh......sh file exists");
//                                 msgBox.exec();
                              }
                              else
                              {

                                  if (!chfile2.open(QIODevice::WriteOnly | QIODevice::Text))
                                  {
                     qDebug() << "..............restart error can't write file..........";
                                  }
                                       // return;
                                  else
                                  {
                                    QTextStream outh(&chfile2);
                                    outh << textofshe2_line1 << endl;
                                    outh << textofshe2_line2 << endl;
                                    outh << textofshe2_line3 << endl;
                                    outh << textofshe2_line4 << endl;
                                    outh << textofshe2_line5 << endl;
                                    outh << textofshe2_line6 << endl;





                                   }

                                    chfile2.close();


                                    //
                                    QMessageBox msgBox;
                                    msgBox.setText("New .sh file in /home/[username]/GUI_TRM8TT created. Please restart PC, mark all GUI_xTRM8TT_exit or GUI_xTRM8TT_restart files as executables and restart the program.");
                                    msgBox.exec();




                              }



               //end exit2


//exit3


                              QString textofshr1_line1 = "#!/bin/sh";
                              QString textofshr1_line2 = trm8ttsyspathshr2;

                              QFile chfile3(trm8ttsyspathshr1);



                                             if(QFileInfo::exists(trm8ttsyspathshr1))
                                             {

                                                qDebug() << "........GUI_xTRM8TT_restart.sh......sh file exists.........." ;

                                                //
//                                                QMessageBox msgBox;
//                                                msgBox.setText("GUI_xTRM8TT_restart.sh.....sh file exists");
//                                                msgBox.exec();
                                             }
                                             else
                                             {

                                                 if (!chfile3.open(QIODevice::WriteOnly | QIODevice::Text))
                                                 {
                                    qDebug() << "..............restart error can't write file..........";
                                                 }
                                                      // return;
                                                 else
                                                 {
                                                   QTextStream outh(&chfile3);
                                                   outh << textofshr1_line1 << endl;
                                                    outh << textofshr1_line2 << endl;
                                                   qDebug() << "writing to file before restarting...recmode.. ." << textofshr1_line1;
                                                    qDebug() << "writing to file before restarting...recmode.. ." << textofshr1_line2;
                                                  }

                                                   chfile3.close();


                                                   //
                                                   QMessageBox msgBox;
                                                   msgBox.setText("New .sh file in /home/[username]/GUI_TRM8TT created. Please restart PC, mark all GUI_xTRM8TT_exit or GUI_xTRM8TT_restart files as executables and restart the program.");
                                                   msgBox.exec();




                                             }


 //end exit3

            // exit4


                                             QString textofshr2_line1 = "#!/bin/sh";
                                              QString textofshr2_line2 = "if pgrep GUI_TRM8TT; then pkill GUI_TRM8TT; fi";
                                                QString textofshr2_line3 = "if pgrep ecasound; then pkill ecasound; fi";
                                                  QString textofshr2_line4 = "sleep 1s";
                                                    QString textofshr2_line5 = "if pgrep GUI_TRM8TT; then pkill GUI_TRM8TT; fi";
                                                      QString textofshr2_line6 = "if pgrep ecasound; then pkill ecasound; fi";
                                                      QString textofshr2_line7 = trm8tts_exepath;

//                                                 QFile Fileexe(QCoreApplication::applicationDirPath());

//                                                 QFileInfo fileInfo(Fileexe.fileName());
//                                                 QString filename(fileInfo.fileName());

//                                                     qDebug() << "..............file+++++++++++++++++++++++++++++++++++++++++........." << filename;


//                                                QString exepath =     QDir::currentPath();

//                                                 qDebug() << "..............exepath ++++++++++++++++++++++++++++++++++++++++++++++++........." << exepath ;

//                                                 QDir dir(".");
//                                                 qDebug() << dir.absolutePath() << "dir.absolutePath() " <<endl;






                                             QFile chfile4(trm8ttsyspathshr2);



                                                            if(QFileInfo::exists(trm8ttsyspathshr2))
                                                            {

                                                               qDebug() << "........GUI_xTRM8TT_restart2.sh......sh file exists.........." ;

                                                               //
//                                                               QMessageBox msgBox;
//                                                               msgBox.setText("GUI_xTRM8TT_restart2.sh......sh file exists");
//                                                               msgBox.exec();
                                                            }
                                                            else
                                                            {

                                                                if (!chfile4.open(QIODevice::WriteOnly | QIODevice::Text))
                                                                {
                                                   qDebug() << "..............restart error can't write file..........";
                                                                }
                                                                     // return;
                                                                else
                                                                {
                                                                  QTextStream outh(&chfile4);
                                                                  outh << textofshr2_line1 << endl;
                                                                  outh << textofshr2_line2 << endl;
                                                                  outh << textofshr2_line3 << endl;
                                                                  outh << textofshr2_line4 << endl;
                                                                  outh << textofshr2_line5 << endl;
                                                                  outh << textofshr2_line6 << endl;
                                                                  outh << textofshr2_line7 << endl;

                                                                          //path of exe





                                                                 }

                                                                  chfile4.close();


                                                                  //
                                                                  QMessageBox msgBox;
                                                                  msgBox.setText("New .sh file in /home/[username]/GUI_TRM8TT created. Please restart PC, mark all GUI_xTRM8TT_exit or GUI_xTRM8TT_restart files as executables and restart the program.");
                                                                  msgBox.exec();




                                                            }







       //end exit4


  //sh end

  //+++++++++++++++++tape slot

     QString activetapeST;

        // QString HomePathT = QDir::homePath();
              QString tapeslotfilename = HomePathT + "/GUI_TRM8TT/trm8tt_tapeslot.txt";

                //QFile rhfile("trm8tt_tapeslot.txt");
                   QFile rhfile(tapeslotfilename);

                       if (!rhfile.open(QIODevice::ReadOnly | QIODevice::Text))
                       {

                           QMessageBox msgBox;
                           msgBox.setText("Tape missing. Please select a tape folder.");
                           msgBox.exec();

                            qDebug() << ".......................!hfile.open...  activetapeNR 1";
                       }
                       //
                       else
                       {
                       QTextStream rin(&rhfile);
                            while (!rin.atEnd())
                               {
                                 QString rhostrr = rin.readLine();

                                 if(~(rhostrr.isEmpty()))
                                      {
                                  qDebug() << rhostrr << "+++++++++++++++++string+1++++++activetapeST++++++++++++++++++in.readLine" ;
                                //int rforrecmode=rhostrr.toInt();
                                     activetapeST=rhostrr;
                                 qDebug() << activetapeST << "+++++++++++++activetapeST+++++++++++++++++++++++++++in.readLine" ;
                                 //activetapeNR=rforrecmode;

                                      }
                                 else
                                 {
                                     QMessageBox msgBox;
                                     msgBox.setText("Tape missing. Please select a tape folder.");
                                     msgBox.exec();
                                 }
                                }
                       }
                        rhfile.close();


//+++++++++++++++++
//database

    const QString DRIVER("QSQLITE");
     QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

//     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","connection1");
//     QSqlDatabase notesdb = QSqlDatabase::addDatabase("QSQLITE","connection2");

//  db = QSqlDatabase::addDatabase("QSQLITE","connection1");
// notesdb = QSqlDatabase::addDatabase("QSQLITE","connection2");


     //QString dbnamepath = HomePathT + "/GUI_TRM8TT/trm8tt_db";

      QString dbnamepath = activetapeST +"/trm8tt_db";

           //db.setDatabaseName("trm8tt_db");
               db.setDatabaseName(dbnamepath);

           if(!db.open())
           {
             qWarning() << "SQLite ERROR: " << db.lastError();
            }


//move to tape folder
//           QString dbnamepath2 = HomePathT + "/GUI_TRM8TT/trm8tt_db2";

//                 //db.setDatabaseName("trm8tt_db");
//                     notesdb.setDatabaseName(dbnamepath2);

//                 if(!notesdb.open())
//                 {
//                   qWarning() << "SQLite 2 ERROR: " << notesdb.lastError();
//                  }


//                 QSqlQuery testquery (notesdb);
               //  testquery.exec("CREATE TABLE IF NOT EXISTS testtracktable (id INTEGER PRIMARY KEY, testtracknumber INTEGER, testrecvalue INTEGER, testinputs TEXT, testtracknote TEXT)");
//


QSqlQuery query;
query.exec("CREATE TABLE IF NOT EXISTS tracktable (id INTEGER PRIMARY KEY, tracknumber INTEGER, recvalue INTEGER, inputs TEXT, tracknote TEXT)");





   if(!query.isActive())
       qWarning() << "---------------------sql ERROR: " << query.lastError().text();



     QSqlQuery query31;
             query31.exec("INSERT INTO tracktable(id, tracknumber) VALUES(1, 1);");

     QSqlQuery query32;
             query32.exec("INSERT INTO tracktable(id, tracknumber) VALUES(2, 2);");
     QSqlQuery query33;
             query33.exec("INSERT INTO tracktable(id, tracknumber) VALUES(3, 3);");
     QSqlQuery query34;
             query34.exec("INSERT INTO tracktable(id, tracknumber) VALUES(4, 4);");

     QSqlQuery query35;
             query35.exec("INSERT INTO tracktable(id, tracknumber) VALUES(5, 5);");
     QSqlQuery query36;
             query36.exec("INSERT INTO tracktable(id, tracknumber) VALUES(6, 6);");
     QSqlQuery query37;
             query37.exec("INSERT INTO tracktable(id, tracknumber) VALUES(7, 7);");
     QSqlQuery query38;
             query38.exec("INSERT INTO tracktable(id, tracknumber) VALUES(8, 8);");





QSqlQuery querys1;
querys1.exec("CREATE TABLE IF NOT EXISTS settingstable (id INTEGER PRIMARY KEY, settings TEXT, settingstext TEXT, settingsint INTEGER)");

if(!querys1.isActive())
    qWarning() << "---------------------sql ERROR: " << querys1.lastError().text();

QSqlQuery querys11;
querys11.exec("INSERT INTO settingstable(id, settings) VALUES(1, 'mode')");
QSqlQuery querys12;
querys12.exec("INSERT INTO settingstable(id, settings) VALUES(2, 'controller')");
QSqlQuery querys13;
querys13.exec("INSERT INTO settingstable(id, settings) VALUES(3, 'folder')");

QSqlQuery querys14;
querys14.exec("INSERT INTO settingstable(id, settings) VALUES(4, 'vol_map')");
QSqlQuery querys15;
querys15.exec("INSERT INTO settingstable(id, settings) VALUES(5, 'pan_map')");

QSqlQuery querys16;
querys16.exec("INSERT INTO settingstable(id, settings) VALUES(6, 'ff')");
QSqlQuery querys17;
querys17.exec("INSERT INTO settingstable(id, settings) VALUES(7, 'rw')");
QSqlQuery querys18;
querys18.exec("INSERT INTO settingstable(id, settings) VALUES(8, 'play')");
QSqlQuery querys19;
querys19.exec("INSERT INTO settingstable(id, settings) VALUES(9, 'stop')");
QSqlQuery querys20rtz;
querys20rtz.exec("INSERT INTO settingstable(id, settings) VALUES(10, 'rtz')");





////read sql
//     QSqlQuery query2("SELECT tracknumber FROM tracktable WHERE id = 8");
//    if(!query2.isActive())
//            qWarning() << "---------------------sql ERROR: " << query2.lastError().text();

//    if(query2.first())
//      qDebug() << "sql output ------------------------" << (query2.value(0).toString());
//    else
//      qDebug() << ("track data not found in db");


////update db
 // QSqlQuery query39("UPDATE tracktable SET recvalue = 1 WHERE id = 7;");

QString sTapeFolder=activetapeST;



QSqlQuery query39tfolder1;
        query39tfolder1.exec("UPDATE settingstable SET settingstext = '" + sTapeFolder + "' WHERE id = 3;");

//QSqlQuery queryrsf2ss;
//queryrsf2ss.exec("SELECT settingstext FROM settingstable WHERE settings = 'folder';");

//     if(!queryrsf2ss.isActive())
//            {
//                    qWarning() << "---------------------sql ERROR: " << queryrsf2ss.lastError().text();
//            }
//            if(queryrsf2ss.first())
//            {
//                sTapeFolder = (queryrsf2ss.value(0).toString());
//              //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryrsf2.value(0).toString()) << "trackNRstring:" << trackNRstring;
//              qDebug() << "sTapeFolder= ------------------------" << sTapeFolder;
//            }
//            else
//            {
//              qDebug() << ("sTapeFolder data not found in db");
//            }


 ui->label_file->setText(sTapeFolder);

 if(sTapeFolder==NULL)
 {

     QMessageBox msgBox;
     msgBox.setText("Tape missing. Please select a tape folder.");
     msgBox.exec();
}


 //QSqlQuery querys1addcol("ALTER TABLE tracktable ADD COLUMN IF NOT EXISTS '" + sTapeFolder + "' TEXT");

//tracknotes

 QString  n1string;

 QSqlQuery n1queryr2;
 n1queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 1;");

if(!n1queryr2.isActive())
{
        qWarning() << "---------------------sql ERROR: " << n1queryr2.lastError().text();
}
if(n1queryr2.first())
{
    n1string = (n1queryr2.value(0).toString());
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
   //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
  qDebug() << ("track data not found in db");
}

ui->lineEdit->setText(n1string);

//--2

QString  n2string;

QSqlQuery n2queryr2;
n2queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 2;");

if(!n2queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n2queryr2.lastError().text();
}
if(n2queryr2.first())
{
   n2string = (n2queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n2string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_2->setText(n2string);

//3

QString  n3string;

QSqlQuery n3queryr2;
n3queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 3;");

if(!n3queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n3queryr2.lastError().text();
}
if(n3queryr2.first())
{
   n3string = (n3queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_3->setText(n3string);

//4

QString  n4string;

QSqlQuery n4queryr2;
n4queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 4;");

if(!n4queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n4queryr2.lastError().text();
}
if(n4queryr2.first())
{
   n4string = (n4queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_4->setText(n4string);

//5

QString  n5string;

QSqlQuery n5queryr2;
n5queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 5;");

if(!n5queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n5queryr2.lastError().text();
}
if(n5queryr2.first())
{
   n5string = (n5queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_5->setText(n5string);

//6

QString  n6string;

QSqlQuery n6queryr2;
n6queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 6;");

if(!n6queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n6queryr2.lastError().text();
}
if(n6queryr2.first())
{
   n6string = (n6queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_6->setText(n6string);

//7

QString  n7string;

QSqlQuery n7queryr2;
n7queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 7;");

if(!n7queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n7queryr2.lastError().text();
}
if(n7queryr2.first())
{
   n7string = (n7queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_7->setText(n7string);

//8

QString  n8string;

QSqlQuery n8queryr2;
n8queryr2.exec("SELECT tracknote FROM tracktable WHERE tracknumber = 8;");

if(!n8queryr2.isActive())
{
       qWarning() << "---------------------sql ERROR: " << n8queryr2.lastError().text();
}
if(n8queryr2.first())
{
   n8string = (n8queryr2.value(0).toString());
 //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" <<  n1string  << "trackNRstring:" ;
}
else
{
 qDebug() << ("track data not found in db");
}

ui->lineEdit_8->setText(n8string);

//




//database end



      mThread = new Thread1(this);


//      QFile hfile(".eca_hfile.txt");
//      if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
//          return;
//      QTextStream in(&hfile);
//      while (!in.atEnd()) {
//          QString hostr = in.readLine();
//          //qDebug() << hostr;
//          if(~(hostr.isEmpty())){
//          ui->label_2->setText(hostr);}
//                  }


 mThread->start();

 qDebug() << "_____________________--mainwindow thread" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());




//connect(mThread,SIGNAL(possignal(int)), this, SLOT(valueGot(int)));



 //connect(this,SIGNAL(signalValueUpdated(int)),mThread, SLOT(valueChanged1(int)));
 connect(this,SIGNAL(signalValueUpdated(int)),mThread, SLOT(rewind(int searchvalue)));
 connect(this,SIGNAL(signalValueUpdated(int)),mThread, SLOT(forward(int searchvalue)));

  //


connect(mThread,SIGNAL(t1signal(int)), this, SLOT(tograph1(int)));
connect(mThread,SIGNAL(t2signal(int)), this, SLOT(tograph2(int)));
connect(mThread,SIGNAL(t3signal(int)), this, SLOT(tograph3(int)));
connect(mThread,SIGNAL(t4signal(int)), this, SLOT(tograph4(int)));
connect(mThread,SIGNAL(t5signal(int)), this, SLOT(tograph5(int)));
connect(mThread,SIGNAL(t6signal(int)), this, SLOT(tograph6(int)));
connect(mThread,SIGNAL(t7signal(int)), this, SLOT(tograph7(int)));
connect(mThread,SIGNAL(t8signal(int)), this, SLOT(tograph8(int)));



//connect(mThread,SIGNAL(t1signal(int)), ui->progressBar1, SLOT(setValue(int)));
//connect(mThread,SIGNAL(t1signal(QString)), ui->plabel1green, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t2signal(QString)), ui->label_t2, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t3signal(QString)), ui->label_t3, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t4signal(QString)), ui->label_t4, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t5signal(QString)), ui->label_t5, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t6signal(QString)), ui->label_t6, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t7signal(QString)), ui->label_t7, SLOT(setText(QString)));
//connect(mThread,SIGNAL(t8signal(QString)), ui->label_t8, SLOT(setText(QString)));

connect(mThread,SIGNAL(red1signal(QString)), ui->label_t1, SLOT(setText(QString)));
connect(mThread,SIGNAL(red2signal(QString)), ui->label_t2, SLOT(setText(QString)));
connect(mThread,SIGNAL(red3signal(QString)), ui->label_t3, SLOT(setText(QString)));
connect(mThread,SIGNAL(red4signal(QString)), ui->label_t4, SLOT(setText(QString)));

connect(mThread,SIGNAL(red5signal(QString)), ui->label_t5, SLOT(setText(QString)));
connect(mThread,SIGNAL(red6signal(QString)), ui->label_t6, SLOT(setText(QString)));
connect(mThread,SIGNAL(red7signal(QString)), ui->label_t7, SLOT(setText(QString)));
connect(mThread,SIGNAL(red8signal(QString)), ui->label_t8, SLOT(setText(QString)));


//connect(mThread,SIGNAL(jarsignal(QList)), ui->comboBox_7, SLOT(addItems(QList)));

//connect(mThread,SIGNAL(jarsignal(QList)), this, SLOT(tolistinput(QList)));
connect(mThread,SIGNAL(jarsignal(QString)), this, SLOT(tolistinput(QString)));
  //void jarsignal(QList<QString> sendjar);

   //void t1signal(int sendiT1);




connect(mThread,SIGNAL(possignalmin(QString)), ui->label_posmin, SLOT(setText(QString)));
//connect(mThread,SIGNAL(possignalsec(QString)), ui->label_possec, SLOT(setText(QString)));

connect(mThread,SIGNAL(jsignalrate(QString)), ui->label_jackrate, SLOT(setText(QString)));
//connect(mThread,SIGNAL(midiinfo(QString)), ui->label_midi, SLOT(setText(QString)));


connect(mThread,SIGNAL(midiinfo(QString)), ui->statusBar, SLOT(showMessage(QString)));


connect(mThread,SIGNAL(enable1(bool)), ui->armButton, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable2(bool)), ui->armButton_2, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable3(bool)), ui->armButton_3, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable4(bool)), ui->armButton_4, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable5(bool)), ui->armButton_5, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable6(bool)), ui->armButton_6, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable7(bool)), ui->armButton_7, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable8(bool)), ui->armButton_8, SLOT(setEnabled(bool)));


connect(mThread,SIGNAL(enable1(bool)), ui->comboBox, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable2(bool)), ui->comboBox_2, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable3(bool)), ui->comboBox_3, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable4(bool)), ui->comboBox_4, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable5(bool)), ui->comboBox_5, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable6(bool)), ui->comboBox_6, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable7(bool)), ui->comboBox_7, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enable8(bool)), ui->comboBox_8, SLOT(setEnabled(bool)));

connect(mThread,SIGNAL(enablerec(bool)), ui->recButton, SLOT(setEnabled(bool)));
connect(mThread,SIGNAL(enablenonrec(bool)), ui->nonrecButton, SLOT(setEnabled(bool)));


connect(mThread,SIGNAL(ffclicked(int)), ui->FFButton, SLOT(animateClick(int)));
connect(mThread,SIGNAL(rwclicked(int)), ui->RWButton, SLOT(animateClick(int)));
connect(mThread,SIGNAL(stopclicked(int)), ui->stopButton, SLOT(animateClick(int)));
connect(mThread,SIGNAL(playclicked(int)), ui->playButton, SLOT(animateClick(int)));
connect(mThread,SIGNAL(resetclicked(int)), ui->rtzButton, SLOT(animateClick(int)));



//connect(mThread,SIGNAL(lensignalmin(QString)), ui->label_alenmin, SLOT(setText(QString)));
//connect(mThread,SIGNAL(lensignalsec(QString)), ui->plainTextEdit, SLOT(setText(QString)));

//connect(mThread,SIGNAL(textoutput(QString)), ui->plainTextEdit, SLOT(insertPlainText(QString)));


connect(mThread,SIGNAL(exitvalue(int)), this, SLOT(exitslot0(int)));

//ui->spinBox->setValue(5);

//get midi controller

#define perm_ok(pinfo,bits) ((snd_seq_port_info_get_capability(pinfo) & (bits)) == (bits))
snd_seq_t *seqm;
snd_seq_open(&seqm, "default", SND_SEQ_OPEN_DUPLEX, 0);
//

    mrid = snd_seq_client_id(seqm);
    //qDebug() <<  mrid;

    mrport = snd_seq_set_client_name(seqm, "AlsaConnector");
    //qDebug() <<  mrport;

    //
    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;
    //



        snd_seq_port_info_alloca(&pinfo);


        snd_seq_port_info_set_capability(pinfo,
                         SND_SEQ_PORT_CAP_WRITE |
                         SND_SEQ_PORT_CAP_SUBS_WRITE);
        snd_seq_port_info_set_type(pinfo,
                       SND_SEQ_PORT_TYPE_MIDI_GENERIC |
                       SND_SEQ_PORT_TYPE_APPLICATION);
        snd_seq_port_info_set_midi_channels(pinfo, 16);


        snd_seq_port_info_set_timestamping(pinfo, 1);
        snd_seq_port_info_set_timestamp_queue(pinfo, queue);




//



    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);
    snd_seq_client_info_set_client(cinfo, -1);
    while (snd_seq_query_next_client(seqm, cinfo) >= 0)

    {
            snd_seq_port_info_set_client(pinfo, snd_seq_client_info_get_client(cinfo));
            snd_seq_port_info_set_port(pinfo, -1);

            int seldd = 0;
             int iseldd = 0;

            while (snd_seq_query_next_port(seqm, pinfo) >= 0)


                //output


                if (    perm_ok
                                       (pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ))
                                       //(pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE))
                                           {
                                               QString pname = snd_seq_port_info_get_name(pinfo);
                                            qDebug() << "pname" << pname;
                                               nameAr.append(pname);
                                               int icnum = snd_seq_client_info_get_client(cinfo);
                                               QString scnum = QString::number(icnum);
                                              // qDebug() << scnum;
                                               clientAr.append(scnum);
                                               //
                                               const char* fullname = snd_seq_client_info_get_name(cinfo);
                                              qDebug() << "fullname";
                                                   qDebug() << fullname;
                                                    //fullAr.append(fullname + pname);
                                                    fullAr.append(fullname);
                                               //
                                               int ipnum = snd_seq_port_info_get_port(pinfo);
                                               QString spnum = QString::number(ipnum);
                                             // qDebug() << spnum;
                                               portAr.append(spnum);
                                              seldd++;
                                           }






     }


    ui->comboBoxClients->addItems(fullAr);
   // ui->comboBox2->addItems(nameArIn);


snd_seq_close(seqm);


}

void MainWindow::savemidislot()
{
QString HomePathT = QDir::homePath();
     QString controllerfilename = HomePathT + "/GUI_TRM8TT/trm8tt_controller.txt";

    int getmididev2 = ui->comboBoxClients->currentIndex();
         //qDebug() << getmididev;

         QString getclient2 =  fullAr[getmididev2];

   // QFile chfile("trm8tt_controller.txt");
      QFile chfile(controllerfilename);
                 if (!chfile.open(QIODevice::WriteOnly | QIODevice::Text))
                 {
   qDebug() << ".............can't write trm8tt_controller file.........";
                 }

                 else
                 {
                   QTextStream outh(&chfile);
                   outh << getclient2;
                   qDebug() << "writing to file trm8tt_controller.. ." << getclient2;
                  }

                   chfile.close();




                   //sql

                   QSqlQuery query39savem;
                           query39savem.exec("UPDATE settingstable SET settingstext = '" + getclient2 + "' WHERE id = 2;");






                   //


                   QMessageBox msgBox;
                   msgBox.setText("Please restart GUI_TRM8TT.");
                   msgBox.exec();

}

//get system:capture_x input for recording

void MainWindow::recbuttonslot()
{
    qDebug() << "*******************************recbuttonslot";

    if(ui->checkBox_1->isChecked())
    {
       getinput1();

          qDebug() << "add track 1 to rec list -> sql";

          //update db
                QSqlQuery queryu71;
                        queryu71.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 1;");

    }

    if(ui->checkBox_2->isChecked())
    {
       getinput2();

          qDebug() << "add track 2 to rec list -> sql";

          //update db
                QSqlQuery queryu72;
                        queryu72.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 2;");

    }

    if(ui->checkBox_3->isChecked())
    {
       getinput3();

          qDebug() << "add track 3 to rec list -> sql";

          //update db
                QSqlQuery queryu73;
                        queryu73.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 3;");

    }

    if(ui->checkBox_4->isChecked())
    {
       getinput4();

          qDebug() << "add track 4 to rec list -> sql";

          //update db
                QSqlQuery queryu74;
                        queryu74.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 4;");

    }

    if(ui->checkBox_5->isChecked())
    {
       getinput5();

          qDebug() << "add track 5 to rec list -> sql";

          //update db
                QSqlQuery queryu75;
                        queryu75.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 5;");

    }

    if(ui->checkBox_6->isChecked())
    {
       getinput6();

          qDebug() << "add track 6 to rec list -> sql";

          //update db
                QSqlQuery queryu76;
                        queryu76.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 6;");

    }

    if(ui->checkBox_7->isChecked())
    {
       getinput7();

          qDebug() << "add track 7 to rec list -> sql";

          //update db
                QSqlQuery queryu71;
                        queryu71.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 7;");

    }

    if(ui->checkBox_8->isChecked())
    {
       getinput8();

          qDebug() << "add track 8 to rec list -> sql";

          //update db
                QSqlQuery queryu78;
                        queryu78.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 8;");

    }

 if((ui->checkBox_1->isChecked())||(ui->checkBox_2->isChecked())||(ui->checkBox_3->isChecked())||(ui->checkBox_4->isChecked())||(ui->checkBox_5->isChecked())||(ui->checkBox_6->isChecked())||(ui->checkBox_7->isChecked())||(ui->checkBox_8->isChecked()))
{
//     QMessageBox msgBox;
//     msgBox.setText("Changing to RECORDING MODE...relax");
//     msgBox.exec();


     if (QMessageBox::Yes == QMessageBox::question(this, "GUI_TRM8TT", "Changing to RECORDING MODE...?", QMessageBox::Yes | QMessageBox::No))
        {
           mThread->restart_slot();

        }


}

 else
 {
     QMessageBox msgBox;
     msgBox.setText("No track(s) selected.");
     msgBox.exec();
 }
//   else
//    {


// qDebug() << "track 7 is not added to the list, if no track is added, no recording... in this case: warning and no restart";

//  QSqlQuery queryu72("UPDATE tracktable SET recvalue = 0 WHERE id = 7;");

//    }



}

//getinput

void MainWindow::nonrecbuttonslot()
{



     QSqlQuery queryusetallnull1;
             queryusetallnull1.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 1;");
         QSqlQuery queryusetallnull2;
                 queryusetallnull2.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 2;");
             QSqlQuery queryusetallnull3;
                     queryusetallnull3.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 3;");
                 QSqlQuery queryusetallnull4;
                         queryusetallnull4.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 4;");

                     QSqlQuery queryusetallnull5;
                             queryusetallnull5.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 5;");
                         QSqlQuery queryusetallnull6;
                                 queryusetallnull6.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 6;");
                             QSqlQuery queryusetallnull7;
                                     queryusetallnull7.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 7;");
                                 QSqlQuery queryusetallnull8;
                                         queryusetallnull8.exec("UPDATE tracktable SET recvalue = 0 WHERE id = 8;");


//                                         QMessageBox msgBox;
//                                         msgBox.setText("Changing to PLAYBACK MODE...relax");
//                                         msgBox.exec();

                                         if (QMessageBox::Yes == QMessageBox::question(this, "GUI_TRM8TT", "Changing to PLAYBACK MODE...?", QMessageBox::Yes | QMessageBox::No))
                                            {

                                               mThread->restart_slot();
                                            }







}





void MainWindow::getinput1()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput1 = ui->comboBox->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput1 -> sql" << getinput1;

                 QSqlQuery queryu11;
                         queryu11.exec("UPDATE tracktable SET inputs = '" + getinput1 + "' WHERE id = 1;");



}

void MainWindow::getinput2()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput2 = ui->comboBox_2->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput2 -> sql" << getinput2;

                 QSqlQuery queryu12;
                         queryu12.exec("UPDATE tracktable SET inputs = '" + getinput2 + "' WHERE id = 2;");



}

void MainWindow::getinput3()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput3 = ui->comboBox_3->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput3 -> sql" << getinput3;

                 QSqlQuery queryu13;
                         queryu13.exec("UPDATE tracktable SET inputs = '" + getinput3 + "' WHERE id = 3;");

//QString query_string = "UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;";

}

void MainWindow::getinput4()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput4 = ui->comboBox_4->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinpu4t4-> sql" << getinput4;

                 QSqlQuery queryu14;
                         queryu14.exec("UPDATE tracktable SET inputs = '" + getinput4 + "' WHERE id = 4;");



}

void MainWindow::getinput5()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput5 = ui->comboBox_5->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput5 -> sql" << getinput5;

                 QSqlQuery queryu15;
                         queryu15.exec("UPDATE tracktable SET inputs = '" + getinput5 + "' WHERE id = 5;");

//QString query_string = "UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;";

}

void MainWindow::getinput6()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput6 = ui->comboBox_6->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput6 -> sql" << getinput6;

                 QSqlQuery queryu16;
                         queryu16.exec("UPDATE tracktable SET inputs = '" + getinput6 + "' WHERE id = 6;");

//QString query_string = "UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;";

}

void MainWindow::getinput7()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput7 = ui->comboBox_7->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput7 -> sql" << getinput7;

                 QSqlQuery queryu73;
                         queryu73.exec("UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;");

//QString query_string = "UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;";

}

void MainWindow::getinput8()
{
   // int getinput7int = ui->comboBox_7->currentIndex();
     QString getinput8 = ui->comboBox_8->currentText();


            //QString getinput7 =  fullAr[getinput7int];

             //QString getinput7 =  fullAr[getinput7int];

                qDebug() << "getinput8 -> sql" << getinput8;

                 QSqlQuery queryu18;
                         queryu18.exec("UPDATE tracktable SET inputs = '" + getinput8 + "' WHERE id = 8;");

//QString query_string = "UPDATE tracktable SET inputs = '" + getinput7 + "' WHERE id = 7;";

}





//getinput end
//

void MainWindow::closeEvent(QCloseEvent *event)
{


event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "GUI_TRM8TT", "Disconnect and Exit?", QMessageBox::Yes | QMessageBox::No))
    {
       mThread->exitslot();
        event->accept();

    }


    if (disconandexit==1)
    {
    {
             qDebug() << "closeevvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvent" ;
        mThread->exitslot();
        event->accept();
    }

    }







}



void MainWindow::tolistinput(QString sendjar)
{
//qDebug() << "sendjar" << sendjar;

ui->comboBox->addItem(sendjar);
ui->comboBox_2->addItem(sendjar);
ui->comboBox_3->addItem(sendjar);
ui->comboBox_4->addItem(sendjar);
ui->comboBox_5->addItem(sendjar);
ui->comboBox_6->addItem(sendjar);
ui->comboBox_7->addItem(sendjar);
ui->comboBox_8->addItem(sendjar);


}




void MainWindow::tograph1(int sendiT1)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT1>0)&&(sendiT1<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT1*2, outlinePen, greenBrush);
   }

   if((sendiT1>70)&&(sendiT1<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT1*2, outlinePen, yellowBrush);
   }

   if((sendiT1>90)&&(sendiT1<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT1*2, outlinePen, redBrush);
   }

}

//2

void MainWindow::tograph2(int sendiT2)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_2->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT2>0)&&(sendiT2<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT2*2, outlinePen, greenBrush);
   }

   if((sendiT2>70)&&(sendiT2<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT2*2, outlinePen, yellowBrush);
   }

   if((sendiT2>90)&&(sendiT2<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT2*2, outlinePen, redBrush);
   }

}


//3

void MainWindow::tograph3(int sendiT3)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_3->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT3>0)&&(sendiT3<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT3*2, outlinePen, greenBrush);
   }

   if((sendiT3>70)&&(sendiT3<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT3*2, outlinePen, yellowBrush);
   }

   if((sendiT3>90)&&(sendiT3<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT3*2, outlinePen, redBrush);
   }

}


//4

void MainWindow::tograph4(int sendiT4)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_4->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT4>0)&&(sendiT4<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT4*2, outlinePen, greenBrush);
   }

   if((sendiT4>70)&&(sendiT4<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT4*2, outlinePen, yellowBrush);
   }

   if((sendiT4>90)&&(sendiT4<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT4*2, outlinePen, redBrush);
   }

}



//5

void MainWindow::tograph5(int sendiT5)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_5->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT5>0)&&(sendiT5<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT5*2, outlinePen, greenBrush);
   }

   if((sendiT5>70)&&(sendiT5<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT5*2, outlinePen, yellowBrush);
   }

   if((sendiT5>90)&&(sendiT5<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT5*2, outlinePen, redBrush);
   }

}




//6

void MainWindow::tograph6(int sendiT6)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_6->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT6>0)&&(sendiT6<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT6*2, outlinePen, greenBrush);
   }

   if((sendiT6>70)&&(sendiT6<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT6*2, outlinePen, yellowBrush);
   }

   if((sendiT6>90)&&(sendiT6<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT6*2, outlinePen, redBrush);
   }

}



//7

void MainWindow::tograph7(int sendiT7)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_7->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT7>0)&&(sendiT7<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT7*2, outlinePen, greenBrush);
   }

   if((sendiT7>70)&&(sendiT7<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT7*2, outlinePen, yellowBrush);
   }

   if((sendiT7>90)&&(sendiT7<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT7*2, outlinePen, redBrush);
   }

   //

//   if(sendiT7==9999)
//   {
//     rectangle = scene->addRect(0,0,55, sendiT7*2, outlinePen, blueBrush);
//   }



}



//8


void MainWindow::tograph8(int sendiT8)
{

//qDebug() << "_____________________--mainwindow peak meter" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());
//qDebug() << "Iti____sendiT1___________________________-" << sendiT1;

scene = new QGraphicsScene(this);
   ui->graphicsView_8->setScene(scene);

   QBrush greenBrush(Qt::green);
   QBrush redBrush(Qt::red);
   QBrush yellowBrush(Qt::yellow);
   //QBrush blueBrush(Qt::blue);
   QPen outlinePen(Qt::black);
   outlinePen.setWidth(2);

   //rectangle = scene->addRect(0,0,55, 50, outlinePen, blueBrush);

   if((sendiT8>0)&&(sendiT8<70))
   {
     rectangle = scene->addRect(0,0,121, sendiT8*2, outlinePen, greenBrush);
   }

   if((sendiT8>70)&&(sendiT8<90))
   {
     rectangle = scene->addRect(0,0,121, sendiT8*2, outlinePen, yellowBrush);
   }

   if((sendiT8>90)&&(sendiT8<100))
   {
     rectangle = scene->addRect(0,0,121, sendiT8*2, outlinePen, redBrush);
   }

}



//graph end




void MainWindow::valueGot(int timevalue)
{

    qDebug() << "timevalue" << timevalue;
}


void MainWindow::resetslot()
{

////    QString nfile( ui->lineEdit->toPlainText())   ;
//   // qDebug() << nfile;

mThread->reset();

//        //ui->StartButton->setVisible(false);
}


void MainWindow::stopslot()
{
// QPalette palette;
// palette.setColor(QPalette::Window, Qt::white);
// palette.setColor(QPalette::WindowText, Qt::blue);
// ui->plabel1green->setAutoFillBackground(true);
// ui->plabel1green->setPalette(palette);

   // ui->progressBar1->setValue(50);

  mThread->pstop();

     //rectangle->setPos(0, 0);



}

//if (m_ui.BackwardToolButton->isDown() && m_fSkipAccel < 60.0)
//m_fSkipAccel *= 1.1f;



void MainWindow::rewindslot()
{

  int searchvalue = ui->spinBox->value();
qDebug() << "searchvalueRR:::::::::::::::::::::::::::";
 qDebug() << searchvalue;


emit signalValueUpdated(searchvalue);


//mThread->valueChanged1(searchvalue);
mThread->rewind(searchvalue);


}

void MainWindow::forwardslot()
{

  int searchvalue = ui->spinBox->value();
  qDebug() << "searchvalueFF:::::::::::::::::::::::::::";
   qDebug() << searchvalue;

  emit signalValueUpdated(searchvalue);

mThread->forward(searchvalue);
}

void MainWindow::fileslot()
{
//     mThread->terminateall();
//     mThread->exitslot();
//todo: let user select default folder in settings
//    QString fileName;
//    fileName = QFileDialog::getOpenFileName(this,
//         tr("Open WAV File"), "/home/debian9/Desktop/ecasound", tr("WAV Files (*.wav)"));
//    ui->lineEdit->setText(fileName);

//    QFile hfile(".eca_hfile.txt");
//         if (!hfile.open(QIODevice::WriteOnly | QIODevice::Text))
//             return;

//         QTextStream outh(&hfile);
//         outh << fileName;
//           qApp->quit();
//           QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

//the following was OK to get the new file with signals/slots (toggle all//):
    //connect(this,SIGNAL(esignal(QString TapeFolder)),mThread,SLOT(cs_remove()));

   // mThread->terminateall();
  //  mThread->exitslot();
//todo: let user select default folder in settings

   QString TapeFolder = QFileDialog::getExistingDirectory(0, ("Select Tape Folder"), QDir::currentPath());


// QString fileName;
// fileName = QFileDialog::getOpenFileName(this,
//      tr("Open WAV File"), "/home/debian9/Desktop/ecasound", tr("WAV Files (*.wav)"));

            //emit esignal(TapeFolder);

 ui->label_file->setText(TapeFolder);

// QFile hfile(".eca_hfile.txt");
//      if (!hfile.open(QIODevice::WriteOnly | QIODevice::Text))
//          return;

//      QTextStream outh(&hfile);
//      outh << TapeFolder;


////sleep(1);
//mThread->cs_remove(TapeFolder);

 QString HomePathT = QDir::homePath();
      QString tapeslotfilename = HomePathT + "/GUI_TRM8TT/trm8tt_tapeslot.txt";

 //QFile thfile("trm8tt_tapeslot.txt");
  QFile thfile(tapeslotfilename);
              if (!thfile.open(QIODevice::WriteOnly | QIODevice::Text))
              {
qDebug() << "..............restart error can't write file... blink warning here........";
              }
                   // return;
              else
              {
                QTextStream outh(&thfile);
                outh << TapeFolder;
                qDebug() << "writing to file before restarting..tapeslot... ." << TapeFolder;
               }

                thfile.close();


QSqlQuery query39tfolder;
        query39tfolder.exec("UPDATE settingstable SET settingstext = '" + TapeFolder + "' WHERE id = 3;");

//sleep(1);
//        QMessageBox msgBox;
//        msgBox.setText("Changing tape...");
//        msgBox.exec();


        if (QMessageBox::Yes == QMessageBox::question(this, "GUI_TRM8TT", "That tape...?", QMessageBox::Yes | QMessageBox::No))
        {

    mThread->restart_slot();
        }







}




void MainWindow::playslot()
{
   mThread->play();

//   //-- int cstimestart =1;

//    //--emit signalcstimer(cstimestart);

   //mThread->csgetpos();


//   // tThread->timerChanged1(cstimestart);


}

//void MainWindow::metersslot()
//{
//    // mThread->aseqtransport();
//     mThread->rxsend();
//}




void MainWindow::note1enterslot()
{


    QString note1= ui->lineEdit->text();
    QSqlQuery query39savemn1;
                             query39savemn1.exec("UPDATE tracktable SET tracknote = '" + note1 + "' WHERE id = 1;");

}

//

void MainWindow::note2enterslot()
{


    QString note2= ui->lineEdit_2->text();
    QSqlQuery query39savemn2;
                             query39savemn2.exec("UPDATE tracktable SET tracknote = '" + note2 + "' WHERE id = 2;");

}

void MainWindow::note3enterslot()
{


    QString note3= ui->lineEdit_3->text();
    QSqlQuery query39savemn3;
                             query39savemn3.exec("UPDATE tracktable SET tracknote = '" + note3 + "' WHERE id = 3;");

}

void MainWindow::note4enterslot()
{


    QString note4= ui->lineEdit_4->text();
    QSqlQuery query39savemn4;
                             query39savemn4.exec("UPDATE tracktable SET tracknote = '" + note4 + "' WHERE id = 4;");

}

void MainWindow::note5enterslot()
{


    QString note5= ui->lineEdit_5->text();
    QSqlQuery query39savemn5;
                             query39savemn5.exec("UPDATE tracktable SET tracknote = '" + note5 + "' WHERE id = 5;");

}

void MainWindow::note6enterslot()
{


    QString note6= ui->lineEdit_6->text();
    QSqlQuery query39savemn6;
                             query39savemn6.exec("UPDATE tracktable SET tracknote = '" + note6 + "' WHERE id = 6;");

}

void MainWindow::note7enterslot()
{


    QString note7= ui->lineEdit_7->text();
    QSqlQuery query39savemn7;
                             query39savemn7.exec("UPDATE tracktable SET tracknote = '" + note7 + "' WHERE id = 7;");

}

void MainWindow::note8enterslot()
{


    QString note8= ui->lineEdit_8->text();
    QSqlQuery query39savemn8;
                             query39savemn8.exec("UPDATE tracktable SET tracknote = '" + note8 + "' WHERE id = 8;");

}



//exitslot0
void MainWindow::exitslot0(int onevalue)
{


       mThread->quit();



     qDebug() << "onevalue";
      qDebug() << onevalue;



//     qDebug() << "exitslot main"  ;

//      qDebug() << "_____________________--mainwindow exit thread" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());



//     QProcess sh;
//     sh.start("sh");

//     sh.write("pgrep ecasound");
//     sh.closeWriteChannel();

//     sh.waitForFinished();
//     QByteArray output2 = sh.readAll();

//     QString DataAsString = QString(output2);

//      QString  outp2 = DataAsString.remove("\n");

//      qDebug() << " QByteArray output" << output2 << outp2;

//       int stdoi =  outp2.toInt();

//       sleep(1);

//      if(outp2!=NULL)
//      {
//        qDebug() << "not null";

//       kill (stdoi, SIGINT);
//        //kill (stdoi, SIGTERM);
//            sleep(1);

//            qApp->quit();
//            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

//          system("reboot");

//      }




//     sh.close();

//while(outp2==NULL)
//{


//     //
//     QProcess process3;
//     QProcess process4;


//     int n = 0;
//     if(n==0)
//     {

//           process3.start("pgrep ecasound");
//           process3.waitForFinished(-1);
////sleep(2);
//           QString stdoute = process3.readAllStandardOutput();
////sleep(2);
//          QString stdoute2 = stdoute.remove("\n");

//        int stdo3 =  stdoute2.toInt();

//           qDebug() << "QProcess" << stdoute << stdoute2 << stdo3   ;

//           sleep(1);

//           n=n+1;

//           if(stdoute!=NULL)
//           {
//             qDebug() << "not null";

//            kill (stdo3, SIGINT);
//             //kill (stdo3, SIGTERM);
//                 sleep(1);
//                 qApp->quit();
//                 QProcess::startDetached(qApp->arguments()[0], qApp->arguments());


//           }

//     }
//           else
//           {
//               process4.start("pidof ecasound");
//               process4.waitForFinished(-1);
//    sleep(1);
//               QString stdoute4 = process4.readAllStandardOutput();

//              QString stdoute24 = stdoute4.remove("\n");

//            int stdo34 =  stdoute24.toInt();

//               qDebug() << "QProcess4" << stdoute4 << stdoute24 << stdo34   ;

//               if(stdoute4!=NULL)
//               {
//                 qDebug() << "not null4";

//                kill (stdo34, SIGINT);
//                 //kill (stdo34, SIGTERM);
//                     sleep(1);

//                     qApp->quit();
//                     QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
//           }
//           }




// qDebug() << "exitslot3"  ;


// process3.kill();
//  process4.kill();

  //}

//      qDebug() << "exitslot4 after jack"  ;

//    qApp->quit();
//    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());


//QApplication::exit(-1);

//disconandexit=1;



sleep(1);

//     QProcess sh;
//     sh.start("sh");

//     sh.write("pgrep GNU_TRM8TT");
//     sh.closeWriteChannel();

//     sh.waitForFinished();
//     QByteArray output2 = sh.readAll();

//     QString DataAsString = QString(output2);

//      QString  outp2 = DataAsString.remove("\n");

//      qDebug() << " QByteArray output GNU_TRM8TT" << output2 << outp2;

//       int stdoi =  outp2.toInt();

//       sleep(1);

//      if(outp2!=NULL)
//      {
//        qDebug() << "not null";

//       kill (stdoi, SIGINT);
//        //kill (stdoi, SIGTERM);
//            sleep(1);





      //



}





//exit0 end

MainWindow::~MainWindow()
{
    delete ui;
}



