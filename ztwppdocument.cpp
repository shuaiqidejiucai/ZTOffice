#include "ztwppdocument.h"

ZTWPPDocument::ZTWPPDocument() {}

bool ZTWPPDocument::openWPPFile(const QString &qsFilePath)
{
    QString nativePath = QDir::toNativeSeparators(qsFilePath);
    libolecf_file_t* file = nullptr;
    int errorCode = libolecf_file_initialize(&file, &error);
    if(errorCode == 1)
    {
        libolecf_file_open(file, nativePath.toUtf8().constData(), LIBOLECF_OPEN_READ, nullptr);
        m_oleFilePtr = QSharedPointer<libolecf_file_t>(file, oleFileDeleter);
        return true;
    }
    return false;
}


