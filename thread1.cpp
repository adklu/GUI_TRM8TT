

/*
 * GUI_TRM8TT - Professional 8 Track Audio Recorder for Midi CC Controllers
 *
 * Copyright (c) 2020 A.D.Klumpp
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */



//Required:
//Debian 9/10
//Qt5, qt5-default, build-essential
//ALSA
//libasound2-dev
//libasound2
//Jack
//libjack-dev or libjack-jackd2-dev
//Ecasound
//Midi CC controller for 8 tracks (e.g. Behringer XTouchCompact)
//Audio Interface for Linux

//qt style with gtk/gnome://
//sudo apt install qt5-style-plugins
//echo "export QT_QPA_PLATFORMTHEME=gtk2" >> ~/.profile



//Assigment of set of 8 CC faders/knobs to volumne or balance:
//To map volumne faders:
//Create inside of the folder with the executable file a file with the name "vol_map", open the file
//enter the first midi CC number (e.g. "1"), save and close the file (now midi CC 1 to 8 are assigned as volumne faders).

//To map panning knobs:
//Create inside of the folder with the executable file a file with the name "pan_map", open the file
//enter the first midi CC number (e.g. "10"), save and close the file (now midi CC 10 to 18 are assigned as panning knobs).

//If no vol_map or pan_map are inside of the folder, the following values are used:
int vol_map = 1;
int pan_map = 10;
//(= Behringer XTouchCompact Layer A)


//"Transport": Permanent assigment of midi notes
//<<: 49
//>>: 50
//RTZ: 51
//STOP: 53
//>:54
//(= Behringer XTouchCompact default settings)

//--------------------------------------------------------
//bug fixes
//v103
//fixed: crash when pressing stop, >>, <<, RTZ before pressing start
//v102
//removed while (! in  QTextStream
//v80
//sqlite replaced by txt db
//added to readme: required: qt5-default, build-essential
//v0077
//incorrect midi error message with: snd_seq_get_port_subscription(seq, subs) == 0
//v0074:
//paused fader crash
//spam button crash
//empty folder playback/stop crash

//--------------------------------------------------------
//removed from X_GNU_TRM8TT:
//master track removed, filter 'master' to enable it
    //with master track use system-01
    //ecas.command("ao-add jack,system-01");
//deletetrack();
//activetapeNR
//recmode
//readrecmodetxt
//void rxvirtualclient();
//void alsaconnectrx();
//timer->
//tThread = new Thread2(this);
//---
//readrecmodetxt(
//recmodesfile(
//tapesfile(
//readtapeslottxt(
//++++
//restartmodes(
//activetapeLED(
//effectmainlim(
//effecttrack(
//effectoff(
//valueGotStop(
//valueGotStart(
//startstoploop(
//++++++++++
//removed
// effecttrack(4);
//compressor/limiter
//[- hardware/software monitor switch]



int midierrorinput = 0;

int nospammidi = 0;

int stopspammcbox = 0;

int nospamalsaconnect = 0;

//int activetapeNR=1;

int noinputcombobox=0;



//int recmode=0;
//int recmode2counter=0;
int deletepre1=0;
int deletepre2=0;
int deletepre3=0;

int trackNRRecLED1=0;
int trackNRRecLED2=0;

int RecLED1counter=0;
int RecLED2counter=0;

int timerLEDsOK=0;



//sql removed for v80
//#include <QSqlDatabase>
//#include <QSqlDriver>
//#include <QSqlError>
//#include <QSqlQuery>

#include <QDateTime>
#include "thread1.h"
#include <QDebug>
#include <QString>
//#include <QMutex>
#include <eca-control-interface.h>
#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

//#include <QStandardPaths>
#include <QDir>

#include <QMessageBox>

#include <QTimer>

#include <QFile>

#include <QByteArray>


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

#include <jack/statistics.h>


#include <jack/jack.h>
#include <jack/transport.h>
//#include <jack/metadata.h>
//#include <jack/session.h>

//>>signal
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <cassert>
#include <cmath>
#include <cstdio>

#include <ctime>

#include <signal.h>
#include <unistd.h>


#include <sys/time.h>     /* POSIX: select() */
#include <sys/select.h>   /* POSIX: timeval struct */

#include "kvu_numtostr.h"

#include "eca-control-interface.h"

#include "ecicpp_helpers.h"


#include <cstring>




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

//#include <thread>
//#include <mutex>
//#include <condition_variable>

     QList<QString> jackportsAr;

QString activetape=NULL;
QString HomePathT = QDir::homePath();
//QString TapesPath = HomePathT + "/" + "TRM8TT_Tape";



//QString activetape = HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_1";

//int track1_rec = 0;
//int track2_rec = 0;
//int track3_rec = 0;
//int track4_rec = 0;
//int track5_rec = 0;
//int track6_rec = 0;
//int track7_rec = 0;
//int track8_rec = 0;

QString getdbLine1="";
QString getdbLine2="";
QString getdbLine3="";
QString getdbLine4="";
QString getdbLine5="";
QString getdbLine6="";
QString getdbLine7="";
QString getdbLine8="";



std::vector<int> emptytracksar;

int emptytracks;


int oneemptytrack=0;

int track_rec[] = {0, 0, 0, 0, 0, 0, 0, 0};
int maxrectracks = 0;
int mainrec = 0;
int twotracks = 0;
int reconly1track = 0;
int only1 = 0;

int togglerec = 0;
int toggleeffect1 = 0;
int toggleeffect2 = 0;
int toggleeffect3 = 0;
int toggleeffect4 = 0;
int toggleeffect5 = 0;
int toggleeffect6 = 0;
int toggleeffect7 = 0;
int toggleeffect8 = 0;

int toggleeffect11 = 0;
int toggleeffect22 = 0;
int toggleeffect33 = 0;
int toggleeffect44 = 0;
int toggleeffect55 = 0;
int toggleeffect66 = 0;
int toggleeffect77 = 0;
int toggleeffect88 = 0;

int toggleeffect111 = 0;
int toggleeffect222 = 0;
int toggleeffect333 = 0;
int toggleeffect444 = 0;
int toggleeffect555 = 0;
int toggleeffect666 = 0;
int toggleeffect777 = 0;
int toggleeffect888 = 0;


int toggleeffect9 = 0;


int rec1counter = 0;
int rec2counter = 0;
int rec3counter = 0;
int rec4counter = 0;
int rec5counter = 0;
int rec6counter = 0;
int rec7counter = 0;
int rec8counter = 0;

int maincounter = 0;

int restart1 = 0;
int restart2 = 0;
int restart3 = 0;
int restart4 = 0;
int restart5 = 0;
int restart6 = 0;
int restart7 = 0;
int restart8 = 0;


 snd_seq_t *seq;

int searchvalueN = 3;

char resultport[100];
//const char *  rxconnect;

static char *send_hex;
static char *send_data;
static int send_data_length;

static snd_rawmidi_t *input, **inputp;
static snd_rawmidi_t *output, **outputp;

//end ALSA

using namespace std;

//set channel number
static int ecasv_chcount = 8;
//signalmeter
static sig_atomic_t done = 0;



//  jack_port_t*  ecaMasterIN_1;
//   jack_port_t*  ecaMasterIN_2;
//    jack_port_t*  ecaMasterOUT_1;
//     jack_port_t*  ecaMasterOUT_2;



QProcess process1;
QProcess process2;


ECA_CONTROL_INTERFACE ecas;


jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;
jack_client_t *mclient;

    const char **ports;
    const char *client_name;
    const char *mclient_name;

    jack_options_t options = JackNullOption;
    jack_options_t moptions = JackNullOption;
    jack_status_t status;
      jack_status_t mstatus;


    QString qserver_name = "default";
    std::string qtserver_name = qserver_name.toStdString();
    const char * server_name = qtserver_name.c_str();

    QString mqserver_name = "mdefault";
    std::string mqtserver_name = mqserver_name.toStdString();
    const char * mserver_name = mqtserver_name.c_str();



int quitnumber = 0;

int timepointer = 0;


//clock
//QTimer* timer = new QTimer();
//int ntt = 0;

//QTimer* timer2 = new QTimer();
//int ntt2 = 0;

//QTimer* timer3 = new QTimer();
//int ntt3 = 0;


//


Thread1::Thread1(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{




    //

    //readtapeslottxt();

//removed because of gui:
    tThread = new Thread2(this);

     //in line 2866 tThread->start();

    //connect(tThread,SIGNAL(possignalstart(int)), this, SLOT(valueGotStart(int)));
    //connect(tThread,SIGNAL(possignalstop(int)), this, SLOT(valueGotStop(int)));
    //connect(this,SIGNAL(stopsignal(int)), tThread, SLOT(startstoploop(int)));

    connect(tThread,SIGNAL(aseqsignal2(int)), this, SLOT(valueGotAseq(int)));

     //connect(tThread,SIGNAL(ccaseqsignal(int)), this, SLOT(valueGotCC(int)));





qDebug() << "__%%%%%%%%%%%%%%%%%%%%%%%%%%%___________________--thread 1 before timer" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());


//    //for midi input
//    timer2->setInterval(300);
//    timer2->setSingleShot(false);
//    timer2->start(300);

    //for vu meter
//    timer3->setInterval(80);
//    timer3->setSingleShot(false);
//    timer3->start(80);


//timer was here, but in same thread as mainwindow...

    //++++++connect to Jack+++++

//    if (m_pJackClient)
//            stopJack();
//        else
//    startJack();
//++++++++++++++++++++
//   QString acommand = "gnome-terminal -x bash -c \"jackd -R -d alsa -d hw:Audio -r 44100 -p 512";
//   qDebug() << acommand;
//   process2.start(acommand);


//sleep(1);

    QString qclient_name = "ecasound";
    std::string qtclient_name = qclient_name.toStdString();
    const char * client_name = qtclient_name.c_str();



    client = jack_client_open (client_name, options, &status, server_name);
       qDebug() << "client";
       qDebug() << client;
       qDebug() << client_name;


       //

//       QString mqclient_name = "ecaMaster";
//       std::string mqtclient_name = mqclient_name.toStdString();
//       const char * mclient_name = mqtclient_name.c_str();



//       mclient = jack_client_open (mclient_name, moptions, &mstatus, mserver_name);
//          qDebug() << "mclient";
//          qDebug() << mclient;
//          qDebug() << mclient_name;



//        ecaMasterIN_1 = jack_port_register 	(mclient,"ecaMasterIN_1",JACK_DEFAULT_AUDIO_TYPE,JackPortIsInput,2);
//          ecaMasterIN_2 = jack_port_register 	(mclient,"ecaMasterIN_2",JACK_DEFAULT_AUDIO_TYPE,JackPortIsInput,2);

//            ecaMasterOUT_1 = jack_port_register 	(mclient,"ecaMasterOUT_1",JACK_DEFAULT_AUDIO_TYPE,JackPortIsOutput,2);
//              ecaMasterOUT_2 = jack_port_register 	(mclient,"ecaMasterOUT_2",JACK_DEFAULT_AUDIO_TYPE,JackPortIsOutput,2);


//              if (jack_activate (mclient)) {
//                      qDebug() << "---------------------------------------cannot activate client";

//                  }



//              if (jack_activate (client)) {
//                      qDebug() << "---------------------------------------cannot activate client";

//                  }


       //

        if (client == NULL)
        {
               qDebug() << "client == NULL";
        }

        if (status & JackServerStarted)
        {
             qDebug() << "JACK server started";
        }

        if (status & JackNameNotUnique)
        {
           client_name = jack_get_client_name(client);
            qDebug() << "TRM8TT/ecasound engine already running. Please close TRM8TT/ecasound and kill all running instances of ecasound before restarting.";
            qDebug() << client_name;

         quitnumber = quitnumber +1;



//            QMessageBox msgBox;
//               msgBox.setText("TRM8TT/ecasound engine already running. Please close TRM8TT/ecasound and kill all running instances of ecasound before restarting.");
//               msgBox.exec();

         }


        qDebug() << "client_name3";
        qDebug() << client_name;



   sleep(1);

//alsaconnect();





}

