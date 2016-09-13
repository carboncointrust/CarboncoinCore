// Copyright (c) 2011-2015 The Carboncoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CARBONCOIN_QT_UTILITYDIALOG_H
#define CARBONCOIN_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>

class CarboncoinGUI;
class ClientModel;

namespace Ui {
    class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget *parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog *ui;
    QString text;

private Q_SLOTS:
    void on_okButton_accepted();
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    ShutdownWindow(QWidget *parent=0, Qt::WindowFlags f=0);
    static void showShutdownWindow(CarboncoinGUI *window);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CARBONCOIN_QT_UTILITYDIALOG_H
