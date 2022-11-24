#include "databaseurl.h"

DatabaseURL::DatabaseURL()
{
    base_url = "http://localhost:3000";

}

QString DatabaseURL::getBaseURL()
{
    return base_url;
}

void DatabaseURL::setBaseURL(QString url)
{
    base_url = url;
}

QString DatabaseURL::base_url
{
    "http://localhost:3000"
    //"http://localhost:3000"
};
