QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    cheeseitem.cpp \
    countinglabel.cpp \
    gamefinishscreen.cpp \
    gamescreen.cpp \
    item.cpp \
    jerry.cpp \
    leaderboard.cpp \
    main.cpp \
    map.cpp \
    powerup.cpp \
    tom.cpp \
    user.cpp \
    welcomescreen.cpp

HEADERS += \
    character.h \
    cheeseitem.h \
    countinglabel.h \
    gamefinishscreen.h \
    gamescreen.h \
    item.h \
    jerry.h \
    leaderboard.h \
    map.h \
    powerup.h \
    tom.h \
    user.h \
    welcomescreen.h

FORMS += \
    gamefinishscreen.ui \
    leaderboard.ui \
    welcomescreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