//void Thread1::valueGotStart(int timestartvalue)
//{

//// effecttrack(4);
//    //                //turn off all fan lights
//                   // add_send_hex_data("B0 28 00");
//                   //  add_send_hex_data("B0 29 00");
//    qDebug() << "timestartvalue" << timestartvalue;

//    //timepointer = timevalue;

//    //add_send_hex_data("B0 29 01");

//    if (timestartvalue > 5)
//    {
//   add_send_hex_data("B0 29 01");
//    }

//    if (timestartvalue > 10)
//    {
//   add_send_hex_data("B0 29 02");
//    }

//    if (timestartvalue > 15)
//    {
//   add_send_hex_data("B0 29 03");
//   qDebug() << "signal received..................................";
//    }

//    //


//}


//void Thread1::valueGotCC(int ccvalue)
//{
//     qDebug() << "cccccccccccccccccccccccccccccc ccvalue received" << ccvalue;

////     ecas.command("cs-select play_chainsetup");



////            ecas.command("c-select chain1");
////            ecas.command("cop-select 3");
////               //ecas.command("ctrl-select 1");

////            //cop 3: ea to control the volume
////             //gui-wip changed ea from 0 to 90
////            //ecas.command("cop-set -ea:50");


////                 QString rqfai_addo = "cop-set -ea:" + QString::number(ccvalue);
////                   QString rqfai_add = rqfai_addo;
////                   QString rfstr = rqfai_add;
////                   std::string rfstdstr = rfstr.toStdString();
////                   const char * rfcstr = rfstdstr.c_str();
////                   qDebug() << "rfcstr" << qPrintable(rfcstr);
////                   //ecas.command("cop-select 3");
////                   //ecas.command("ctrl-add -km:1,0,180,1,1");
////                   ecas.command(rfcstr);
//}





//  connect(tThread,SIGNAL(aseqsignal2(int)), this, SLOT(valueGotAseq(int)));
void Thread1::valueGotAseq(int aseqsignal2value)
{


//    if (aseqsignal2value == 8)
//    {
//     qDebug() << "cccccccccccccccccccccccccccccc 8 received";
//     deletepre1=1;
//    }

//    if (aseqsignal2value == 9)
//    {
//     qDebug() << "cccccccccccccccccccccccccccccc 9 received";
//     deletepre2=1;
//    }
//    if (aseqsignal2value == 10)
//    {
//     qDebug() << "cccccccccccccccccccccccccccccc 10 received";
//     if(timerLEDsOK==1)
//     {
////         ecas.command("c-select chainMaster");
////         ecas.command("cop-set ’1,1,0’");
////         sleep(1);
//         ecas.command("c-select chain1");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain2");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain3");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain4");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain5");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain6");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain7");
//         ecas.command("cop-set ’3,1,0’");
//         sleep(1);
//         ecas.command("c-select chain8");
//         ecas.command("cop-set ’3,1,0’");

//         add_send_hex_data("B0 24 1C");

//         sleep(2);

//          add_send_hex_data("B0 24 00");



//          qDebug() << "ea reset";
//     }

//    }



////     if (toggleeffect9==0)
////      {
////      //effectmainlim();
////      //toggleeffect9=toggleeffect9+1;
////     }
////      else
////     {
////      //effectoff(4);
////     }






////top row, delete track
//    if (aseqsignal2value == 16)
//    {
//     qDebug() << "11cccccccccccccccccccccccccccccccccccccccc 16 received";
//     recmode=11;
//     deletepre3=1;
//     restartmodes();


//    }
//    if (aseqsignal2value == 17)
//    {
//     qDebug() << "12cccccccccccccccccccccccccccccccccccccccc 17 received";


//    recmode=12;
//     deletepre3=1;
//     restartmodes();

//    }
//    if (aseqsignal2value == 18)
//    {
//     qDebug() << "13ccccccccccccccccccccccccccccccccccccccccr 18 received";
//         recmode=13;
//          deletepre3=1;
//          restartmodes();

//    }
//    if (aseqsignal2value == 19)
//    {
//     qDebug() << "14ccccccc444cccccccccccccccccccccccccccccccccr 19 received";
//         recmode=14;
//          deletepre3=1;
//          restartmodes();



//    }
//    //
//    if (aseqsignal2value == 20)
//    {
//     qDebug() << "15ccccccc444cccccccccccccccccccccccccccccccccr 20 received";
//         recmode=15;
//          deletepre3=1;
//          restartmodes();


//    }
//    //
//    if (aseqsignal2value == 21)
//    {
//     qDebug() << "16ccccccc444cccccccccccccccccccccccccccccccccr 21 received";
//         recmode=16;
//          deletepre3=1;
//          restartmodes();



//    }
//    //
//    if (aseqsignal2value == 22)
//    {
//     qDebug() << "17ccccccc444cccccccccccccccccccccccccccccccccr 22 received";
//         recmode=17;
//          deletepre3=1;
//          restartmodes();



//    }
//    //

//    //

//    if (aseqsignal2value == 23)
//    {
//     qDebug() << "18ccccccc444cccccccccccccccccccccccccccccccccr 23 received";
//         recmode=18;
//          deletepre3=1;
//          restartmodes();


//    }


//    transport
//    RW: 49
//    FF: 50
//    RTZ: 51
//    STOP: 53
//    PLAY:54





    if (aseqsignal2value == 54)
    {
    //play();
     emit playclicked(500);

//    if((recmode==1)||(recmode==2))
//    {
//        rectrackled();
//        add_send_hex_data("90 24 02");

//    }
    }

    if (aseqsignal2value == 53)
    {
    //pstop();
    mainrec = 0;
     emit stopclicked(500);


    }

    if (aseqsignal2value == 49)
    {
    //rewind(10);
    //rewind(searchvalueN);
        emit rwclicked(500);

    }

    if (aseqsignal2value == 50)
    {
    //forward(10);
    //forward(searchvalueN);
     emit ffclicked(500);
    }

    if (aseqsignal2value == 51)
    {
    //reset();
    emit resetclicked(500);
    }


    //
//    if (aseqsignal2value == 14)
//    {
//searchvalueN=3;
//qDebug() << "searchvalueN=3" << searchvalueN;
//    }

//    if (aseqsignal2value == 15)
//    {
//searchvalueN=searchvalueN+10;
//qDebug() << "searchvalueN=searchvalueN+10" << searchvalueN;
//    }

//    //main rec
//    if (aseqsignal2value == 52)
//    {
//        if(togglerec==0)
//        {

//              if(recmode==0)
//              {
//                  activetapeLED();
//                  recreadyled();
//              }

//              if((recmode==1)||(recmode==2))
//              {
//                  rectrackled();
//                  activetapeLED();
//                  sleep(1);
//                   add_send_hex_data("90 24 02");

//              }

//    togglerec=togglerec+1;
//        }
//        else
//        {



//            if(recmode==0)
//            {
//            //all rec leds off
//                  add_send_hex_data("90 18 01");
//                  add_send_hex_data("90 19 01");
//                  add_send_hex_data("90 1A 01");
//                  add_send_hex_data("90 1B 01");
//                  add_send_hex_data("90 1C 01");
//                  add_send_hex_data("90 1D 01");
//                  add_send_hex_data("90 1E 01");
//                  add_send_hex_data("90 1F 01");

//                 // rec led
//                  add_send_hex_data("90 24 01");

//                  //tape slot led off
//                  add_send_hex_data("B0 1A 07");
//                    add_send_hex_data("B0 1B 07");
//                      add_send_hex_data("B0 1C 07");
//                        add_send_hex_data("B0 1D 07");
//                          add_send_hex_data("B0 1E 07");
//                            add_send_hex_data("B0 1F 07");
//                              add_send_hex_data("B0 20 07");
//                                add_send_hex_data("B0 21 07");


//                }

//            else if((recmode==1)||(recmode==2))
//            {
//                rectrackled();



//                //tape slot led off
//                add_send_hex_data("B0 1A 07");
//                  add_send_hex_data("B0 1B 07");
//                    add_send_hex_data("B0 1C 07");
//                      add_send_hex_data("B0 1D 07");
//                        add_send_hex_data("B0 1E 07");
//                          add_send_hex_data("B0 1F 07");
//                            add_send_hex_data("B0 20 07");
//                              add_send_hex_data("B0 21 07");
//                              sleep(1);
//                               add_send_hex_data("90 24 02");

//            }


//                  togglerec=0;


//        }
//    //mainrec  = 1;
//    //only1 = 0 ;
//    //recreadyledinit();
//    }


//    //activetape

//    //enable one channel recordings
//    if (aseqsignal2value == 40)
//    {
//        //rec1counter = rec1counter + 1;
//         maincounter = 1;

//          qDebug() << "------------------40----------------------rec1counter" <<  maincounter;

//          recmode=1;

//          restartmodes();



//    }

//    //enable 2 channel recordings
//    if (aseqsignal2value == 41)
//    {
//        //rec1counter = rec1counter + 1;
//         maincounter = 1;

//          qDebug() << "------------------41----------------------rec2counter" <<  maincounter;

//          recmode=2;

//          restartmodes();

//    }

//    //main button
//    if (aseqsignal2value == 48)
//    {
//        //maincounter = maincounter + 1;
//         maincounter =1;


//         recmode=0;

//          qDebug() << "-------------------48---------------------maincounter" << maincounter;

//          restartmodes();
//    }



//    if (aseqsignal2value == 0)
//    {
//activetapeNR=1;
//        restart1=1;

//         qDebug() << "-------------------0 knob----------------restart1=1";

//         restartmodes();

////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_1";
//    }





//    //
//    if (aseqsignal2value == 1)
//    {
//        activetapeNR=2;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_2";
//    }

//    if (aseqsignal2value == 2)
//    {
//        activetapeNR=3;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_3";
//    }

//    if (aseqsignal2value == 3)
//    {
//        activetapeNR=4;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_4";
//    }

//    if (aseqsignal2value == 4)
//    {
//        activetapeNR=5;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_5";
//    }

//    if (aseqsignal2value == 5)
//    {
//        activetapeNR=6;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_6";
//    }

//    if (aseqsignal2value == 6)
//    {
//        activetapeNR=7;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_7";
//    }

//    if (aseqsignal2value == 7)
//    {
//        activetapeNR=8;
//               restart1=1;
//               restartmodes();
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_8";
//    }
//    //
//    if (aseqsignal2value == 55)
//    {
//         //deletetrack();
//         qDebug() << "55 received";
////activetape=HomePathT + "/" + "TRM8TT_Tapes" + "/" + "TRM8TT_Tape_8";
//    }




}





