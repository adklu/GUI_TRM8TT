

//#include <jack/jack.h>
//#include <jack/transport.h>
//jack_client_t *client2;
//const char *client_name2;

#include "thread2.h"
#include "thread1.h"

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <sys/poll.h>
#include <string>
#include <cmath>

#include <cstdio>
#include <ctime>

#include <QDebug>
#include <QTimer>

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


#include <QProcess>



#include<iostream>
#include<ctime>

#include <QDir>

//#include <QMessageBox>

//#include <QTimer>

#include <QFile>

//sql removed for v80
//#include <QSqlDatabase>
//#include <QSqlDriver>
//#include <QSqlError>
//#include <QSqlQuery>

using namespace std;

static sig_atomic_t done = 0;

//#include "eca-control-interface.h"

int timestartvalue=0;
int timestopvalue=0;
int systemtime=1;
int stoploop;
int initialc=0;
int tapezero=0;
int tapeduration=0;
int playing=0;
//int ntt=0;

//#include <QThread>

//QTimer* timer2 = new QTimer();
//int ntt2 = 0;

//clock

// Declaring argument for time()
time_t tt;

// Declaring variable to store return value of
// localtime()
struct tm * ti;


//Thread2::Thread2(QObject *parent) : QObject(parent)
  Thread2::Thread2(QObject *parent, bool b) :
      QThread(parent), Stop(b)
{
      //for midi input
//      timer2->setInterval(300);
//      timer2->setSingleShot(false);
//      timer2->start(300);


}



void Thread2::run()

{


aseqtransport();




qDebug() << "_____________________--worker thread 2" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());



exec();

}





void Thread2::check_snd(const char *operation, int err)
{
    if (err < 0)
        qDebug() << "check_snd error" << operation << snd_strerror(err);

}



void Thread2::aseqtransport()
{

qDebug() << "_____________________--aseq  " << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());

    static snd_seq_t *seq;
    static int port_count;
    static snd_seq_addr_t *ports;

    int do_list = 0;
        struct pollfd *pfds;
        int npfds;
        int c;


