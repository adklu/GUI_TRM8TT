#ifndef THREAD1_H
#define THREAD1_H

//#include <jack/jack.h>
//#include <jack/transport.h>
//#include <jack/metadata.h>
//#include <jack/control.h>

#include "eca-control-interface.h"

#include <vector>

#include <cassert>
#include <cmath>
#include <cstdio>

#include "asoundlib.h"


#include <QThread>

#include "thread2.h"


class Thread1 : public QThread
{


    Q_OBJECT
public:
    explicit Thread1(QObject *parent = 0, bool b = false);
     ~Thread1();
    Thread2 *tThread;

    void run();
    void pstop();
    void reset();
    void rewind(int searchvalueN);
    void forward(int searchvalueN);
    void meters();
    void play();
    //void valueChanged1(int searchvalueN);
    void terminateall();
    void exitslot();
    void restart_slot();
    int signalmeter(ECA_CONTROL_INTERFACE* ecas);

    //void recvalue_t8(int recv_t8N);



    void loop_device();

    //void csgetpos();

  typedef void (*action_func_t)(snd_seq_t *seq, snd_seq_client_info_t *cinfo, snd_seq_port_info_t *pinfo, int count);
   void alsaconnect();
   void alsadisconnect();


//   void list_subscribers(snd_seq_t *seq, const snd_seq_addr_t *addr);
//   void list_each_subs(snd_seq_t *seq, snd_seq_query_subscribe_t *subs, int type, const char *msg);
//   void check_permission(snd_seq_port_info_t *pinfo, int perm);

   //x-touch sends midi notes
//   void dump_event(const snd_seq_event_t *ev);
//   void aseqdump();
//   void check_snd(const char *operation, int err);

   //rx: x-touch receives midi notes (RX lights, fader movement)
//   void rxsend();
//   void rxplayon();
//   void rxplayoff();
   //void add_send_hex_data(const char *str);
   //void parse_data(void);
   //int hex_value(char c);
   //void rxvirtualclient();
   //void alsaconnectrx();
  // void rxpan1();
//   void rxpan2();
//   void rxpan3();
//   void rxpan4();
//   void rxpan5();
//   void rxpan6();
//   void rxpan7();
//   void rxpan8();
//   void rxfader1();
//   void rxfader2();
//   void rxfader3();
//   void rxfader4();
//   void rxfader5();
//   void rxfader6();
//   void rxfader7();
//   void rxfader8();

   //void recreadyledinit();
    //void recreadyled();
    //void effecttrack(int effecttrackNR);
     //void effectoff(int effecttrackNR);
     //void effectmainlim();

    //void readrestarttxt();
    //void readrecmodetxt();
    //void restartmodes();
    //void rectrackled();

    //void recmodesfile();
    //void tapesfile();
    //void activetapeLED();
    //void readtapeslottxt();
    //void deletetrack();
    //void maincounterfive();




    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;


private:
       //jack_client_t *client;


signals:

    //void T1(QString);
    void t1signal(int sendiT1);
    //void t1signal(QString T1);
    void t2signal(int sendiT2);
    void t3signal(int sendiT3);
    void t4signal(int sendiT4);
    void t5signal(int sendiT5);
    void t6signal(int sendiT6);
    void t7signal(int sendiT7);
    void t8signal(int sendiT8);

    void red1signal(QString redT1);
     void red2signal(QString redT2);
      void red3signal(QString redT3);
       void red4signal(QString redT4);

        void red5signal(QString redT5);
         void red6signal(QString redT6);
          void red7signal(QString redT7);
           void red8signal(QString redT8);

    void possignalmin(QString possmin);
    //void possignalsec(QString posssec);
    void jsignalrate(QString frateec);
    void midiinfo(QString sigmidiinfo);

    void floatsignalrate(float gxrate);

   //void jarsignal(QList<QString> sendjar);
    void jarsignal(QString sendjar);

    void enable1(bool);
      void enable2(bool);
        void enable3(bool);
          void enable4(bool);
            void enable5(bool);
              void enable6(bool);
                void enable7(bool);
                  void enable8(bool);

                   void enablerec(bool);
                   void enablenonrec(bool);

                   void ffclicked(int);
                    void rwclicked(int);
                     void stopclicked(int);
                      void playclicked(int);
                       void resetclicked(int);

    void lensignalmin(QString possmin);
     void lensignalsec(QString possec);     
     void stopsignal(int stoploop);
     void textoutput(QString);
     void exitvalue(int putexit);



    void buttonOkClickedSignal(QString var);

public slots:

private slots:
    //void valueGotStart(int timestartvalue);
    //void valueGotStop(int timestopvalue);
    void valueGotAseq(int aseqsignal2value);
    //void valueGotCC(int ccvalue);








};

#endif // THREAD1_H
