#-------------------------------------------------
#
# Project created by QtCreator 2022-05-18T15:07:21
#
#-------------------------------------------------

QT       += core gui charts multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual_24
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    frmsmoothcurve.cpp \
    function.cpp \
    smoothcurve.cpp \
    display_lcd.cpp \
    start_page.cpp \
    choose_city.cpp \
    choose_season.cpp \
    choose_device.cpp \
    choose_info.cpp \
    myshadowwidget.cpp \
    humidity.cpp \
    login.cpp \
    to_register.cpp \
    air_detail_info.cpp \
    energy_consumption.cpp \
    brushtool.cpp \
    customslice.cpp \
    mainwidget.cpp \
    pentool.cpp \
    play_music.cpp \
    humi_detail_info.cpp \
    equipment.cpp

HEADERS += \
        mainwindow.h \
    frmsmoothcurve.h \
    function.h \
    smoothcurve.h \
    display_lcd.h \
    start_page.h \
    choose_city.h \
    choose_season.h \
    choose_device.h \
    choose_info.h \
    myshadowwidget.h \
    humidity.h \
    login.h \
    to_register.h \
    air_detail_info.h \
    energy_consumption.h \
    brushtool.h \
    customslice.h \
    mainwidget.h \
    pentool.h \
    play_music.h \
    humi_detail_info.h \
    equipment.h

FORMS       += frmsmoothcurve.ui \
    display_lcd.ui \
    start_page.ui \
    choose_city.ui \
    choose_season.ui \
    choose_device.ui \
    choose_info.ui \
    myshadowwidget.ui \
    login.ui \
    to_register.ui \
    air_detail_info.ui \
    play_music.ui \
    humi_detail_info.ui

RESOURCES += \
    image.qrc \
    music.qrc

CONFIG += C++11
CONFIG += resources_big
