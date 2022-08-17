QT += quick \
    widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/accounts/accountmanager.cpp \
        source/datastorage/datastorage.cpp \
        source/main.cpp \
        source/transactions/transactionmanager.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    translations/YBalance_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations
CONFIG += c++11 c++14 c++17

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/accounts/account.h \
    source/accounts/accountmanager.h \
    source/datastorage/datastorage.h \
    source/datastorage/iaccount.h \
    source/datastorage/itransaction.h \
    source/transactions/itransactionsmanager.h \
    source/transactions/transaction.h \
    source/transactions/transactionmanager.h \
    source/accounts/iaccountmanager.h