//const char * port_name ;
char *buf, *s, *port_name;
   // char *buf, *s;
    int err;

        err = snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0);
        check_snd("open sequencer", err);

        qDebug() << "___222__________________--aseq  " << err;


        err = snd_seq_set_client_name(seq, "aseqtransport");
    check_snd("set client name", err);

    qDebug() << "___333__________________--aseq  " << err;


    //portname

    //port_name = "X-TOUCH COMPACT";
    QString qsenderv;
    QString HomePathT = QDir::homePath();
         QString controllerfilename = HomePathT + "/GUI_TRM8TT/trm8tt_controller.txt";

          qDebug() << "___444____controllerfilename______________--aseq  " << controllerfilename;

       //QFile hfile("trm8tt_controller.txt");
        QFile hfile(controllerfilename);
              if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
              {
                //emit midiinfo("Midi error (file)");
                  qDebug() << "___Midi error (file)______________--aseq  " << controllerfilename;
              }
              //
              else
              {
                  qDebug() << "___Midi error (file)___else___________--aseq  " << controllerfilename;


              QTextStream in(&hfile);

               qDebug() << "___Midi error (file)___else____222_______--aseq  " << controllerfilename;

                    //while (!in.atEnd())
                    //  {
                        qDebug() << "___while___________--aseq  " << controllerfilename;

                        QString hostrr = in.readLine();

                        if(~(hostrr.isEmpty()))
                             {
                         qDebug() << hostrr << "+++++++++++++++++string+++++++++++++++++++++++++in.readLine" ;
                         //qsenderv = hostrr;

                         //QString port_namestr = (tqueryrsf2ss.value(0).toString());
                          std::string sqsenderv = hostrr.toStdString();
                          const char * port_namecc   = sqsenderv.c_str();

                          port_name = strdup(port_namecc );

                            //const char * port_name  = sqsenderv.c_str();

                          //port_name = (queryrsf2ss.value(0).toString());
                        //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryrsf2.value(0).toString()) << "trackNRstring:" << trackNRstring;
                        qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << hostrr ;
                         qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << port_namecc;
                          qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << port_name;

                             }
                         if((hostrr.isEmpty())){
                            qDebug() << "___file empty___________--aseq  " << controllerfilename;
                        }
                 //      }


                    //--------
          //    }
           //     hfile.close();
                //----------


    //


//    QSqlQuery tqueryrsf2ss;
//            tqueryrsf2ss.exec("SELECT settingstext FROM settingstable WHERE settings = 'controller';");

//         if(!tqueryrsf2ss.isActive())
//                {
//                        qWarning() << "---------------------sql ERROR: " << tqueryrsf2ss.lastError().text();
//                }
//                if(tqueryrsf2ss.first())
//                {
//                   QString port_namestr = (tqueryrsf2ss.value(0).toString());
//                    std::string sqsenderv = port_namestr.toStdString();
//                    port_name  = sqsenderv.c_str();

//                      //const char * port_name  = sqsenderv.c_str();

//                    //port_name = (queryrsf2ss.value(0).toString());
//                  //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryrsf2.value(0).toString()) << "trackNRstring:" << trackNRstring;
//                  qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << port_namestr;
//                   qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << port_name;
//                    qDebug() << "port_name= -------+++++++++++++++++++++++++++++++++++++-------****************----------" << port_name;
//                }
//                else
//                {
//                  qDebug() << ("port_name data not found in db");
//                }


    //end portname

                qDebug() << "__pre---_buf port__________--aseq  ";

    buf = strdup(port_name);

    qDebug() << "___buf port__________--aseq  ";

    for (port_name = s = buf; s; port_name = s + 1)
    {

        s = strchr(port_name, ',');
        if (s)
            *s = '\0';

        ++port_count;

        ports = static_cast<snd_seq_addr_t*>(realloc(ports, port_count * sizeof(snd_seq_addr_t)));

        err = snd_seq_parse_address(seq, &ports[port_count - 1], port_name);
        if (err < 0)
                qDebug() << "Invalid port";
    }

    free(buf);

        err = snd_seq_create_simple_port(seq, "aseqtransport",
                         SND_SEQ_PORT_CAP_WRITE |
                         SND_SEQ_PORT_CAP_SUBS_WRITE,
                         SND_SEQ_PORT_TYPE_MIDI_GENERIC |
                         SND_SEQ_PORT_TYPE_APPLICATION);
    check_snd("create port", err);


    //create_port end

    //connect_ports

        int i;

        for (i = 0; i < port_count; ++i)
        {
            err = snd_seq_connect_from(seq, 0, ports[i].client, ports[i].port);
            if (err < 0)
                qDebug() << "snd_seq_connect_from error";

         }
     //connect_ports

        //main

        err = snd_seq_nonblock(seq, 1);
            check_snd("set nonblock mode", err);

            if (port_count > 0)
            {
                qDebug() << "Waiting for data... port_count > 0";
            }
            else
            {
                qDebug() << "Waiting for data... else port_count > 0" <<  snd_seq_client_id(seq);
            }


            npfds = snd_seq_poll_descriptors_count(seq, POLLIN);
                pfds = static_cast<pollfd*>(alloca(sizeof(*pfds) * npfds));



                for (;;)
                          {
                               usleep(300000);

                              snd_seq_poll_descriptors(seq, pfds, npfds, POLLIN);
                              if (poll(pfds, npfds, -1) < 0)
                              {
                             // qDebug() << " if (poll(pfds, npfds, -1) < 0)";
                              }
                              do {
                                  snd_seq_event_t *event;
                                  err = snd_seq_event_input(seq, &event);

                                if (err < 0)
                                {
                                    // qDebug() << "err < 0" << err < 0;
                                }

                                  if (event)
                                  {
                                      dump_event(event);
                                  }
                              } while (err > 0);

                              fflush(stdout);
                           }


      //------

              }
                hfile.close();



      //---------

}


