#ifndef PST_SLIDEPERSISTATOM_H
#define PST_SLIDEPERSISTATOM_H

#include "pst_base.h"

class PST_SlidePersistAtom : public PST_Base
{
public:
    PST_SlidePersistAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    quint32 PSRReference = 0;
    quint32 Flags = 0;
    qint32 NumberTexts = 0;
    qint32 SlideID = 0;
    qint32 Unused = 0;
};

#endif // PST_SLIDEPERSISTATOM_H
