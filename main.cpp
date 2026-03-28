#include "mainwindow.h"
#include "tageditor.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Force Fusion so QSS isn't overridden by the Windows native style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Build a palette from scratch so Windows color settings are ignored
    QPalette palette;

    // Background colors
    palette.setColor(QPalette::Window,          QColor(245,245,245)); // main window bg
    palette.setColor(QPalette::Base,            QColor(255,255,255)); // input fields, lists
    palette.setColor(QPalette::AlternateBase,   QColor(235,235,235)); // alternating rows

    // Text colors
    palette.setColor(QPalette::WindowText,      QColor(30,30,30)); // main text
    palette.setColor(QPalette::Text,            QColor(30,30,30)); // input field text
    palette.setColor(QPalette::PlaceholderText, QColor(170,170,170)); // placeholder text

    // Button colors
    palette.setColor(QPalette::Button,          QColor(224,224,224)); // button bg
    palette.setColor(QPalette::ButtonText,      QColor(30,30,30)); // button text

    // Highlight (selection)
    palette.setColor(QPalette::Highlight,       QColor(58, 134, 255)); // selected item bg
    palette.setColor(QPalette::HighlightedText, QColor(255,255,255)); // selected item text

    // Disabled state (optional but recommended)
    palette.setColor(QPalette::Disabled, QPalette::Text,       QColor(170,170,170));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(170,170,170));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(170,170,170));

    qApp->setPalette(palette);

    QFile f(":/styles.qss/styles.qss");
    if (!f.open(QFile::ReadOnly)) {
        qDebug() << "Failed to open stylesheet:" << f.errorString();
    } else {
        QByteArray rawData = f.readAll();
        qDebug() << "Raw bytes read:" << rawData.size();
        qDebug() << "First 100 chars:" << rawData.left(100);

        QString styleSheet = QString::fromUtf8(rawData);
        qDebug() << "QString length:" << styleSheet.length();

        a.setStyleSheet(styleSheet);
        qDebug() << "App stylesheet length immediately after set:" << a.styleSheet().length();

        f.close();
    }

    qDebug() << "App stylesheet length after file():" << a.styleSheet().length();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ToDoList_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    qDebug() << "App stylesheet length after translation():" << a.styleSheet().length();

    MainWindow w;
    qDebug() << "App stylesheet length at show():" << a.styleSheet().length();
    w.show();


    TagEditor e;
    e.show();





    return QCoreApplication::exec();
}