void Thread1::play()

{

    nospamalsaconnect=nospamalsaconnect+1;

    qDebug() << "nospamalsaconnect" << nospamalsaconnect;

      //gui-wip
 //emit stopsignal(0);



     //int timepointerplay=timepointer;

     //qDebug() << "timepointerplay" << timepointerplay;


    //tThread->start();
    //QString Tx = "emit from worker test";
//emit t1signal(Tx);
    //QString acommand = "gnome-terminal -x bash -c \"/usr/bin/qjackctl";    
    // process1.start(acommand);

    if(nospamalsaconnect<2)
    {

alsaconnect();

      client_name = jack_get_client_name(client);

       //qDebug() << "client_namePlay";
       //qDebug() << client_name;

  //gui-wip

          //ecas.command("engine-launch");

      jack_transport_start(client);
       qDebug() << client;

    }

// ecas.command("cs-select play_chainsetup");



//        ecas.command("c-select chain1");
//        ecas.command("cop-select 3");
//           //ecas.command("ctrl-select 1");

//        //cop 3: ea to control the volume
//         //gui-wip changed ea from 0 to 90
//        ecas.command("cop-set -ea:50");


//            ecas.command("ctrl-add -km:1,0,180,1,1");






//            ecas.command("ctrlp-select 1");
//            ecas.command("ctrlp-set 1");
//            ecas.command("ctrlp-select 2");
//            ecas.command("ctrlp-set 0");
//            ecas.command("ctrlp-select 3");
//            ecas.command("ctrlp-set 180");
//            ecas.command("ctrlp-select 4");
//            ecas.command("ctrlp-set 1");
//            ecas.command("ctrlp-select 5");
//            ecas.command("ctrlp-set 1");


//                 ecas.command("ctrl-status");
//                 cerr << "ctrl- status: " << ecas.last_string() << endl;




//           ecas.command("ctrl-remove");
//           ecas.command("ctrl-add -km:1,0,180,1,1");


//              //cop-set ’chainop_id,param_id,value’

//               ecas.command("cop-set ’5,3,0’");


//               //ea (faders)
//               //vol_map = 1
//              // int volchan = vol_map - 1 + trackNR;
//             QString rqfai_addo = "ctrl-remove -km:1,0,180,1,1";
//               //QString qfai_addo = "ctrl-add -km:1,0,180," + QString::number(volchan) + ",1";
//               QString rqfai_add = rqfai_addo;
//               QString rfstr = rqfai_add;
//               std::string rfstdstr = rfstr.toStdString();
//               const char * rfcstr = rfstdstr.c_str();
//               qDebug() << "rfcstr" << qPrintable(rfcstr);
//               ecas.command("cop-select 3");
//               //ecas.command("ctrl-add -km:1,0,180,1,1");
//               ecas.command(fcstr);




//                       //ea (faders)
//                       //vol_map = 1
//                      // int volchan = vol_map - 1 + trackNR;
//                     QString qfai_addo = "ctrl-add -km:1,0,180,1,1";
//                       //QString qfai_addo = "ctrl-add -km:1,0,180," + QString::number(volchan) + ",1";
//                       QString qfai_add = qfai_addo;
//                       QString fstr = qfai_add;
//                       std::string fstdstr = fstr.toStdString();
//                       const char * fcstr = fstdstr.c_str();
//                       qDebug() << "fcstr" << qPrintable(fcstr);
//                       ecas.command("cop-select 3");
//                       //ecas.command("ctrl-add -km:1,0,180,1,1");
//                       ecas.command(fcstr);





//           ecas.command("cs-get-position");
//              double cspos = ecas.last_float();

//                         qDebug() << "cspos%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
//                          qDebug() << cspos;

//gui-wip
//rxplayon();



           //gui-wip
//timer->start(1000);




}

void Thread1::meters()

{
   // QString bcommand = "gnome-terminal -x bash -c \"jmeters -t din -c 2 L R";

      // process1.start(bcommand);

     //  jack_port_by_name(client);
      // ecas.command("jack-connect ’ecasound-01:out_1’ ’jmeters:in-1’");
     //  ecas.command("jack-connect ’src-port’ ’dest-port’");

//system:playback_1
//system:playback_2
//ecasound-01:out_1
//ecasound-01:out_2
//ecasound-03:out_1
//ecasound-03:out_2
//jmeters:in-1
//jmeters:in-2

//---------------------------

    //jack_connect

        // to list all clients:
         //jack_lsp

      //   jack_connect "TRM8TT:Track_1_1" "jack_mixer:1 L"


        ports = jack_get_ports (client, NULL, NULL,JackPortIsOutput);

             qDebug() << "eca ports--------------------------";
             qDebug() << ports;

        jack_client_t *mclient;

            const char **mports;
            //const char *mclient_name;

        QString qmclient_name = "jack_mixer";
        std::string qmtclient_name = qmclient_name.toStdString();
        const char * mclient_name = qmtclient_name.c_str();



        mclient = jack_client_open (mclient_name, options, &status, server_name);
           qDebug() << "mclient";
           qDebug() << mclient;
           qDebug() << mclient_name;

            mports = jack_get_ports (mclient, NULL, NULL,JackPortIsInput);

            qDebug() << "jack mixer ports--------------------------";
            qDebug() << mports;

    //*************************************




    //+++++ARRAY+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //for array
    //                                const QByteArray client_port1
    //                                    = QString(node1->nodeName() + ':' + port1->portName()).toUtf8();
    //                                const QByteArray client_port2
    //                                    = QString(node2->nodeName() + ':' + port2->portName()).toUtf8();

    //                                const char *client_port_name1 = client_port1.constData();
    //                                const char *client_port_name2 = client_port2.constData();

    //end for array
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


                                    const char **client_ports1
                                        = ::jack_get_ports(client, NULL, NULL, 0);
                                    if (client_ports1 == NULL)
                                        return;
                                    //
//                                       const char **client_ports1sh    = ::jack_port_short_name(client);
//                                       if (client_ports1 == NULL)
//                                           return;


                                    qDebug() << "client_ports1";

                                     qDebug() << client_ports1;

//                                     qDebug() << "client_ports1sh";

//                                      qDebug() << client_ports1sh;

                                     for (int i = 0; client_ports1[i]; ++i)
                                     {
                                         const char *client_port1 = client_ports1[i];
                                         jack_port_t *jack_port1 = ::jack_port_by_name(client, client_port1);

                                         qDebug() << "client_port1";

                                          qDebug() << client_port1;

                                          //

//                                          const char *client_port1sh = client_ports1sh[i];
//                                          //jack_port_t *jack_port1sh = ::jack_port_by_name(client, client_port1sh);

//                                          qDebug() << "client_port1sh";

//                                           qDebug() << client_port1sh;

















                                         if (jack_port1 == NULL)
                                             continue;

      //++++++other port

      const char **client_ports2 = ::jack_port_get_all_connections(client, jack_port1);
    qDebug() << "client_ports2";
    qDebug() << client_ports2;



    //                                     for (int j = 0; client_ports2[j]; ++j)
    //                                     {
    //                                         const char *client_port2 = client_ports2[j];


    //                                         qDebug() << "client_port2";

    //                                         qDebug() << client_port2;

    //                                     }




                                     }



    //"jack_mixer:1 L";


    //"TRM8TT:Track_1_1";

//collect ports in prop down lists... so user can connect them...


QString qclient_port_name1a= "TRM8TT:Track_1_1";
std::string qtclient_port_name1a = qclient_port_name1a.toStdString();
 const char * client_port_name1a = qtclient_port_name1a.c_str();

 QString qclient_port_name1b= "jack_mixer:1 L";
 std::string qtclient_port_name1b = qclient_port_name1b.toStdString();
  const char * client_port_name1b = qtclient_port_name1b.c_str();


 //jack_connect(client, client_port_name1a, client_port_name1b);


 //to do: jack_disconnect...

     //multiport end







}

void Thread1::loop_device()

{
    ecas.command("c-add loopdevice_chain");
     ecas.command("c-select loopdevice_chain");

     ecas.command("ai-add loop,1");
     //ecas.command("ao-add jack,system");

     //cop_pmeter();

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//alsaconnect



//deleted alsa outtake


//alsadisconnect()++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




void Thread1::alsadisconnect()
{

    nospammidi=nospammidi+1;
      qDebug() << "nospammidi" << nospammidi;

    if((midierrorinput==0)&&(nospammidi<2))
    {


                    qDebug() << "inside";

 QString qsenderv;
 QString HomePathT = QDir::homePath();
      QString controllerfilename = HomePathT + "/GUI_TRM8TT/trm8tt_controller.txt";

    //QFile hfile("trm8tt_controller.txt");
     QFile hfile(controllerfilename);
           if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
           {
             emit midiinfo("Midi error (file)");
           }
           //
           else
           {
           QTextStream in(&hfile);
                 //while (!in.atEnd())
                  // {
                     QString hostrr = in.readLine();

                     if(~(hostrr.isEmpty()))
                          {
                      qDebug() << hostrr << "+++++++++++++++++string+++++++++++++++++++++++++in.readLine" ;
                      qsenderv = hostrr;

                          }
                   // }
           }
             hfile.close();



             std::string sqsenderv = qsenderv.toStdString();
              const char * senderv  = sqsenderv.c_str();


    snd_seq_port_subscribe_t *subs;
snd_seq_addr_t sender, dest;


const char destv  [16] ="ecasound";



//do_search_port(seq, list_perm,list_subs ? print_port_and_subs : print_port);


int perm;



    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;




    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);
    snd_seq_client_info_set_client(cinfo, -1);
    //--



    qDebug() << "alsadisconnect 1";





snd_seq_parse_address(seq, &sender, senderv);
snd_seq_parse_address(seq, &dest, destv);

snd_seq_port_subscribe_alloca(&subs);
snd_seq_port_subscribe_get_sender(subs);
snd_seq_port_subscribe_get_dest(subs);


    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);





snd_seq_unsubscribe_port(seq, subs);

if (snd_seq_get_port_subscription(seq, subs) < 0)
        {
            snd_seq_close(seq);
            emit midiinfo("Midi: Paused");
            return;
        }
if (snd_seq_unsubscribe_port(seq, subs) < 0)
        {
            snd_seq_close(seq);
            emit midiinfo("Midi: Disconnection failed");
            return;
        }


    }




}


//++++++alsaconnect()++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



