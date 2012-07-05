#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <QObject>
#include <QtCore/QUrl>
#include <QtCore/QXmlStreamReader>
#include <QtNetwork/QNetworkAccessManager>

#include "projects.h"

namespace Jenkins {
namespace Internal {

class DataFetcher : public QObject
{
Q_OBJECT
public:
    DataFetcher(int maxItems, QObject *parent = 0);

signals:

    void projectItemReady(const Project& proj);

public slots:
    void fetch(QUrl url, QString username=QString(), QString password=QString());
    void finished(QNetworkReply* repl);

signals:
    void finished(bool error, QString message);

private:
    void parseXml();
    void parseJob();
    void parseProjectHealth();

    QXmlStreamReader m_xml;
    Project currentProject;

    QNetworkAccessManager mNetworkAccess;
    QString m_errorMessage;

    int m_items;
    int m_maxItems;

};

} // namespace Internal
} // namespace CruiseControl

#endif // DATAFETCHER_H