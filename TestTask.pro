TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

LIBS += -lmysqlcppconn

SOURCES += main.cpp \
    stack.cpp \
    basestack.cpp \
    book.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    basestack.h \
    book.h \
    stack.h \
    sqlretriver.h

