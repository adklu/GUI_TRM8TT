#ifndef THREAD2_H
#define THREAD2_H

#include <QObject>

#include <QThread>

#include <cassert>
#include <cmath>
#include <cstdio>

#include "asoundlib.h"



class Thread2 : public QThread
{
    Q_OBJECT
public:
   // explicit Thread2(QObject *parent = 0, bool b = false);
    //~Thread2();

    explicit Thread2(QObject *parent = 0, bool b = false);
     ~Thread2();
   void run();

   //void timetoLED();

   //x-touch sends midi notes
   void dump_event(const snd_seq_event_t *ev);
   void aseqtransport();
   void check_snd(const char *operation, int err);



   // if Stop = true, the thread will break
   // out of the loop, and will be disposed
   bool Stop;

signals:
      void possignalstop(int timestopvalue);
      void possignalstart(int timestartvalue);
      void aseqsignal2(int aseqsignal2value);

      //void ccaseqsignal(int ccvalue);

      //void possignalsec(QString posssec);
      //void possignalmin(QString possmin);





public slots:

private slots:
      //void startstoploop(int stoploop);


};

#endif // THREAD2_H
