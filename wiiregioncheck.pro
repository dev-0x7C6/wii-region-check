#-------------------------------------------------
#
# Project created by QtCreator 2008-11-27T20:13:13
#
#-------------------------------------------------

TARGET = wiiregioncheck
TEMPLATE = app
DEPENDPATH += . forms src
INCLUDEPATH += . src

UI_DIR = src
MOC_DIR = src
RCC_DIR = src
OBJECTS_DIR = src

RESOURCES += images.qrc

win32 {
 RC_FILE = win/icon.rc
}

unix {
 INSTALL_PREFIX =  /usr
 target.path =  $${INSTALL_PREFIX}/bin
 icons.path =  /usr/share/icons
 icons.files =  icons/$${TARGET}32.png  icons/$${TARGET}48.png  icons/$${TARGET}128.png 
 doc.path = /usr/share/doc/wiiregioncheck
 doc.files = doc/CHANGELOG doc/COPYING doc/README
 desktop.path =  /usr/share/applications
 desktop.files =  res/$${TARGET}.desktop
 dolphin_integration.path =  /usr/share/apps/dolphin/servicemenus
 dolphin_integration.files =  res/$${TARGET}-check.desktop
 d3lphin_integration.path =  /usr/share/apps/d3lphin/servicemenus
 d3lphin_integration.files =  res/$${TARGET}-check.desktop
 konqueror_integration.path =  /usr/share/apps/konqueror/servicemenus
 konqueror_integration.files =  res/$${TARGET}-check.desktop
 kde4_integration.path =  /usr/lib/kde4/share/kde4/services/ServiceMenus
 kde4_integration.files = res/$${TARGET}-check.desktop
 INSTALLS =  target \ 
  doc \
  icons \
  desktop \
  dolphin_integration \
  d3lphin_integration \
  konqueror_integration \
  kde4_integration
}

macx {
 QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.5.sdk
 CONFIG-=app_bundle
 CONFIG+=x86 ppc
 ICON =  macx/icon.icns
}

SOURCES += src/main.cpp src/mainwindow.cpp
HEADERS  += src/mainwindow.h
FORMS    += forms/mainwindow.ui

