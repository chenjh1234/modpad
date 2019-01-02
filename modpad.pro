include (../geoseis.include)
TEMPLATE = app
TARGET = modpad 
CONFIG += debug
           
QT += widgets
QT += testlib
QT += xml
 

win32{
INCLUDEPATH += .\
        D:\openseaseis_v2.03\openseaseis_v2.03\src\cs\geolib
LIBS += E:\test\seageolib\Debug\seageolib.dll
}

!win32{
INCLUDEPATH += .\
        $(GEOSEIS)/include

LIBS += -L$(GEOSEIS)/lib \
	-L$(GEOSEIS)/mod \
        -lgeolib -lcseis_system  -lprojectBase       

}

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
