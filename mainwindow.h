#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "thread1.h"
#include "thread2.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Thread1 *mThread;
    //Thread2 *tThread;

signals:
//        void buttonOkClickedSignal(QString var);
        void signalValueUpdated(int);
        void esignal(QString fileName);
//          void signalcstimer(int);

//wip-v80
       // void signalRecValue_t8(int);

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QGraphicsRectItem *rectangle;

public slots:
    void closeEvent(QCloseEvent *event);


private slots:
    void resetslot();
    void stopslot();
    void fileslot();
    void writenotedb();
     void writedb();

    void note1enterslot();
      void note2enterslot();
        void note3enterslot();
          void note4enterslot();

            void note5enterslot();
              void note6enterslot();
                void note7enterslot();
                  void note8enterslot();

   void rewindslot();
   void forwardslot();
//    void metersslot();
    void playslot();
   void valueGot(int timevalue);
    void exitslot0(int onevalue);

    void tograph1(int sendiT1);
     void tograph2(int sendiT2);
      void tograph3(int sendiT3);
       void tograph4(int sendiT4);

       void tograph5(int sendiT5);
       void tograph6(int sendiT6);
       void tograph7(int sendiT7);
       void tograph8(int sendiT8);

       void getframerate(float gxrate);

       void savemidislot();

       void tolistinput(QString sendjar);

       void recbuttonslot();
       void nonrecbuttonslot();

       void getinput1();
           void getinput2();
               void getinput3();
                   void getinput4();

                       void getinput5();
                           void getinput6();
                               void getinput7();
                                   void getinput8();




};

#endif // MAINWINDOW_H