void Thread1::alsaconnect()
{

    nospammidi=0;

 QString qsenderv;
 QString HomePathT = QDir::homePath();
      QString controllerfilename = HomePathT + "/GUI_TRM8TT/trm8tt_controller.txt";

    //QFile hfile("trm8tt_controller.txt");
     QFile hfile(controllerfilename);
           if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
           {
             emit midiinfo("Midi error (saved controller)");
           }
           //
           else
           {
           QTextStream in(&hfile);
                 //while (!in.atEnd())
                   //{
                     QString hostrr = in.readLine();

                     if(~(hostrr.isEmpty()))
                          {
                      qDebug() << hostrr << "+++++++++++++++++string+++++++++++++++++++++++++in.readLine" ;
                      qsenderv = hostrr;

                          }
                    //}
           }
             hfile.close();
//sql
//                  QSqlQuery query2mcon;
//                          query2mcon.exec("SELECT settingstext FROM settingstable WHERE id = 2");
//                 if(!query2mcon.isActive())
//                         qWarning() << "------trm8tt_controller---------------sql ERROR: " << query2mcon.lastError().text();

//                 if(query2mcon.first())
//                 {
//                   qDebug() << "sql output ----trm8tt_controller--------------------" << (query2mcon.value(0).toString());
//                 qsenderv = (query2mcon.value(0).toString());
//                 }

//                 else
//                   qDebug() << ("trm8tt_controller data not found in db");



//


             std::string sqsenderv = qsenderv.toStdString();
              const char * senderv  = sqsenderv.c_str();

  //  snd_seq_t *seq;

    if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0) < 0)
    {
            fprintf(stderr, ("can't open sequencer\n"));
            emit midiinfo("Midi error (ALSA)");
            return;
    }



    int queue = 0, convert_time = 0, convert_real = 0, exclusive = 0;
//    int command = SUBSCRIBE;

    snd_seq_port_subscribe_t *subs;
snd_seq_addr_t sender, dest;

//const char senderv  [16] = "X-TOUCH COMPACT";
//const char senderv  [32] = "Arturia BeatStep Pro";
//const char destv  [16] ="ecasound";
const char destv  [16] ="ecasound";



//do_search_port(seq, list_perm,list_subs ? print_port_and_subs : print_port);


int perm;



    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;




    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);
    snd_seq_client_info_set_client(cinfo, -1);
    //--



    qDebug() << "alsaconnect 1";



//check_permission(pinfo, perm);



    if (snd_seq_set_client_name(seq, "ALSA Connector") < 0)
    {
        snd_seq_close(seq);

        emit midiinfo("Midi error (ALSA)");
        return;
}


      if (snd_seq_parse_address(seq, &sender, senderv) < 0)
      {
          snd_seq_close(seq);

           emit midiinfo("Midi error (input)");
          midierrorinput = 1;
          return;
      }
      if (snd_seq_parse_address(seq, &dest, destv) < 0)
      {
          snd_seq_close(seq);

          emit midiinfo("Playback error");
          return;
      }
      //
      if (snd_seq_parse_address(seq, &sender, senderv) == 0)
      {
            midierrorinput = 0;
           qDebug() << "valid Midi sender address:" << senderv;
             emit midiinfo(senderv);


      }
        if (snd_seq_parse_address(seq, &dest, destv) == 0)
        {

             qDebug() << "valid Midi destination address:" << destv;

        }




    snd_seq_port_subscribe_alloca(&subs);

    snd_seq_port_subscribe_set_sender(subs, &sender);
    snd_seq_port_subscribe_set_dest(subs, &dest);
    snd_seq_port_subscribe_set_queue(subs, queue);
    snd_seq_port_subscribe_set_exclusive(subs, exclusive);
    snd_seq_port_subscribe_set_time_update(subs, convert_time);
    snd_seq_port_subscribe_set_time_real(subs, convert_real);

    if (snd_seq_get_port_subscription(seq, subs) == 0)
            {
//                snd_seq_close(seq);

//                emit midiinfo("Midi error (connection)");
//                return;

                qDebug() << "snd_seq_get_port_subscription(seq, subs) == 0";

            }
            if (snd_seq_subscribe_port(seq, subs) < 0)
            {
//                snd_seq_close(seq);

//                emit midiinfo("Midi error");
//                return;

                 qDebug() << "snd_seq_subscribe_port(seq, subs) < 0";



             }



    //qDebug() << snd_seq_port_info_get_addr(pinfo);

}








