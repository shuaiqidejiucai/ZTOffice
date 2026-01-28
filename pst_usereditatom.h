#ifndef PST_USEREDITATOM_H
#define PST_USEREDITATOM_H

#include "pst_base.h"

class PST_UserEditAtom : public PST_Base
{
public:
    PST_UserEditAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    quint32 lastSlideIdRef = 0;
    /*quint32 version : 16;
    quint32 minorVersion : 8;
    quint32 majorVersion : 8;*/
    quint16 version = 0;
    quint8 minorVersion = 0;
    quint8 majorVersion = 0;

    quint32 offsetLastEdit = 0;
    quint32 offsetPersistDirectory = 0;
    quint32 docPersistIdRef = 0;
    quint32 persistIdSeed = 0;
    quint16 lastView = 0;
    quint16 unused = 0;
    quint32 encryptSessionPersistIdRef = 0;
};

#endif // PST_USEREDITATOM_H
