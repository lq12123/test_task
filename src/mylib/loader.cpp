#include <loader.hpp>

#include <QNetworkRequest>
#include <QUrlQuery>

Loader::Loader(const QUrl& url, QObject *parent)
    : QObject{parent}, _url{url}
{
    connect(this, &Loader::finished, this, &Loader::quit);
}

/**
 * @brief Loader::sendQuery
 * Starts a thread to send a request and receive data from
 * the server.
 * @return the response received from the server.
 */
QString Loader::sendQuery()
{
    QThread th;

    connect(&th, &QThread::started, this, &Loader::get);
    connect(this, &Loader::finished, &th, &QThread::terminate);

    this->moveToThread(&th);
    th.start();

    waiting(th, _url.url(), READING);

    return _response;
}

/**
 * @brief Loader::get
 * Send a get request by URL.
 */
void Loader::get()
{
    _manager = new QNetworkAccessManager;
    QNetworkRequest request(_url);

    connect(_manager, &QNetworkAccessManager::finished, this, &Loader::onReady);

    _manager->get(request);
}

/**
 * @brief Loader::onReady
 * Processing the response received from the server.
 * @param reply
 */
void Loader::onReady(QNetworkReply* reply)
{
    if (reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    } else
    {
        _response = reply->readAll();
    }

    emit finished();
}

/**
 * @brief Loader::quit
 * Exit the thread.
 */
void Loader::quit()
{
    thread()->quit();
}

/**
 * @brief Loader::addQueryParam
 * Adds parameters in the form "key=value" to the url address.
 * @param key
 * @param param
 */
void Loader::addQueryParam(const QString& key, const QString& param)
{
    QUrlQuery query;
    query.addQueryItem(key, param);
    _url.setQuery(query);
}
