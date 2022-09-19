#ifndef LOADER_HPP
#define LOADER_HPP

#include <QObject>
#include <QThread>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Loader : public QObject
{
    Q_OBJECT
public:
    enum State
    {
        WRITING,
        READING
    };

    explicit Loader(const QUrl& url, QObject *parent = nullptr);

    QString sendQuery();
    void addQueryParam(const QString& key, const QString& param);

    template<typename T>
    static void waiting(T& th, const QString& text, Loader::State state);

signals:
    void finished();

public slots:
    void get();

private slots:
    void onReady(QNetworkReply* reply);
    void quit();

private:
    QNetworkAccessManager* _manager;
    QUrl 				   _url;
    QString 			   _response;
};

/**
 * @brief Loader::waiting
 * Displays a wait message while receiving or writing data.
 * @param th
 * @param text
 * @param state
 */
template<typename T>
void Loader::waiting(T& th, const QString& text, Loader::State state)
{
    QTextStream out(stdout);
    out << text << Qt::endl;

    QString out_str{"Waiting..."};
    while (th.isRunning())
    {
        for (auto it = out_str.cbegin(); it != out_str.cend(); ++it)
        {
            out << *it;
            out.flush();
            QThread::msleep(320);
        }

        out << '\r'; out.flush();

        for (auto i = 0; i < out_str.size(); ++i)
        {
            out << ' ';
            out.flush();
        }
        out << '\r'; out.flush();
    }

    switch(state)
    {
    case READING:
        out << "Data from " << text << " received" << Qt::endl;
        break;
    case WRITING:
        out << "Data for the " << text <<
               " architecture is written." << Qt::endl;
        break;
    }
}

#endif // LOADER_HPP
