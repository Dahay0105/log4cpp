QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customstream.cpp \
    dsLog.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    customstream.h \
    dsLog.h \
    widget.h

FORMS += \
    widget.ui

# set library include and path
win32{
    message("load win32 library")

    INCLUDEPATH += C:\EnvXlibrary\DependPackage\OpencvBuild_XLibrary\include \
                   C:\EnvXlibrary\XLibraryCode\XCode \
                   C:\EnvXlibrary\DependPackage\boost \
                   C:\EnvXlibrary\DependPackage\boost\boost \
                   $$quote(C:\Program Files\Point Grey Research\FlyCapture2\include) \
                   $$quote(C:\Program Files (x86)\MindVision\Demo\QT5\Include) \
                   $$quote(C:\Program Files (x86)\ZBar\include)\
                   $$quote(C:\Program Files (x86)\Log4pp\include)\

    CONFIG (release, debug|release){
    LIBS += C:\EnvXlibrary\DependPackage\OpencvBuild_XLibrary\lib\opencv_highgui346.lib \
            C:\EnvXlibrary\DependPackage\OpencvBuild_XLibrary\lib\opencv_imgproc346.lib \
            C:\EnvXlibrary\DependPackage\OpencvBuild_XLibrary\lib\opencv_core346.lib \
            C:\EnvXlibrary\DependPackage\boost\lib\libboost_thread-vc141-mt-x64-1_72.lib \
            C:\EnvXlibrary\DependPackage\boost\lib\libboost_math_tr1-vc141-mt-x64-1_72.lib \
            C:\EnvXlibrary\DependPackage\boost\lib\libboost_date_time-vc141-mt-x64-1_72.lib \
            C:\EnvXlibrary\DependPackage\boost\lib\libboost_chrono-vc141-mt-x64-1_72.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\DataDefinition.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\ImageProcess.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\MathLibrary.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\ImageStitch.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\Devices.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\Utility.lib \
            C:\EnvXlibrary\XLibraryCode\XLib\XThread.lib \
            C:\EnvXlibrary\DependPackage\TBB\lib\intel64\vc14\tbb.lib \
            $$quote(C:\Program Files (x86)\ZBar\lib\libzbar-0.lib) \
            $$quote(C:\Program Files (x86)\ZBar\lib\libzbar64-0.lib) \
            $$quote(C:\Program Files (x86)\Log4pp\log4cpp.lib) \
    }
}

unix{
    message("load unix library")
    INCLUDEPATH += /usr/local/include \
                   /usr/local/XLib/include
    LIBS  += /usr/local/lib/libopencv*.so \
             /usr/local/XLib/lib/* \
             -ltbb
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
