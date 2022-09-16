#ifndef LOADER_HPP
#define LOADER_HPP

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Loader : public QObject
{
    Q_OBJECT
public:
    explicit Loader(const QUrl& url, QObject *parent = nullptr);

    QString sendQuery();

signals:
    void finished();

public slots:
    void get();

private slots:
    void onReady(QNetworkReply* reply);
    void quit();

private:
    QNetworkAccessManager* _manager;
    QUrl _url;
    QString _response;
};

#endif // LOADER_HPP