void Thread1::run()
{

emptytracks=0;

int res;

qDebug() << "_____________________--worker thread 1" << reinterpret_cast<std::uintptr_t>(thread()->currentThreadId());

qDebug() << "QDir::homePath() from thread1" << HomePathT;

//-------v80-------------------


QString qsenderv;


QString HomePathT = QDir::homePath();
     QString tapeslotfilename = HomePathT + "/GUI_TRM8TT/trm8tt_tapeslot.txt";

      qDebug() << "___ts444____tapeslotfilename____________  " << tapeslotfilename;


    QFile hfile(tapeslotfilename);


          if (!hfile.open(QIODevice::ReadOnly | QIODevice::Text))
          {

              qDebug() << "___ error (file)____________ " << tapeslotfilename;
          }


          else
          {
              qDebug() << "___  (file)___else____ts______  " << tapeslotfilename;


          QTextStream in(&hfile);

           qDebug() << "__ (file)___else____ts222______  " << tapeslotfilename;



                    qDebug() << "___w____ts______ " << tapeslotfilename;


                    QString hostrr = in.readLine();

                    if(~(hostrr.isEmpty()))
                         {
                     qDebug() << hostrr << "+++++++ts++++++++++string+++++++++++++++++++++++++in.readLine" ;



                      std::string sqsenderv = hostrr.toStdString();
                      const char * port_namecc   = sqsenderv.c_str();

                      activetape = strdup(port_namecc );


                    qDebug() << "activetape= -------++ts+++++++++++++++++++++++++++++++++++-------****************----------" << activetape ;


                         }
                     if((hostrr.isEmpty()))
                   {
                        qDebug() << "___file empty_________ts " << tapeslotfilename;
                    }


                }

//--------------v80 replace sqlite by txt


            QString txtdbnamepath = activetape +"/db.txt";

                           QFile rhfile80(txtdbnamepath);

                               if (!rhfile80.open(QIODevice::ReadOnly | QIODevice::Text))
                               {

//                                   QMessageBox msgBox;
//                                   msgBox.setText("Tape missing. Please select a tape folder.");
//                                   msgBox.exec();

                                    qDebug() << "..........meta info....db.txt.........!hfile.open...  activetapeNR 1";
                               }
                               //
                               else
                               {
                               QTextStream rin(&rhfile80);





                                    //while (!rin.atEnd())
                                        for(int i=1; i<9; i++)
                                       {
                                         QString rhostrr = rin.readLine();


                                         qDebug() << rhostrr << "+++++++++++++++++line number+++++++++++++in.readLine:  " << i ;


                                         if(~(rhostrr.isEmpty()))
                                              {
                                          qDebug() << rhostrr << "++++++not+++empty line++++++++string+1++++++activetapeST++++++++++++++++++in.readLine" << i;
                                 if(i==1)
                                 {
                                     getdbLine1=rhostrr;

                                      qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==2)
                                 {
                                     getdbLine2=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==3)
                                 {
                                     getdbLine3=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==4)
                                 {
                                     getdbLine4=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==5)
                                 {
                                     getdbLine5=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==6)
                                 {
                                     getdbLine6=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==7)
                                 {
                                     getdbLine7=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                 }

                                 if(i==8)
                                 {
                                     getdbLine8=rhostrr;
                                     qDebug() << rhostrr << " getdbLine " << i;
                                     qDebug() <<getdbLine8 << "+++++getdbLine8 not+++empty line++++++++string+1++++++activetapeST++++++++++++++++++in.readLine" << i;
                                 }




                                              }




                                         else
                                         {
//                                             QMessageBox msgBox;
//                                             msgBox.setText("Tape missing. Please select a tape folder.");
//                                             msgBox.exec();
                                             qDebug() << "............meta info....db.txt.......!hfile.empty...  activetapeNR 1";
                                         }
                                        }
                               }
                                rhfile80.close();




//---------------------------
//v80 removed sqlite

//const QString DRIVER("QSQLITE");
 //QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);


//  QString dbnamepath = activetape +"/trm8tt_db";

//       //db.setDatabaseName("trm8tt_db");
//           db.setDatabaseName(dbnamepath);

//       if(!db.open())
//       {
//         qWarning() << "SQLite ERROR: " << db.lastError();
//        }






//----------------------------

//QSqlQuery queryrsf2ss;
//        queryrsf2ss.exec("SELECT settingstext FROM settingstable WHERE settings = 'folder';");

//     if(!queryrsf2ss.isActive())
//            {
//                    qWarning() << "---------------------sql ERROR: " << queryrsf2ss.lastError().text();
//            }
//            if(queryrsf2ss.first())
//            {
//                activetape = (queryrsf2ss.value(0).toString());
//              //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryrsf2.value(0).toString()) << "trackNRstring:" << trackNRstring;
//              qDebug() << "activetape= --------------****************----------" << activetape;
//            }
//            else
//            {
//              qDebug() << ("activetape data not found in db");
//            }


//--------------------------


   QDir dir(activetape);
   if (!dir.exists())
       dir.mkpath(activetape);

qDebug() << "activetape#####################################################################" << activetape;

if(activetape==NULL)
{

}

//set midi map


//vol (default 1)
QString vol_mapPath = HomePathT + "/GUI_TRM8TT/vol_map";

        //QDir dir(TapesPath);
         QDir dir_home(HomePathT);


            if (dir_home.exists(vol_mapPath))
            {
          qDebug() << " vol_map file in folder 00000000000%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";


                      QFile vhfile(vol_mapPath);
                            if (!vhfile.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                              vol_map = 1;
                            }
                            //
                            else
                            {
                            QTextStream in(&vhfile);
                                  //while (!in.atEnd())
                                   // {
                                      QString vhostrr = in.readLine();

                                      if(~(vhostrr.isEmpty()))
                                           {

                                       vol_map = vhostrr.toInt();
                                       qDebug() << vhostrr << "+++++vol_mapPath++not empty++++++++++string+++++++++++++++++++++++++in.readLine" << vol_map;



                                           }


                                    // }
                            }
                              vhfile.close();
                 }

            if (!dir_home.exists(vol_mapPath))
            {
            vol_map = 1;

            qDebug() << "no vol_map file %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";



            }
//pan_map (default 10)
            QString pan_mapPath = HomePathT + "/GUI_TRM8TT/pan_map";

                    //QDir dir(TapesPath);
                     QDir pdir_home(HomePathT);


                        if (pdir_home.exists(pan_mapPath))
                        {
                      qDebug() << " pan_mapfile in folder 00000000000%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";


                                  QFile pvhfile(pan_mapPath);
                                        if (!pvhfile.open(QIODevice::ReadOnly | QIODevice::Text))
                                        {
                                          pan_map = 10;
                                        }
                                        //
                                        else
                                        {
                                        QTextStream in(&pvhfile);
                                              //while (!in.atEnd())
                                               // {
                                                  QString pvhostrr = in.readLine();

                                                  if(~(pvhostrr.isEmpty()))
                                                       {

                                                   pan_map = pvhostrr.toInt();
                                                   qDebug() << pvhostrr << "+++++pan_mapPath++not empty++++++++++string+++++++++++++++++++++++++in.readLine" << pan_map;



                                                       }


                                                 //}
                                        }
                                          pvhfile.close();
                             }

                        if (!dir_home.exists(pan_mapPath))
                        {
                        pan_map = 10;

                        qDebug() << "no pan _map file %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<  pan_map ;



                        }


//+++++++ecasound++++++++++++

    ecas.command("engine-launch");
    //ecas.command("engine-status");

    ecas.command("cs-add play_chainsetup");


    //wip v110
    //ecas.command("cs-set-audio-format ’24,2,’");

   ecas.command("cs-set-param -G:jack,system,recv");




//master chain
// ecas.command("c-add chainMaster");
// ecas.command("c-select chainMaster");
// ecas.command("ao-add jack,system");
// ecas.command("ai-add jack,xMaster,xMasterIN");

// //cop 1 (master vol.):
// //gui-wip changed ea from 0 to 90
//  ecas.command("cop-add -ea:90");

// //cop 2 (master peak signal):
//  ecas.command("cop-add -evp");

// //cop 3 master limiter:
//   //ecas.command("cop-add -eal:80");

//  //master volumne control:
//   ecas.command("cop-select 1");
//   ecas.command("ctrl-add -km:1,0,100,9,1");




//stereo mix
//CC midi map for X-TOUCH COMPACT
    for(int trackNR=1;trackNR<=8;trackNR++)
    {
        //QString TapeName =  TapesPath + "/TRM8TT_Track_" + QString::number(trackNR) + ".wav";
        QString TrackName = activetape + "/Track_" + QString::number(trackNR) + ".wav";

                //QDir dir(TapesPath);
                 QDir dir(activetape);





//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //play ready
 //if (dir.exists(TapeName))
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

                    if (dir.exists(TrackName))
                {
                    qDebug() << TrackName << "does exist";

                    //wip v110
                         //ecas.command("-f:24,2,");
                    //ecas.command("-f:s24_le,2,44100,i");




                    QString qcai_addo = "c-add chain" + QString::number(trackNR);
                    QString qcai_add = qcai_addo;
                    QString strc = qcai_add;
                    std::string stdstrc = strc.toStdString();
                    const char * cstrc = stdstrc.c_str();
                    qDebug() << "cstrc" << qPrintable(cstrc);
                    //ecas.command("c-add chain1");
                    ecas.command(cstrc);

                    QString qcsai_addo = "c-select chain" + QString::number(trackNR);
                    QString qcsai_add = qcsai_addo;
                    QString strcs = qcsai_add;
                    std::string stdstrcs = strcs.toStdString();
                    const char * cstrcs = stdstrcs.c_str();
                    qDebug() << "cstrcs" << qPrintable(cstrcs);
                    //ecas.command("c-select chain1");
                    ecas.command(cstrcs);


           //wip v110
                   //ecas.command("-f:24,2,");
                    //ecas.command("cop-add -chcopy:1,2");

                     ecas.command("ao-add jack,system");

                     //v110
                     ecas.command("-f:24,2,");


                    //with master track use system-01
                      //ecas.command("ao-add jack,system-01");



                    //QString qai_addo = "ai-add " + TapeName;
                    QString qai_addo = "ai-add " + TrackName;

                    QString qai_add = qai_addo;
                    QString str = qai_add;
                    std::string stdstr = str.toStdString();
                    const char * cstr = stdstr.c_str();
                    //qDebug() << "ai-add" << qPrintable(cstr);
                    ecas.command(cstr);

                    //chcopy to get mono file ready for epp panning
                    ecas.command(cstrcs);

//cop 1
                    //cop 1 (to pan mono in the middle)
                    ecas.command("cop-add -chcopy:1,2");
                     ecas.command(cstrcs);

//                     //[old cop 2] (pan):
//                    ecas.command("cop-add -epp:50");
//cop 2
                    //[old cop 3]:
                     //ea to control the volume
                    //new 2
                     //gui-wip changed ea from 0 to 90
                    ecas.command("cop-add -ea:50");
//cop 3
                    //[old cop 4]:
                    //evp for signal meter (after ea)
                    //new 3
                    ecas.command("cop-add -evp");

//cop 4
                     //------------[--old---cop 2]
                    //(pan):
                     //new 4
                    ecas.command("cop-add -epp:50");

                    //



                    //cop 5: reverb -ete:room_size,feedback-%,wet-%
                    //ecas.command("cop-add -ete:50,25,0");
                    //-efl:cutoff-freq
                    //ecas.command("-efl:20000");


                    //cop 5: limiter (number not called)
                    //ecas.command("cop-add -eal:98");



                    //epp (pan)
                    //pan_map = 10;
                    //int panchan = 9 + trackNR;
                    int panchan = pan_map - 1 + trackNR;
                    qDebug() << "panchan" << panchan;
                    QString qpfai_addo = "ctrl-add -km:1,0,100," + QString::number(panchan) + ",1";
                    QString qpfai_add = qpfai_addo;
                    QString pfstr = qpfai_add;
                    std::string pfstdstr = pfstr.toStdString();
                    const char * pfcstr = pfstdstr.c_str();
                    qDebug() << "pfcstr" << qPrintable(pfcstr);
                    //ecas.command("cop-select 2");
                    //new 4
                    ecas.command("cop-select 4");
                    //ecas.command("ctrl-add -km:1,0,100,10,1");
                    ecas.command(pfcstr);

                    //ea (faders)
                    //vol_map = 1
                    int volchan = vol_map - 1 + trackNR;
                    //QString qfai_addo = "ctrl-add -km:1,0,180," + QString::number(trackNR) + ",1";
                    QString qfai_addo = "ctrl-add -km:1,0,180," + QString::number(volchan) + ",1";
                    QString qfai_add = qfai_addo;
                    QString fstr = qfai_add;
                    std::string fstdstr = fstr.toStdString();
                    const char * fcstr = fstdstr.c_str();
                    qDebug() << "fcstr" << qPrintable(fcstr);
                    //ecas.command("cop-select 3");
                    //new 2
                    ecas.command("cop-select 2");
                    //ecas.command("ctrl-add -km:1,0,180,1,1");
                    ecas.command(fcstr);


                    //

//                    //reverb knobs
//                    //QString rqfai_addo = "ctrl-add -km:3,0,100," + QString::number(trackNR+17) + ",1";
//                    //QString rqfai_addo = "ctrl-add -km:3,0,100," + QString::number(trackNR+36) + ",1";
//                    //low pass filter
//                    //QString rqfai_addo = "ctrl-add -km:1,0,10000," + QString::number(trackNR+36) + ",1";
//                    QString rqfai_add = rqfai_addo;
//                    QString rfstr = rqfai_add;
//                    std::string rfstdstr = rfstr.toStdString();
//                    const char * rfcstr = rfstdstr.c_str();
//                    qDebug() << "fcstr" << qPrintable(rfcstr);
//                    ecas.command("cop-select 5");
//                    //ecas.command("ctrl-add -km:1,0,180,1,1");
//                    //ecas.command(rfcstr);







                   // ecas.command("cop-select 5");
                   // ecas.command("ctrl-add -km:1,0,150,18,1");

                    //-km:fx-param,start-value,end-value,controller,channel
                    //-ete:room_size,feedback-%,wet-%


                }







//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//rec ready
//if ((!dir.exists(TapeName))&&reconly1track<1)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



                   if (!dir.exists(TrackName))

                {

                       emptytracks=emptytracks+1;


qDebug() << TrackName << "does not exist, emptytracks:" << emptytracks;

//1: check file if track is already marked as rec ready,
                       //if any track is marked as 1 = rec mode
                       //if all tracks are 0 (or empty) = playback mode





//2: if yes (at least one track has a saved check box in file: '1'),
                       //add rec track
                       //jack capture 1,2,3... drop down... get input

                       //meters();


//


                           //

                             const char **client_ports1 = ::jack_get_ports(client, NULL, NULL, 0);
                                                               if (client_ports1 == NULL)
                                                                   return;
                                                               //
                           //                                       const char **client_ports1sh    = ::jack_port_short_name(client);
                           //                                       if (client_ports1 == NULL)
                           //                                           return;


                                                               //qDebug() << "client_ports1";

                                                                //qDebug() << client_ports1;

                           //                                     qDebug() << "client_ports1sh";

                           //                                      qDebug() << client_ports1sh;

                                        if (stopspammcbox==0)
                                        {

                                                                for (int i = 0; client_ports1[i]; ++i)
                                                                {
                                                                    const char *client_port1 = client_ports1[i];
                                                                    jack_port_t *jack_port1 = ::jack_port_by_name(client, client_port1);

                                                                   // qDebug() << "client_port1" << i;

                                                                    // qDebug() << client_port1;

                                                                     QString qclient_port1 = client_port1;

                                                                      //qDebug() << qclient_port1  << "qclient_port1";

                                                                      emit jarsignal (qclient_port1);


                                                                                    jackportsAr.append(client_port1);


                                                                 }
                                           }

                                        stopspammcbox=stopspammcbox+1;


                       //

                        //qDebug() << jackportsAr;



                       //end 2





//3: if no (all tracks are '0' in file),
   //mark track as empty and rec ready (button green), buttons of playback tracks inactive

//set buttons, comboboxes active, when track is empty/rec ready

                       if(trackNR==1)
                       {


                           emit enable1(true);

                       }

                       if(trackNR==2)
                       {


                           emit enable2(true);

                       }

                       if(trackNR==3)
                       {


                           emit enable3(true);

                       }

                       if(trackNR==4)
                       {


                           emit enable4(true);

                       }

                       if(trackNR==5)
                       {


                           emit enable5(true);

                       }

                       if(trackNR==6)
                       {

                           emit enable6(true);

                       }

                       if(trackNR==7)
                       {


                           emit enable7(true);

                       }

                       if(trackNR==8)
                       {


                           emit enable8(true);

                       }





//++++++++++++end buttons

 //get rectrack and input from sqlite

//v80 change to txt db

        QString inputsstring;
        QString recvaluestring;

                       if((trackNR==1)&&(getdbLine1!=""))
                       {

                        recvaluestring="1";
                         qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==2)&&(getdbLine2!=""))
                       {
                         recvaluestring="1";
                        qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==3)&&(getdbLine3!=""))
                       {
                         recvaluestring="1";
                         qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==4)&&(getdbLine4!=""))
                       {
                          recvaluestring="1";
                         qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }


                       if((trackNR==5)&&(getdbLine5!=""))
                       {
                         recvaluestring="1";
                          qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==6)&&(getdbLine6!=""))
                       {
                         recvaluestring="1";
                          qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==7)&&(getdbLine7!=""))
                       {
                         recvaluestring="1";
                          qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }

                       if((trackNR==8)&&(getdbLine8!=""))
                       {
                         recvaluestring="1";
                          qDebug() << "  recvaluestring=1 " << trackNR  ;
                       }




//v80 sqlite replaced by txt.db




//trackNR

