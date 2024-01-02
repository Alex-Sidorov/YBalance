#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <memory>

#include "accounts/account.h"
#include "transactions/transaction.h"
#include "transactions/transactionmanager.h"
#include "accounts/accountmanager.h"
#include "datastorage/datastorage.h"
#include "models/fullaccountsmodel.h"
#include "currency/storage/currencystorage.h"
#include "categories/category.h"

#include "currency/loader/currencyloader.h"//
#include "currency/parser/parserfromrub.h"//
#include "currency/converter/converterbyrub.h"//

//#include <QLocale>
//#include <QTranslator>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    //QCoreApplication::addLibraryPath("dll");
    //qDebug() << QCoreApplication::libraryPaths();

    qmlRegisterType<AccountType>("AccountType", 1, 0, "AccountType");
    qmlRegisterAnonymousType<Account>("Account", 1);
    qmlRegisterAnonymousType<Transaction>("Transaction", 1);
    qmlRegisterAnonymousType<AccountsModel>("AccountsModel", 1);
    qmlRegisterAnonymousType<Category>("AccountsModel", 1);

    DataStorage data;
    TransactionManager transactionManager(&data);
    AccountManager accountsManager(&data);
    FullAccountsModel accountsModel(&accountsManager);
    CurrencyStorage currencyStorage;

    ParserFromRUB parser;
    CurrencyLoader loader(&parser);
    loader.refreshCurrencies();

    ConverterByRUB converter(&loader);

    /*QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "YBalance_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }*/

    std::unique_ptr<QQmlApplicationEngine> engine = std::make_unique<QQmlApplicationEngine>();

    engine->rootContext()->setContextProperty(QLatin1String("accountsModel"), &accountsModel);
    engine->rootContext()->setContextProperty(QLatin1String("currencyStorage"), &currencyStorage);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(engine.get(), &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine->load(url);

    auto result = app.exec();
    engine.reset();
    return result;
}
