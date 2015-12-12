# QTunneler #

A simple multiplayer network game, based on the original "Tunneler" DOS game and written in C++ using the Qt framework.

# Design workbench #

## Docs ##
Internal paper documents from project inception phase. Do not attempt to understand unless you are a project member.

![![](http://img440.imageshack.us/img440/3631/qtunneler1.th.jpg)](http://img440.imageshack.us/i/qtunneler1.jpg)
![![](http://img169.imageshack.us/img169/3858/qtunneler2.th.jpg)](http://img169.imageshack.us/i/qtunneler2.jpg)

## TODO list ##
  * optimize collison detection by using bit operators
  * rework network model (allow asynchronous processing to reduce client lag)

## Bug list ##
  * ocasional deadlock of threads
  * invisible stone inside of base (???)
  * after the end of game is the client core still running and the dialogue text-boxes can not be edited. Here is [log](http://code.google.com/p/qtunneler/source/browse/wiki/debugWindow1.png).