void Thread2::dump_event(const snd_seq_event_t *ev)
{

    switch (ev->type)
    {
    case SND_SEQ_EVENT_NOTEON:
        if (ev->data.note.velocity)
        {
       qDebug() << ev->data.note.note;

        int bytex = ev->data.note.note;


        //



//        //activetape buttons of balance knobs
//        if (bytex == 0)
//                   {
//                 qDebug() << "activetape 0 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(0);
//                  }
//        if (bytex == 1)
//                   {
//                 qDebug() << "activetape 1 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(1);
//                  }
//        if (bytex == 2)
//                   {
//                 qDebug() << "activetape 2 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(2);
//                  }
//        if (bytex == 3)
//                   {
//                 qDebug() << "activetape 3 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(3);
//                  }
//        if (bytex == 4)
//                   {
//                 qDebug() << "activetape 4 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(4);
//                  }
//        if (bytex == 5)
//                   {
//                 qDebug() << "activetape 5 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(5);
//                  }
//        if (bytex == 6)
//                   {
//                 qDebug() << "activetape 6 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(6);
//                  }
//        if (bytex == 7)
//                   {
//                 qDebug() << "activetape 7 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(7);
//                  }

//         //buttons of knobs

//        if (bytex == 8)
//                   {
//                 qDebug() << "8 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(8);
//                  }

//        if (bytex == 9)
//                   {
//                 qDebug() << "9 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(9);
//                  }
//        if (bytex == 10)
//                   {
//                 qDebug() << "10 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(10);
//                  }
//        if (bytex == 11)
//                   {
//                 qDebug() << "11 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(11);
//                  }
//        if (bytex == 12)
//                   {
//                 qDebug() << "12 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(12);
//                  }
//        if (bytex == 13)
//                   {
//                 qDebug() << "13 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(13);
//                  }


//        if (bytex == 14)
//                   {
//                 qDebug() << "T2_14 reset searchvalue to 5 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(14);
//                  }
//        if (bytex == 15)
//                   {
//                 qDebug() << "T2_14 searchvalue + 10 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(15);
//                  }

//        //first row
//        if (bytex == 16)
//                   {
//                 qDebug() << "16 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(16);
//                  }
//        if (bytex == 17)
//                   {
//                 qDebug() << "17 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(17);
//                  }
//        if (bytex == 18)
//                   {
//                 qDebug() << "18  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(18);
//                  }
//        if (bytex == 19)
//                   {
//                 qDebug() << "19  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(19);
//                  }
//        //
//        if (bytex == 20)
//                   {
//                 qDebug() << "20  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(20);
//                  }
//        if (bytex == 21)
//                   {
//                 qDebug() << "21 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(21);
//                  }
//        if (bytex == 22)
//                   {
//                 qDebug() << "22  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(22);
//                  }
//        if (bytex == 23)
//                   {
//                 qDebug() << "23  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(23);
//                  }





//        //rec enable
//        if (bytex == 40)
//                   {
//                 qDebug() << "40 rec enable 1 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(40);
//                  }
//        if (bytex == 41)
//                   {
//                 qDebug() << "41 rec enable 2 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(41);
//                  }
//        if (bytex == 42)
//                   {
//                 qDebug() << "42 rec enable 3 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(42);
//                  }
//        if (bytex == 43)
//                   {
//                 qDebug() << "43 rec enable 4 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(43);
//                  }
//        if (bytex == 44)
//                   {
//                 qDebug() << "44 rec enable 5 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(44);
//                  }
//        if (bytex == 45)
//                   {
//                 qDebug() << "45 rec enable 6 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(45);
//                  }
//        if (bytex == 46)
//                   {
//                 qDebug() << "46 rec enable 7 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(46);
//                  }
//        if (bytex == 47)
//                   {
//                 qDebug() << "47 rec enable 8 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(47);
//                  }

//        if (bytex == 48)
//                   {
//                 qDebug() << "48 main button vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";

//                 emit aseqsignal2(48);
//                  }




        //transport

        if (bytex == 49)
                   {
                 qDebug() << "T2_49 RRvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                 //rewind(10);
                 emit aseqsignal2(49);
                  }

        if (bytex == 50)
                   {
                 qDebug() << "T2_50 FFvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                 //forward(10);
                 emit aseqsignal2(50);
                  }
        if (bytex == 51)
                   {
                 qDebug() << "T2_51 loopvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                 //reset();
                 emit aseqsignal2(51);
                  }
//        if (bytex == 52)
//                   {
//                 qDebug() << "T2_52 main recvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
//                 //reset();
//                 emit aseqsignal2(52);
//                  }
        if (bytex == 53)
                   {
                 qDebug() << "T2_53 STOPvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                // pstop();
                 emit aseqsignal2(53);
                  }
        if (bytex == 54)
                   {
                 qDebug() << "T2_54 PLAYvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
                 //csgetpos();
                 //play();
                 //emit possignalstop(0);
                 emit aseqsignal2(54);
                  }
        //
//        if (bytex == 55)
//                   {
//                 qDebug() << "55 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
//                 //csgetpos();
//                 //play();
//                 //emit possignalstop(0);
//                 emit aseqsignal2(55);
//                  }


   }
break;



//    case SND_SEQ_EVENT_CONTROLLER:
//    {

////           qDebug() << ev->data.control.channel;
////           qDebug() << ev->data.control.param;
////           qDebug() << ev->data.control.value;

//            int bytexccchannel = ev->data.control.channel;
//            int bytexccparam = ev->data.control.param;
//            int bytexccvalue = ev->data.control.value;

////            qDebug() << "ev->data.control.channel" << bytexccchannel;
////            qDebug() << "ev->data.control.param" << bytexccparam;
////            qDebug() << "ev->data.control.value" << bytexccvalue;

//            if((bytexccchannel==0)&&(bytexccparam==1))
//            {
//            emit ccaseqsignal(bytexccvalue);
//            }






//    }


    }

}