//QString trackNRstring = QString::fromStdString(std::to_string(trackNR));

//        ////read sql
//             QSqlQuery queryr2;
//             queryr2.exec("SELECT recvalue FROM tracktable WHERE tracknumber = '" + trackNRstring + "';");




//            if(!queryr2.isActive())
//            {
//                    qWarning() << "------SELECT recvalue FROM tracktable WHERE tracknumber ---------------sql ERROR: " << queryr2.lastError().text();
//            }
//            if(queryr2.first())
//            {
//                recvaluestring = (queryr2.value(0).toString());
//              //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
//              qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << recvaluestring << "trackNRstring:" << trackNRstring;
//            }
//            else
//            {
//              qDebug() << ("track data not found in db");
//            }



//**********************************REC***************************************************
//if track is empty and marked as recordready, get input selection and prepare rec-chain:

if(recvaluestring=="1")
{

    noinputcombobox=1;

   // qDebug() <<  recvaluestring << trackNRstring << "///////////////////////////////////////////////////ready to record";
       qDebug() <<  recvaluestring << trackNR << "///////////////////////////////////////////////////ready to record";


//input


//    QSqlQuery queryr3;
//    queryr3.exec("SELECT inputs FROM tracktable WHERE tracknumber = '" + trackNRstring + "';");




//   if(!queryr3.isActive())
//   {
//           qWarning() << "---------------------sql ERROR: " << queryr3.lastError().text();
//   }
//   if(queryr3.first())
//   {
//       inputsstring = (queryr3.value(0).toString());
//     //qDebug() << "sql output SELECT recvalue FROM tracktable WHERE tracknumber = ------------------------" << (queryr2.value(0).toString()) << "trackNRstring:" << trackNRstring;
//     qDebug() << "sql output SELECT inputs FROM tracktable WHERE tracknumber = ------------------------" << inputsstring << "trackNRstring:" << trackNRstring;
//   }
//   else
//   {
//     qDebug() << ("track data not found in db");
//   }


//   write inputsstring on top of track in red



//   v80 replaced by txt db

   if(trackNR==1)
   {
inputsstring=getdbLine1;
   emit red1signal(inputsstring);


   }

   if(trackNR==2)
   {

inputsstring=getdbLine2;
        emit red2signal(inputsstring);

   }

   if(trackNR==3)
   {

inputsstring=getdbLine3;
       emit red3signal(inputsstring);

   }

   if(trackNR==4)
   {

inputsstring=getdbLine4;
        emit red4signal(inputsstring);
   }

   if(trackNR==5)
   {

inputsstring=getdbLine5;
       emit red5signal(inputsstring);

   }

   if(trackNR==6)
   {
inputsstring=getdbLine6;
     emit red6signal(inputsstring);

   }

   if(trackNR==7)
   {

inputsstring=getdbLine7;
      emit red7signal(inputsstring);

   }

   if(trackNR==8)
   {

inputsstring=getdbLine8;
     emit red8signal(inputsstring);

   }









 QString qcai_addo = "c-add chain" + QString::number(trackNR);
 QString qcai_add = qcai_addo;
 QString strc = qcai_add;
 std::string stdstrc = strc.toStdString();
 const char * cstrc = stdstrc.c_str();
 qDebug() << "cstrc" << qPrintable(cstrc);
 //ecas.command("c-add chain1");
 ecas.command(cstrc);

 QString qcsai_addo = "c-select chain" + QString::number(trackNR);
 QString qcsai_add = qcsai_addo;
 QString strcs = qcsai_add;
 std::string stdstrcs = strcs.toStdString();
 const char * cstrcs = stdstrcs.c_str();
 qDebug() << "cstrcs" << qPrintable(cstrcs);
 //ecas.command("c-select chain1");
ecas.command(cstrcs);

// -f:24,1, will creat the mono file with 24 bit, but the panning for all tracks after the rec track is locked on the left channel, if not removed after
ecas.command("-f:24,1,");

// ecas.command("ai-add jack,capture_1");
QString aiaddjack = "ai-add jack," + inputsstring;
QString jqcsai_add = aiaddjack;
QString jstrcs = jqcsai_add;
std::string jstdstrcs = jstrcs.toStdString();
const char * jcstrcs = jstdstrcs.c_str();
qDebug() << "jcstrcs" << qPrintable(jcstrcs);
//ecas.command("c-select chain1");
ecas.command(jcstrcs);





 QString qai_addo = "ao-add " + TrackName;
 QString qai_add = qai_addo;
 QString str = qai_add;
 std::string stdstr = str.toStdString();
 const char * cstr = stdstr.c_str();
 qDebug() << "ao-add" << qPrintable(cstr);
ecas.command(cstr);

// v110 added to avoid panning to left channel for the following playback channels
ecas.command("-f:24,2,");

//software monitoring
//ecas.command("ao-add jack,system");

//hardware monitoring
//ecas.command("ao-add null");



//cop 1
         //chcopy to get mono file ready for epp panning
         ecas.command("cop-add -chcopy:1,2");

//cop 2
         //ea to control the volume
         ecas.command("cop-add -ea:50");

//cop 3
         //evp for signal meter (after ea)
         ecas.command("cop-add -evp");

//cop 4

         //pan
         ecas.command("cop-add -epp:50");


 //epp (pan)
   int panchan = pan_map - 1 + trackNR;
 qDebug() << "panchan" << panchan;
 QString qpfai_addo = "ctrl-add -km:1,0,100," + QString::number(panchan) + ",1";
 QString qpfai_add = qpfai_addo;
 QString pfstr = qpfai_add;
 std::string pfstdstr = pfstr.toStdString();
 const char * pfcstr = pfstdstr.c_str();
 qDebug() << "pfcstr" << qPrintable(pfcstr);
 ecas.command("cop-select 4");
 ecas.command(pfcstr);


 //ea (faders)
 int volchan = vol_map - 1 + trackNR;
   QString qfai_addo = "ctrl-add -km:1,0,180," + QString::number(volchan) + ",1";
 QString qfai_add = qfai_addo;
 QString fstr = qfai_add;
 std::string fstdstr = fstr.toStdString();
 const char * fcstr = fstdstr.c_str();
 qDebug() << "fcstr" << qPrintable(fcstr);
 ecas.command("cop-select 2");
 ecas.command(fcstr);




//end of if(recvaluestring=="1")
}


    }

 }





//disable input selection when in rec mode
if(noinputcombobox==1)
{
    emit enable1(false);
    emit enable2(false);
    emit enable3(false);
    emit enable4(false);

    emit enable5(false);
    emit enable6(false);
    emit enable7(false);
    emit enable8(false);

     emit enablerec(false);

}

if(noinputcombobox==0)
{

     emit enablenonrec(false);

}









//+++++++++++CONNECT TO midi cc controller for -ea control
             sleep(1);

             //ecas.command("cs-option -Md:alsaseq,'X-TOUCH COMPACT'");

             ecas.command("cs-option -Md:alsaseq,'ecasound'");


             sleep(1);

//++++++++++++++status
                //ecas.command("ctrl-list");
                //ecas.command("ctrl-status");

                //cerr << "Chain ctrl status: " << ecas.last_string() << endl;

                ecas.command("cs-status");

                cerr << "cs status: " << ecas.last_string() << endl;

                //ecas.command("cop-list");
                //ecas.command("cop-status");

                //cerr << "Chain operator status: " << ecas.last_string() << endl;

//+++++++++++++++++++++++++++++++++++
//OUTPUT
//++++++++++++++++++++++++++++++++++++

//for stereo mix:
    //c-select 'cname1,...,cnameN'
    //ecas.command("c-select-all");
    //ecas.command("ao-add jack,system");


    //todo: peak meter (max. only) for stereo master
    // ecas.command("ao-add jack");
    //ecas.command("ao-add loop,1");
    // ecas.command("ao-add jack_multi,playback_1");
    //stereo master track with -ea via loop,1 chain9
    //jack,system
    //jack (excluding jack connections)
    //jack_multi,destport1,...,destportN
    //(number of channels is set with -f:bits,channels,rate
    //https://manpages.debian.org/jessie/ecasound/ecasound.1.en.html

//stereo mix end++++++++++++++++++++++++++



  ecas.command("cs-connect");
  ecas.command("start");
  ecas.command("cs-set-position 0");



// alsaconnect() and aseqtransport() for midi controll

  //gui-wip
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //+++alsaconnect(++here it will crash the faders, when used when trasnport is stopped++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   //alsaconnect();
     //sleep(1);
     //
    // tThread->start();







          jack_transport_locate(client,0);


        tThread->start();
           //jack_transport_start(client);



//framerate
float xrate;


if (client)
              {
                    jack_position_t tpos;
                    jack_transport_query(client, &tpos);
                    xrate = float(tpos.frame_rate);


                    //v106
                    emit floatsignalrate(xrate);



                          QString fratec =  QString::number(xrate);
                          QString frateec = "  " + fratec + " Hz";
                         emit jsignalrate(frateec);


//+++++++++++++++++++++++++++++++++++++
//signalmeter frequency=100000 microsec
//+++++++++++++++++++++++++++++++++++++



     while(! done )
     {
        usleep(100000);


         res = signalmeter(&ecas);

         //
        // if (client)
                 // {
                      jack_position_t tpos;
                      jack_transport_query(client, &tpos);
                      //float xrate = float(tpos.frame_rate);
                      float xtloc = (float(tpos.frame) / xrate);
                 //qDebug() << "jack_transport_query---------------float xrate-----------" << xrate;
                 // qDebug() << "jack_transport_query--------------float xtloc------------" << xtloc;


                  //min-sec

                 // int  rcsposimin;
//                  int rcsposisec;

                  float rcsposimin;



//                                      if(xtloc>60)
//                                      {
//                                          rcsposimin = (std::round(xtloc/60));
//                                          rcsposisec = xtloc - (rcsposimin * 60);




//                                      }
//                                      if(xtloc<=60)
//                                      {
//                                          rcsposimin = 0;
//                                          rcsposisec = xtloc;
//                                      }



                                        rcsposimin = xtloc/60;


                            // qDebug() << rcsposimin << ":" << rcsposisec;


                             //gui-wip
                            QString posmin =  QString::number(rcsposimin);
                            QString possmin = "  " + posmin;
                            emit possignalmin(possmin);

//                            QString possec =  QString::number(rcsposisec);
//                            QString posssec = "  " + possec;
//                            emit possignalsec(posssec);


            //      }
         //


       if (res < 0)
         {
           qDebug() << "res < 0";
         }


     }
}



//-----v80
//db.close();

//-------


exec();

//}  end of: else (deletetrack...
}









//peak meter


