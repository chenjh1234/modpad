######################################################################
# Automatically generated by qmake (3.0) ??? ?? 22 14:02:59 2015
######################################################################

#TEMPLATE = app
#TARGET = testq5
#CONFIG += debug
#INCLUDEPATH += .
#QT += widgets
#FORMS += modparameter.ui

# Input
#SOURCES += testq5.cpp

TEMPLATE = app
TARGET = modpad 
CONFIG += debug
INCLUDEPATH += .\
        D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\geolib
LIBS += E:\test\seageolib\Debug\seageolib.dll
           
QT += widgets
QT += testlib
QT += xml

#SOURCES += modpad.cpp


# Input
FORMS += modparameter.ui module.ui parmvalue.ui
SOURCES += modpad.cpp\
        moddata.cpp\
        modview.cpp\
        modapp.cpp\
        modmain.cpp
HEADERS += moddata.h\
        modview.h\
        modapp.h\
        modmain.h
RESOURCES     = modpad.qrc