//aseqtransport end




Thread2::~Thread2()
{

    //ecas.command("engine-halt");
    //jack_client_close(client);
    //sleep(1);

//  quit();

//#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
//requestInterruption();
//#endif

//wait();
//sleep(1);

}


//++++++++++++++++++++++++++++++++++++++++++++++++

//timer blocks UI


//QTimer* timer = new QTimer();
//int ntt = 0;

//// for clock
// timer->setInterval(1000); //milliseconds
// timer->setSingleShot(false);
//     //timer->start(1000);
// connect(timer, &QTimer::timeout, this, [=]() mutable
// {
//int  rcsposimin;
//int rcsposisec;

////        ecas.command("cs-get-position");
////                      double cspos = ecas._float();
//                         ntt = ntt +1;
//                   int rcsposi = ntt;
//                   sleep(1);


//                   //int rcsposi = std::round(cspos);
//                    if(rcsposi>60)
//                    {
//                        rcsposimin = (std::round(rcsposi/60));
//                        rcsposisec = rcsposi - (rcsposimin * 60);
//                    }
//                    if(rcsposi<=60)
//                    {
//                        rcsposimin = 0;
//                        rcsposisec = rcsposi;
//                    }


//           qDebug() << rcsposimin << ":" << rcsposisec;


//           //gui-wip
//          QString posmin =  QString::number(rcsposimin);
//          QString possmin = "  " + posmin;
//          emit possignalmin(possmin);

//          QString possec =  QString::number(rcsposisec);
//          QString posssec = "  " + possec;
//          emit possignalsec(posssec);



////gui-wip
////if(timerLEDsOK==1)
////        {


////                add_send_hex_data("B0 19 05");
////                add_send_hex_data("B0 18 05");




////      //sec

////              if(rcsposisec>5)
////              {
////             add_send_hex_data("B0 29 01");
////              }
////              if(rcsposisec>10)
////              {
////             add_send_hex_data("B0 29 02");
////              }
////              if(rcsposisec>15)
////              {
////             add_send_hex_data("B0 29 03");
////              }
////              if(rcsposisec>20)
////              {
////             add_send_hex_data("B0 29 04");
////              }
////              //
////              if(rcsposisec>25)
////              {
////             add_send_hex_data("B0 29 05");
////              }
////              if(rcsposisec>30)
////              {
////             add_send_hex_data("B0 29 06");
////              }
////              if(rcsposisec>35)
////              {
////             add_send_hex_data("B0 29 07");
////              }
////              if(rcsposisec>40)
////              {
////             add_send_hex_data("B0 29 08");
////              }
////              //
////              if(rcsposisec>45)
////              {
////             add_send_hex_data("B0 29 09");
////              }
////              if(rcsposisec>50)
////              {
////             add_send_hex_data("B0 29 0A");
////              }
////              if(rcsposisec>55)
////              {
////             add_send_hex_data("B0 29 0B");
////              }
////              if(rcsposisec>58)
////              {
////             add_send_hex_data("B0 29 0C");
////              }

//////min
////                                         if(rcsposimin>0)
////                                         {
////                                        add_send_hex_data("B0 28 01");
////                                         }
////                                         if(rcsposimin>1)
////                                         {
////                                        add_send_hex_data("B0 28 02");
////                                         }
////                                         if(rcsposimin>2)
////                                         {
////                                        add_send_hex_data("B0 28 03");
////                                         }
////                                         if(rcsposimin>3)
////                                         {
////                                        add_send_hex_data("B0 28 04");
////                                         }
////                                         //
////                                         if(rcsposimin>4)
////                                         {
////                                        add_send_hex_data("B0 28 05");
////                                         }
////                                         if(rcsposimin>5)
////                                         {
////                                        add_send_hex_data("B0 28 06");
////                                         }
////                                         if(rcsposimin>6)
////                                         {
////                                        add_send_hex_data("B0 28 07");
////                                         }
////                                         if(rcsposimin>7)
////                                         {
////                                        add_send_hex_data("B0 28 08");
////                                         }
////                                         //
////                                         if(rcsposimin>8)
////                                         {
////                                        add_send_hex_data("B0 28 09");
////                                         }
////                                         if(rcsposimin>9)
////                                         {
////                                        add_send_hex_data("B0 28 0A");
////                                         }
////                                         if(rcsposimin>10)
////                                         {
////                                        add_send_hex_data("B0 28 0B");
////                                         }
////                                         if(rcsposimin>11)
////                                         {
////                                        add_send_hex_data("B0 28 0C");
////                                         }



//// }

// });






