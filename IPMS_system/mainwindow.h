#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDateTime>
#include <QThread>
#include <QTimer>
#include <QDebug>

#define TIMEOUT (3 * 1000)


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initDatabase();
    void initInformationTableView();
    void initGarageTableView();
    void initLevel();
    void initParkingNum();
    void initTimeKeeper();
    bool getVehicleIDAndPlace(QString& id,QString& place);
    double calculate_money(QDateTime &inTime,QDateTime &outTime,double &price);
    int how_to_get_money(QDateTime &packageDay,QDateTime &inTime,QDateTime &outTime);
    void setPrice();
    bool enableIn();
    bool addCurrentNum();
    bool reduceCurrentNum();
    void showInfo(const QString &vehicleId,const QString &place,double bill,QDateTime &time,int flag);
    void inAndOutClean();

public slots:
    void unlogin();
private slots:
    void level_rec_from_login(int level);

    void showParkingNum();

    void on_inAndOutPageButton_clicked();

    void on_garagePageButton_clicked();

    void on_queryPageButton_clicked();

    void on_rechargePageButton_clicked();

    void on_chargeRulePageButton_clicked();

    void on_managePageButton_clicked();

    void on_inButton_clicked();

    void on_outButton_clicked();

    void on_informationSearchButton_clicked();

    void on_refreshButton_clicked();

    void on_AllInformatioButton_clicked();



private:
    Ui::MainWindow *ui;
    QSqlDatabase *database;
    bool database_open = false;
    QSqlTableModel *information_table_model;
    QSqlTableModel *garage_table_model;
    int level = 0;
    double price = 0.6;
    int max_num;
    int current_num;
    QTimer *timer;

};

#endif // MAINWINDOW_H
