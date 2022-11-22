#ifndef DATABASEURL_H
#define DATABASEURL_H

#include <QString>


class DatabaseURL
{
public:
    DatabaseURL();
    static QString getBaseURL();
    static void setBaseURL(QString url);

private:
    static QString base_url;
};

#endif // DATABASEURL_H
