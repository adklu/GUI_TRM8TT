GUI_TRM8TT is a professional 8 Track (overdubbing) Audio Recorder for Midi CC Controllers. 

For LICENSES see LICENSES file

Content

A) REQUIRED

B) INSTALL

C) FIRST TIME USE

D) GUI

--------------------------


A) REQUIRED

Linux
Qt5
(Qt 5.2.1)
(mesa-common-dev)
(libgl1-mesa-dev libglu1-mesa-dev) 
ALSA
libasound2-dev
libasound2
Jack
libjack-dev or libjack-jackd2-dev
Ecasound 
Midi CC controller for 8 tracks (e.g. Behringer XTouchCompact)
Audio Interface for Linux (ALSA)

B) INSTALL

1) Copy Source into (replace [user name]): /home/[user name]/GUI_TRM8TT
2) Create the makefile: Run the command 'qmake' (and the following commands) inside of /home/[user name]/GUI_TRM8TT
3) Rename Makefile into Makefile.am
4) Run: aclocal 
5) Run: automake --add-missing --foreign
6) Run: autoconf
7) Rename Makefile.am into Makefile
8) Run: ./configure
9) Run: make

10.1) Start GUI_TRM8TT via command (debug output in terminal):
/home/[user name]/GUI_TRM8TT/GUI_TRM8TT

10.2) Create Desktop file (GUI_TRM8TT.desktop):

[Desktop Entry]
Name=GUI_TRM8TT
Version=0.0.76
GenericName=GUI_TRM8TT
Comment=GUI_TRM8TT
Exec=/home/[user name]/GUI_TRM8TT/GUI_TRM8TT %F
Icon=/home/[user name]/GUI_TRM8TT/32_32.png
Categories=audio;Qt;
Keywords=audio;recorder;Qt;
Terminal=false
Type=Application


C) FIRST TIME USE

0) Set sampling rate/frames/period/buffer... in JACK e.g. via QjackCtl (GUI_TRM8TT will start JACK automatically with the saved settings).
1) GUI_TRM8TT is creating helper .sh files (Message: 'Please restart your PC, mark all GUI_xTRM8TT_exit.sh or GUI_xTRM8TT_restart.sh files as executables and restart the program.'). Without these files GUI_TRM8TT will not work.
2) Please create/select a 'tape' folder (it is possible to import mono .wav files with the same bit/sampling rate as the Jack session. Only files with the names Track_1.wav until Track_8.wav are recognized as active tracks (instead of deleting track files, tracks can be renamed e.g. Track_1_Take1.wav).
3) Please select the midi CC controller (Settings) and restart GUI_TRM8TT.

4) Assignment of a set of 8 CC faders/knobs to volume or balance:
To map volume faders:
Create with a text editor like gedit inside of the /home/[user name]/GUI_TRM8TT folder a text file with the name "vol_map", open the file
enter the first midi CC number (e.g. "1"), save and close the file (now midi CC 1 to 8 are assigned as volumne faders).

To map panning knobs:
Create inside of the /home/[username]/GUI_TRM8TT folder a text file with the name "pan_map", open the file
enter the first midi CC number (e.g. "10"), save and close the file (now midi CC 10 to 18 are assigned as panning knobs).

If no vol_map or pan_map files are inside of the folder, the following values are used:
int vol_map = 1;
int pan_map = 10;
(= Behringer XTouchCompact Layer A)

5) "Transport": Permanent assignment of midi notes

'<<': 49

'>>': 50

'RTZ': 51

'STOP': 53

'>':54

(= Behringer XTouchCompact default settings)



D) GUI

![alt text](https://github.com/AndreasDanielKlumpp/GUI_TRM8TT/blob/master/trm8ttManual.png)






