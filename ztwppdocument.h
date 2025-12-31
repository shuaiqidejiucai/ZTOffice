#ifndef ZTWPPDOCUMENT_H
#define ZTWPPDOCUMENT_H

#include "zttools.h"

class ZTWPPDocument
{
public:
    ZTWPPDocument();

    bool openWPPFile(const QString& qsFilePath);

    int extratorAttachment(QSharedPointer<libolecf_item_t> itemPtr);

private:
    QSharedPointer<libolecf_file_t> m_oleFilePtr;
};

#endif // ZTWPPDOCUMENT_H