int Thread1::signalmeter(ECA_CONTROL_INTERFACE* eci)
{
  int result = 0;



      //master
//  for(int cn = 1; cn < 3; cn++)

//       {



//     eci->command("c-select chainMaster");
//     eci->command("cop-select 2");


////     //--
////     QString crqcsai_addo = "copp-select " + QString::number(cn);
////     QString crqcsai_add = crqcsai_addo;
////     QString crstrcs = crqcsai_add;
////     std::string crstdstrcs = crstrcs.toStdString();
////     const char * crcstrcs = crstdstrcs.c_str();
////     //qDebug() << "crcstrcs" << qPrintable(crcstrcs);

////   ecas.command(crcstrcs);


//     //--
//    // eci->command("copp-select 1");


//     eci->command("copp-select " + kvu_numtostr(cn));
//     eci->command("copp-get");

//     if (eci->error())
//     {
//       result = -1;
//       break;
//     }

//     double mvalue = eci->last_float();



//     if(mvalue>=0.95)
//        {
//  //qDebug() << "--------------------------------------mvalue "   <<   mvalue   ;
//         //add_send_hex_data("90 20 02");

//        }

//     if(mvalue<0.93)
//     {
//  //add_send_hex_data("90 20 01");
//        }


//}
     //end master



     for(int n = 0; n < ecasv_chcount; n++)

          {

      //chain select n1 - n8, copp id static
     // eci->command("c-select chain1");

     //<<<<<<<<<<<<<<<<<replace with QString::number(trackNR) and remove kvu

      eci->command("c-select chain" + kvu_numtostr(n + 1));
      //before ea: eci->command("cop-select 1");
      //eci->command("cop-select 4");
      //new3
      eci->command("cop-select 3");




      eci->command("copp-select 1");
    //eci->command("copp-select " + kvu_numtostr(n + 1));
    eci->command("copp-get");

    if (eci->error())
    {
      result = -1;
      break;
    }

    double value = eci->last_float();

  //qDebug() << n << "vu value++++++++++++++++++++++++++" << value;

    if(n==0)
    {
    int iT1=  value*100;
    //QString T1=  QString::number(iT1);
    emit t1signal(iT1);
    }

    if(n==1)
    {
    int iT2=  value*100;
    //QString T2=  QString::number(iT2);
    emit t2signal(iT2);
    }

    if(n==2)
    {
    int iT3=  value*100;
    //QString T3=  QString::number(iT3);
    emit t3signal(iT3);
    }

    if(n==3)
    {
    int iT4=  value*100;
    //QString T4=  QString::number(iT4);
    emit t4signal(iT4);
    }

    //

    if(n==4)
    {
    int iT5=  value*100;
    //QString T4=  QString::number(iT4);
    emit t5signal(iT5);
    }

    if(n==5)
    {
    int iT6=  value*100;
    //QString T4=  QString::number(iT4);
    emit t6signal(iT6);
    }


    if(n==6)
    {
    int iT7=  value*100;
    //QString T4=  QString::number(iT4);
    emit t7signal(iT7);
    }


    if(n==7)
    {
    int iT8=  value*100;
    //QString T4=  QString::number(iT4);
    emit t8signal(iT8);
    }




    //all lights on
//    if(value>=0.9)
//    {
//       if(n==0)
//       {
////        add_send_hex_data("90 00 02");
////        add_send_hex_data("90 08 02");
////        add_send_hex_data("90 10 02");
//       }
//       if(n==1)
//       {
////        add_send_hex_data("90 01 02");
////        add_send_hex_data("90 09 02");
////        add_send_hex_data("90 11 02");
//       }
//       if(n==2)
//       {
////        add_send_hex_data("90 02 02");
////        add_send_hex_data("90 0A 02");
////        add_send_hex_data("90 12 02");
//       }
//       if(n==3)
//       {
////        add_send_hex_data("90 03 02");
////        add_send_hex_data("90 0B 02");
////        add_send_hex_data("90 13 02");
//       }
//       if(n==4)
//       {
////        add_send_hex_data("90 04 02");
////        add_send_hex_data("90 0C 02");
////        add_send_hex_data("90 14 02");
//       }
//       if(n==5)
//       {
////        add_send_hex_data("90 05 02");
////        add_send_hex_data("90 0D 02");
////        add_send_hex_data("90 15 02");
//       }
//       if(n==6)
//       {
////        add_send_hex_data("90 06 02");
////        add_send_hex_data("90 0E 02");
////        add_send_hex_data("90 16 02");
//       }
//       if(n==7)
//       {
////       add_send_hex_data("90 07 02");
////       add_send_hex_data("90 0F 02");
////       add_send_hex_data("90 17 02");
//       }
//    }
//    //turn off peak light
//    if((value<0.84)&(value>0.60))
//    {

//       if(n==0)
//       {
////        add_send_hex_data("90 00 01");
////        add_send_hex_data("90 08 02");
////        add_send_hex_data("90 10 02");
//       }
//       if(n==1)
//       {
////        add_send_hex_data("90 01 01");
////        add_send_hex_data("90 09 02");
////        add_send_hex_data("90 11 02");
//       }
//       if(n==2)
//       {
////        add_send_hex_data("90 02 01");
////        add_send_hex_data("90 0A 02");
////        add_send_hex_data("90 12 02");
//       }
//       if(n==3)
//       {
////        add_send_hex_data("90 03 01");
////        add_send_hex_data("90 0B 02");
////        add_send_hex_data("90 13 02");
//       }
//       if(n==4)
//       {
////        add_send_hex_data("90 04 01");
////        add_send_hex_data("90 0C 02");
////        add_send_hex_data("90 14 02");
//       }
//       if(n==5)
//       {
////        add_send_hex_data("90 05 01");
////        add_send_hex_data("90 0D 02");
////        add_send_hex_data("90 15 02");
//       }
//       if(n==6)
//       {
////        add_send_hex_data("90 06 01");
////        add_send_hex_data("90 0E 02");
////        add_send_hex_data("90 16 02");
//       }
//       if(n==7)
//       {
////       add_send_hex_data("90 07 01");
////       add_send_hex_data("90 0F 02");
////       add_send_hex_data("90 17 02");
//       }
//    }
////turn off peak and middle light
//    if((value<0.60)&(value>0.10))
//    {
//       //qDebug() << "vu meter RED";

//       if(n==0)
//       {
////        add_send_hex_data("90 00 01");
////        add_send_hex_data("90 08 01");
////        add_send_hex_data("90 10 02");
//       }
//       if(n==1)
//       {
////        add_send_hex_data("90 01 01");
////        add_send_hex_data("90 09 01");
////        add_send_hex_data("90 11 02");
//       }
//       if(n==2)
//       {
////        add_send_hex_data("90 02 01");
////        add_send_hex_data("90 0A 01");
////        add_send_hex_data("90 12 02");
//       }
//       if(n==3)
//       {
////        add_send_hex_data("90 03 01");
////        add_send_hex_data("90 0B 01");
////        add_send_hex_data("90 13 02");
//       }
//       if(n==4)
//       {
////        add_send_hex_data("90 04 01");
////        add_send_hex_data("90 0C 01");
////        add_send_hex_data("90 14 02");
//       }
//       if(n==5)
//       {
////        add_send_hex_data("90 05 01");
////        add_send_hex_data("90 0D 01");
////        add_send_hex_data("90 15 02");
//       }
//       if(n==6)
//       {
////        add_send_hex_data("90 06 01");
////        add_send_hex_data("90 0E 01");
////        add_send_hex_data("90 16 02");
//       }
//       if(n==7)
//       {
////       add_send_hex_data("90 07 01");
////       add_send_hex_data("90 0F 01");
////       add_send_hex_data("90 17 02");
//       }
//    }
////turn off "green" light
//    if(value<0.10)
//    {
//       //qDebug() << "vu meter RED";

//       if(n==0)
//       {
////        add_send_hex_data("90 00 01");
////        add_send_hex_data("90 08 01");
////        add_send_hex_data("90 10 01");
//       }
//       if(n==1)
//       {
////        add_send_hex_data("90 01 01");
////        add_send_hex_data("90 09 01");
////        add_send_hex_data("90 11 01");
//       }
//       if(n==2)
//       {
////        add_send_hex_data("90 02 01");
////        add_send_hex_data("90 0A 01");
////        add_send_hex_data("90 12 01");
//       }
//       if(n==3)
//       {
////        add_send_hex_data("90 03 01");
////        add_send_hex_data("90 0B 01");
////        add_send_hex_data("90 13 01");
//       }
//       if(n==4)
//       {
////        add_send_hex_data("90 04 01");
////        add_send_hex_data("90 0C 01");
////        add_send_hex_data("90 14 01");
//       }
//       if(n==5)
//       {
////        add_send_hex_data("90 05 01");
////        add_send_hex_data("90 0D 01");
////        add_send_hex_data("90 15 01");
//       }
//       if(n==6)
//       {
////        add_send_hex_data("90 06 01");
////        add_send_hex_data("90 0E 01");
////        add_send_hex_data("90 16 01");
//       }
//       if(n==7)
//       {
////       add_send_hex_data("90 07 01");
////       add_send_hex_data("90 0F 01");
////       add_send_hex_data("90 17 01");
//       }
//    }



  }

  return result;


}


//end signalmeter



void Thread1::reset()
{


    pstop();
     ecas.command("cs-set-position 0");
     //jack_transport_reposition 	(client,0);
     jack_transport_locate(client,0);


   //turn off all fan lights
                   //add_send_hex_data("B0 28 00");
                    //add_send_hex_data("B0 29 00");
    //ntt=0;

}


