## GUI_TRM8TT - Professional 8 Track Overdubbing Audio Recorder for Midi CC Controllers  (8 Track Tape Recorder Style)

For LICENSES see LICENSES file

### Content

A) REQUIRED  
B) INSTALL  
C) FIRST TIME USE  
D) GUI  


--------------------------


### A) REQUIRED

```
Linux (tested with Debian 9)  
Qt5 (tested with Qt 5.2.1) 
qmake  
GNU Autotools (automake, autoconf, configure, make)
(mesa-common-dev)  
(libgl1-mesa-dev libglu1-mesa-dev)  
ALSA  
libasound2-dev  
libasound2  
Jack (tested with 1.9.10)  
libjack-dev or libjack-jackd2-dev  
Ecasound (tested with 2.9.1-7)  
Midi CC controller for 8 tracks (e.g. Behringer XTouch Compact)  
Audio Interface for Linux (ALSA)
```

### B) INSTALL

- Copy Source into (replace [username]): /home/[username]/GUI_TRM8TT

- Mark all .sh and .desktop files as executables

- ./INSTALL.sh

- Edit Desktop file (GUI_TRM8TT.desktop):

replace [username] in:

Exec=/home/[username]/GUI_TRM8TT/GUI_TRM8TT %F 

Icon=/home/[username]/GUI_TRM8TT/32_32.png 

(To start GUI_TRM8TT via command (debug output in terminal): /home/[username]/GUI_TRM8TT/GUI_TRM8TT)

###  C) FIRST TIME USE

0) Set sampling rate/frames/period/buffer... in JACK e.g. via QjackCtl (GUI_TRM8TT will start JACK automatically with the saved settings).
1) GUI_TRM8TT is creating helper .sh files inside of the GUI_TRM8TT folder (Message: 'Please restart your PC, mark all GUI_xTRM8TT_exit.sh or GUI_xTRM8TT_restart.sh files as executables and restart the program.'). Without these executable files GUI_TRM8TT will not work.
2) Create/select a 'tape' folder (it is possible to import mono .wav files with the same bit depth/sampling rate as the Jack session. Only files with the names Track_1.wav until Track_8.wav are recognized as active tracks (instead of deleting track files, tracks can be renamed e.g. Track_1_Take1.wav).
3) Select the midi CC controller (Settings) and restart GUI_TRM8TT.

4) Assignment of a set of 8 CC faders/knobs to volume or balance:

```
To map volume faders:  
Create with a text editor inside of /home/[username]/GUI_TRM8TT a file with the name "vol_map",
enter the first midi CC number (e.g. "1"), save and close the file (now midi CC 1 to 8 are assigned as volumne faders).

To map panning knobs:  
Create inside of /home/[username]/GUI_TRM8TT a file with the name "pan_map",
enter the first midi CC number (e.g. "10"), save and close the file (now midi CC 10 to 17 are assigned as panning knobs).

If no vol_map or pan_map files are inside of the folder, the following values are used:
int vol_map = 1;
int pan_map = 10;
(= Behringer XTouchCompact Layer A)
```

5) 'Transport function': Midi note (Controller)

```
'<<': 49  
'>>': 50  
'RTZ': 51  
'STOP': 53  
'>':54  
(= Behringer XTouchCompact default settings)
```

Midi channel = Channel 1



### D) GUI

![alt text](https://github.com/AndreasDanielKlumpp/GUI_TRM8TT/blob/master/GUI_png3.png)










