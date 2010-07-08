==A Windows Win32 application for recognizing unistroke gestures==

*Usage:*


  This program is suitable for usage with tablets and touch screens for entering text where needed. *Selecting* where the text will be entered is defined by *dragging* application interior to a *targeted text area*.


*Algorithm:*


  Most of ideas are taken from [http://depts.washington.edu/aimgroup/proj/dollar/dollar.pdf $1 Unistroke Recognizer] and my personal Palm m505 experience.


*Building:*

  * _Microsoft Visual Studio_: add {{{.\inc}}} in {{{Tools | Options | Projects and Solutions |VC++ Directories | Include files}}}
  
  * _Command line Borlanc C++ 5.5_: use the {{{make clean all}}}