void Thread1::pstop()
{

 qDebug() << "emptytracks in pstop" << emptytracks;

    nospamalsaconnect=0;


    if(emptytracks<8)
  {

        qDebug() << "emptytracks<8" << emptytracks;



//    rxfader1();
//    rxfader2();
//    rxfader3();
//    rxfader4();
//    rxfader5();
//    rxfader6();
//    rxfader7();
//    rxfader8();

//ecas.command("c-select chainMaster");
//ecas.command("cop-set ’1,1,0’");
//add_send_hex_data("B0 09 00");


    //change ea
//ecas.command("c-select chain1");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain2");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain3");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain4");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain5");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain6");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain7");
//ecas.command("cop-set ’3,1,0’");
//ecas.command("c-select chain8");
//ecas.command("cop-set ’3,1,0’");




    //qDebug() << "terminate";
    emit stopsignal(1);
    maxrectracks=0;

    //tThread->Stop=true;

    //timer->stop();

//disconnect controller from ecasound to avoid fader crash
    alsadisconnect();
    //ecas.command("engine-halt");
     jack_transport_stop(client);


   //ecas.command("stop");


   // ecas.command("cs-get-position");


     //gui-wip
    // rxplayoff();

    // maincounter = 0;

//     restart1 = 0;
//     restart2 = 0;
//     restart3 = 0;

//     rec1counter = 0;
//     rec2counter = 0;
//     rec3counter = 0;

//     //turn all vu lights off
//sleep(1);

   //gui-wip
//     add_send_hex_data("90 00 01");
//     add_send_hex_data("90 08 01");
//     add_send_hex_data("90 10 01");

//     add_send_hex_data("90 01 01");
//     add_send_hex_data("90 09 01");
//     add_send_hex_data("90 11 01");

//     add_send_hex_data("90 02 01");
//     add_send_hex_data("90 0A 01");
//     add_send_hex_data("90 12 01");

//     add_send_hex_data("90 03 01");
//     add_send_hex_data("90 0B 01");
//     add_send_hex_data("90 13 01");

//     add_send_hex_data("90 04 01");
//     add_send_hex_data("90 0C 01");
//     add_send_hex_data("90 14 01");

//     add_send_hex_data("90 05 01");
//     add_send_hex_data("90 0D 01");
//     add_send_hex_data("90 15 01");

//     add_send_hex_data("90 06 01");
//     add_send_hex_data("90 0E 01");
//     add_send_hex_data("90 16 01");

//    add_send_hex_data("90 07 01");
//    add_send_hex_data("90 0F 01");
//    add_send_hex_data("90 17 01");

//    //all rec leds off
//       add_send_hex_data("90 18 01");
//       add_send_hex_data("90 19 01");
//       add_send_hex_data("90 1A 01");
//       add_send_hex_data("90 1B 01");
//       add_send_hex_data("90 1C 01");
//       add_send_hex_data("90 1D 01");
//       add_send_hex_data("90 1E 01");
//       add_send_hex_data("90 1F 01");


   //gui-wip
// rec led
       //add_send_hex_data("90 24 01");

//       if((recmode==1)||(recmode==2))
//       {
//           //rectrackled();
//             //  add_send_hex_data("90 24 02");


//       }


  // ecas.command("cs-disconnect");


    // requestInterruption();

  //  qApp->quit();
   // QProcess::startDetached(qApp->arguments()[0], qApp->arguments());


    //m_pJackClient != NULL;
    //jack_transport_stop(m_pJackClient);

   // m_pJackClient == NULL;

    // client = jack_client_open("sixad-jack", JackNullOption, 0);


//    const char **ports;
//        const char *client_name = "simple";
//    jack_status_t status;


//jack_port_t *input_port;
//jack_port_t *output_port;
//jack_client_t *client;
//client = jack_client_open (client_name, JackNullOption, &status );

       //

      // jack test


//               if (client)
//                {
//                    jack_position_t tpos;
//                    jack_transport_query(client, &tpos);
//                    float xrate = float(tpos.frame_rate);
//                    float xtloc = (float(tpos.frame) / xrate);
//               qDebug() << "jack_transport_query---------------float xrate-----------" << xrate;
//                qDebug() << "jack_transport_query--------------float xtloc------------" << xtloc;
//                qDebug() << "jack_transport_query--------------------------";
//                qDebug() << "jack_transport_query--------------------------";

//                }




}
    if(emptytracks>7)
  {

         qDebug() << "emptytracks>7" << emptytracks;
      jack_transport_stop(client);
    }



}



//wip-80

//void Thread1::recvalue_t8(int recv_t8N)

//{
//  qDebug() << "recvalue_t8 ..............received in mthread+++++++ " << recv_t8N;

//  //v80
//       QSqlQuery queryu78;
//               queryu78.exec("UPDATE tracktable SET recvalue = 1 WHERE id = 8;");

//}




//--w-------



void Thread1::rewind(int searchvalueN)

{

    //timer->stop();
    pstop();



    //ntt = ntt - searchvalueN;

    //turn off all fan lights
                   // add_send_hex_data("B0 28 00");
                    // add_send_hex_data("B0 29 00");

    qDebug() << "valueChanged in rewind++++++++";
    qDebug() << searchvalueN;
 if (client)
 {
     jack_position_t tpos;
     jack_transport_query(client, &tpos);
     float rate = float(tpos.frame_rate);
     float tloc = ((float(tpos.frame) / rate) - searchvalueN) * rate;
     if (tloc < 0.0f) tloc = 0.0f;
     jack_transport_locate(client, (jack_nframes_t) tloc);

     if (searchvalueN < 60.0)
         searchvalueN *= 1.1f;
 }
}


void Thread1::forward(int searchvalueN)

{

  //timer->stop();
    pstop();


  //ntt = ntt + searchvalueN;

  //turn off all fan lights
                  //add_send_hex_data("B0 28 00");
                   //add_send_hex_data("B0 29 00");

 if (client)
    {
     jack_position_t tpos;
     jack_transport_query(client, &tpos);
     float rate = float(tpos.frame_rate);
     float tloc = ((float(tpos.frame) / rate) + searchvalueN) * rate;
     if (tloc < 0.0f) tloc = 0.0f;
     jack_transport_locate(client, (jack_nframes_t) tloc);

     qDebug() << "searchvalueN"  << searchvalueN;
     qDebug() << "rate" << rate ;
     qDebug() << "tloc"  << tloc;

     if (searchvalueN < 60.0f)
         searchvalueN *= 1.1f;


    }
}


void Thread1::terminateall()
{
    jack_transport_stop(client);
    ecas.command("cs-disconnect");
    ecas.command("engine-halt");

  ecas.command("stop");

}

void Thread1::exitslot()
{


    qDebug() << "exitslot()"  ;
jack_transport_stop(client);
ecas.command("cs-select play_chainsetup");
ecas.command("cs-disconnect");






                     QProcess sh11;
                      sh11.start("sh");

                      //
                      QString qshpath = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_exit.sh";
                      std::string shpath = qshpath.toStdString();
                      const char * pqshpath = shpath.c_str();
                      qDebug() << "pqshpath exit" << qPrintable(pqshpath);



                     sh11.write(pqshpath);

                      sh11.closeWriteChannel();
                      sh11.waitForFinished();





     qDebug() << "exitslot thread"  ;

int putexit =1;


tThread->quit();

emit exitvalue(putexit);


  }

//restart_slot


void Thread1::restart_slot()
{


    qDebug() << "restart_slot()"  ;
jack_transport_stop(client);
ecas.command("cs-select play_chainsetup");
ecas.command("cs-disconnect");


qDebug() << "reconnecting"  ;



                     QProcess shr11;
                      shr11.start("sh");

                      //
                      QString qshpath = HomePathT + "/GUI_TRM8TT/GUI_xTRM8TT_restart.sh";
                      std::string shpath = qshpath.toStdString();
                      const char * pqshpath = shpath.c_str();
                      qDebug() << "pqshpath restart" << qPrintable(pqshpath);



                     shr11.write(pqshpath);

                      shr11.closeWriteChannel();
                      shr11.waitForFinished();





     qDebug() << "restart thread"  ;

int putexit =1;


tThread->quit();

emit exitvalue(putexit);


  }






Thread1::~Thread1()
{
snd_seq_close(seq);
    //ecas.command("engine-halt");
    //jack_client_close(client);
    //sleep(1);
//timer2->stop();
  quit();

#if QT_VERSION >= QT_VERSION_CHECK(5,2,0)
requestInterruption();
#endif

wait();
sleep(1);

//



  //

//  char buf[512];
//  FILE *cmd_pipe = popen("pidof -s ecasound", "r");

//  fgets(buf, 512, cmd_pipe);
//  pid_t pid = strtoul(buf, NULL, 10);

//  pclose( cmd_pipe );

// QString pidrs = QString::number(pid);
//   qDebug() << "pidrs"  ;
//  qDebug() << pidrs  ;

//  //QString comend = "gnome-terminal -x bash -c \"kill -INT " + pidrs + "\"";

//  kill (pid, SIGINT);
//   kill (pid, SIGTERM);


}









//+++NOTES+++++++++++++++++++++++++++++++++++++

//https://manpages.debian.org/jessie/ecasound/ecasound.1.en.html
//http://nosignal.fi/ecasound/Documentation/ecasound-iam_manpage.html

//amidi -l

//amidi -p hw:3,0,0  --dump


//xtouch map

//SEND
//rec enable
//1-8
//90 28 7F
//90 29 7F
//90 2A 7F
//90 2B 7F
//90 2C 7F
//90 2D 7F
//90 2E 7F
//90 2F 7F
// -----------------------
//main
//90 30 7F

//transport
//<<
//90 31 7F

//>>
//90 32 7F

//rec
//90 34 7F

//play
//90 36 7F

//stop
//90 35 7F

//loop
//90 33 7F
//-------------------------

//mute (1-8)
//90 20 7F
//90 21 7F
//90 22 7F
//90 23 7F
//90 24 7F
//90 25 7F
//90 26 7F
//90 27 7F

//solo (1-8)
//90 18 7F
//B0 65 00
//90 1A 7F
//90 1B 7F
//90 1C 7F
//90 1D 7F
//90 1E 7F
//90 1F 7F

//select (1-8)
//90 10 7F
//90 11 7F
//90 12 7F
//90 13 7F
//90 14 7F
//90 15 7F
//90 16 7F
//90 17 7F

//+++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++
//https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2

//RX (receive to controll LED)
//set panning to 12 o'clock

//amidi -p hw:3,0,0 -S "B0 1A 07"

//B0 1A 07
//B0 1B 07
//B0 1C 07
//B0 1D 07
//B0 1E 07
//B0 1F 07
//B0 20 07
//B0 21 07

//--------------

//change 9-16 to FAN LED

//amidi -p hw:3,0,0 -S "B0 12 02"

//B0 13 02
//B0 14 02
//B0 15 02
//...

//------------------------

//faders to 0 (0-127)

//amidi -p hw:3,0,0 -S "B0 01 00"


//...
//B0 09 00


//------------------------

//amidi -p hw:3,0,0 -S "90 00 01"

//xx= 90 (note on)
//yy= note
//zz= vel.

//xx yy 01 off
//xx yy 02 on
//xx yy 03 blinking

//1st row:
//90 00
//90 01
//...
//90 07

//2nd row (yy)
//08
//09
//0A
//0B
//0C
//0D
//0E
//0F


//3rd row (yy)
//10
//11
//12
//13
//14
//15
//16
//17


//rec enable (yy)
//18
//19
//1A
//1B
//1C
//1D
//1E
//1F


//master fader (yy)
//20


//transport (yy)

//<<
//21

//>>
//22

//loop
//23

//rec
//24

//stop
//25

//play
//26



//+++++++++++++++++++++++++++++

//if (byte == 0x28)
//            {
//          qDebug() << "byte 0x28vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
//          if (dontspam28==0)
//          {
//          sendmidinote();
//          dontspam28=dontspam28+1;
//          dontspamrawmidi_open=dontspamrawmidi_open+1;
//          }

//           }

//   if (byte == 0x29)
//            {
//          qDebug() << "byte 0x29vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
//          //reset 28
//          dontspam28=0;
//           }

//   if (byte == 0x2A)
//            {
//          qDebug() << "byte 0x2Avvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv";
//           }



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//restart

//QProcess sh11;
// sh11.start("sh");

// //
// QString qshpath = HomePathT + "/x_helper_script.sh";
// std::string shpath = qshpath.toStdString();
// const char * pqshpath = shpath.c_str();
// qDebug() << "pqshpath" << qPrintable(pqshpath);


// //


//sh11.write(pqshpath);



// sh11.closeWriteChannel();
// sh11.waitForFinished();


//  qDebug() << "error  recmode==2 after  QProcess sh11";


//tThread->quit();

//qDebug() << "error  recmode==2 after  QtThread->quit()";

//aconnect -d 28:0 129:0
//aconnect 28:0 129:0

//aseqdump -p "Arturia BeatStep Pro"
//amidi -l

//list jack ports: jack_lsp -c



