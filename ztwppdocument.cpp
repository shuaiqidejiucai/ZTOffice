#include "ztwppdocument.h"
#include <qdir.h>
ZTWPPDocument::ZTWPPDocument() {}

bool ZTWPPDocument::openWPPFile(const QString &qsFilePath)
{
    QString nativePath = QDir::toNativeSeparators(qsFilePath);
    QSharedPointer<libolecf_error_t> error;
    int errorCode = ZT_libolecf_file_initialize(m_oleFilePtr, error);
    if(errorCode == 1 && m_oleFilePtr)
    {
        errorCode = ZT_libolecf_file_open(m_oleFilePtr, nativePath.toUtf8().constData(), LIBOLECF_OPEN_READ, error);
        if (errorCode == 1)
        {
            return true;
        }
    }
    return false;
}


