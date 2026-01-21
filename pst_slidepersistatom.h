#ifndef PST_SLIDEPERSISTATOM_H
#define PST_SLIDEPERSISTATOM_H

#include "pst_base.h"

class PST_SlidePersistAtom : public PST_Base
{
public:
    PST_SlidePersistAtom(const QByteArray& srcData);

    quint32 PSRReference;
    quint32 Flags;
    qint32 NumberTexts;
    qint32 SlideID;
    qint32 Unused;
};

#endif // PST_SLIDEPERSISTATOM_H
