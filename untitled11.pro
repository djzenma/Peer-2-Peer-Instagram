QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Distributed_Project2/account.cpp \
    ../Distributed_Project2/friendaccount.cpp \
    ../Distributed_Project2/homepage2.cpp \
    ../Distributed_Project2/imageinfo.cpp \
    ../Distributed_Project2/main.cpp \
    ../Distributed_Project2/mainwindow.cpp \
    ../Distributed_Project2/picturesicanview.cpp \
    ../Distributed_Project2/profilesicanview.cpp \
    ../Distributed_Project2/requests.cpp \
    ../Distributed_Project2/signup_page.cpp \
    ../Distributed_Project2/src/Client.cpp \
    ../Distributed_Project2/src/Communication.cpp \
    ../Distributed_Project2/src/Database.cpp \
    ../Distributed_Project2/src/DoS.cpp \
    ../Distributed_Project2/src/Message.cpp \
    ../Distributed_Project2/src/RequestReply.cpp \
    ../Distributed_Project2/src/Server.cpp \
    ../Distributed_Project2/src/Stego.cpp \
    ../Distributed_Project2/src/base64.cpp \
    ../Distributed_Project2/src/experiment.cpp \
    ../Distributed_Project2/src/utils.cpp \
    ../Distributed_Project2/viewpicture.cpp \
    src/Peer.cpp \
    src/Thread.cpp

HEADERS += \
    ../Distributed_Project2/account.h \
    ../Distributed_Project2/friendaccount.h \
    ../Distributed_Project2/headers/Client.h \
    ../Distributed_Project2/headers/Communication.h \
    ../Distributed_Project2/headers/Database.h \
    ../Distributed_Project2/headers/DoS.h \
    ../Distributed_Project2/headers/Message.h \
    ../Distributed_Project2/headers/RequestReply.h \
    ../Distributed_Project2/headers/Server.h \
    ../Distributed_Project2/headers/Stego.h \
    ../Distributed_Project2/headers/base64.h \
    ../Distributed_Project2/headers/experiment.h \
    ../Distributed_Project2/headers/utils.h \
    ../Distributed_Project2/homepage2.h \
    ../Distributed_Project2/imageinfo.h \
    ../Distributed_Project2/mainwindow.h \
    ../Distributed_Project2/picturesicanview.h \
    ../Distributed_Project2/profilesicanview.h \
    ../Distributed_Project2/requests.h \
    ../Distributed_Project2/signup_page.h \
    ../Distributed_Project2/viewpicture.h \
    headers/Peer.h \
    headers/Thread.h \

FORMS += \
    ../Distributed_Project2/account.ui \
    ../Distributed_Project2/friendaccount.ui \
    ../Distributed_Project2/homepage2.ui \
    ../Distributed_Project2/imageinfo.ui \
    ../Distributed_Project2/mainwindow.ui \
    ../Distributed_Project2/picturesicanview.ui \
    ../Distributed_Project2/profilesicanview.ui \
    ../Distributed_Project2/requests.ui \
    ../Distributed_Project2/signup_page.ui \
    ../Distributed_Project2/viewpicture.ui \
    ../Distributed_Project2/imageinfo.ui \
    ../Distributed_Project2/mainwindow.ui \
    src/runbackground.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Images2/mine/Screen Shot 2019-11-06 at 1.55.57 PM.png \
    ../Images2/mine/Screen Shot 2019-11-06 at 1.55.57 PM.png \
    ../Manar/Distributed-Client/CMakeLists.txt \
    ../Manar/Distributed-Client/images/DB.json \
    ../Manar/Distributed-Client/images/mine/0.jpg \
    ../Manar/Distributed-Client/images/mine/1.jpg \
    ../Manar/Distributed-Client/images/mine/2.jpg \
    ../Manar/Distributed-Client/images/mine/4.jpg \
    ../Manar/Distributed-Client/images/stego/0_stego.jpg \
    ../Manar/Distributed-Client/images/stego/1_stego.jpg \
    ../Manar/Distributed-Client/images/stego/2_stego.jpg \
    CMakeLists.txt \
    Images2/mine/Screen Shot 2019-11-06 at 1.55.57 PM.png \
    Images2/mine2/Screen Shot 2019-11-06 at 1.55.57 PM.png \
    Images2/requested/Screen Shot 2019-11-06 at 1.18.45 PM.png \
    Images2/requested2/Screen Shot 2019-11-06 at 1.18.45 PM.png \
    Images2/stego/Screen Shot 2019-11-13 at 10.44.50 PM.png \
    Images2/stego2/Screen Shot 2019-11-13 at 10.44.50 PM.png \
    images/DB.json \
    images/mine/0.jpg \
    images/mine/1.jpg \
    images/mine/2.jpg \
    images/mine/3.jpg \
    images/mine/4.jpg \
    images/mine/5.jpg \
    images/requested/2.jpg \
    images/requested/5.jpg \
    images/stego/0_stego.jpg \
    images/stego/1_stego.jpg \
    images/stego/2_stego.jpg \
    images/stego/3_stego.jpg \
    images/stego/4_stego.jpg

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/jsoncpp/1.9.1/lib/release/ -ljsoncpp.1.9.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/Cellar/jsoncpp/1.9.1/lib/debug/ -ljsoncpp.1.9.0
else:unix: LIBS += -L$$PWD/../../../../usr/local/Cellar/jsoncpp/1.9.1/lib/ -ljsoncpp.1.9.0

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/jsoncpp/1.9.1/include/json
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/jsoncpp/1.9.1/include/json
