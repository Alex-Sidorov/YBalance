QT += quick \
    widgets \
    sql    \
    network

CONFIG += qml_debug
CONFIG += c++11 c++14 c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
    source/accounts/account.h \
    source/accounts/accountmanager.h \
    source/currency/converter/converterbyrub.h \
    source/currency/converter/iconverter.h \
    source/currency/loader/currencyloader.h \
    source/currency/loader/icurrencyloader.h \
    source/currency/parser/iparser.h \
    source/currency/parser/parserfromrub.h \
    source/currency/storage/currencystorage.h \
    source/currency/storage/icurrencystorage.h \
    source/datastorage/datastorage.h \
    source/datastorage/iaccount.h \
    source/datastorage/itransaction.h \
    source/models/accountsmodel.h \
    source/models/fullaccountsmodel.h \
    source/transactions/itransactionsmanager.h \
    source/transactions/transaction.h \
    source/transactions/transactionmanager.h \
    source/accounts/iaccountmanager.h

SOURCES += \
        source/accounts/accountmanager.cpp \
        source/currency/converter/converterbyrub.cpp \
        source/currency/loader/currencyloader.cpp \
        source/currency/parser/parserfromrub.cpp \
        source/currency/storage/currencystorage.cpp \
        source/datastorage/datastorage.cpp \
        source/main.cpp \
        source/models/accountsmodel.cpp \
        source/models/fullaccountsmodel.cpp \
        source/transactions/transactionmanager.cpp

TRANSLATIONS += \
    translations/YBalance_en_US.ts

RESOURCES += qml.qrc \
    icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml/

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

