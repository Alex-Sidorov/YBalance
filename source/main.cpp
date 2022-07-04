#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "transactions/transaction.h"
#include "transactions/transactionmanager.h"
#include "datastorage/datastorage.h"
//#include <QLocale>
//#include <QTranslator>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterAnonymousType<Transaction>("Transaction",1);

    DataStorage data;
    TransactionManager transaction_manager(&data);
    auto i  = transaction_manager.addTransaction("12","3",QDateTime::currentDateTime(), "f",98.98, "usd");
    auto i1 = transaction_manager.addTransaction("12","4",QDateTime::currentDateTime(), "5555",9.98, "usd");
    transaction_manager.addTransaction("333","444",QDateTime::currentDateTime(), "gggg",198.98, "usd");
    transaction_manager.removeTransaction("12",i);
    transaction_manager.getTransactions("12");
    transaction_manager.updateTransaction(i1, "12","3",QDateTime::currentDateTime(), "f",98.98, "usd");

    /*QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "YBalance_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }*/

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
