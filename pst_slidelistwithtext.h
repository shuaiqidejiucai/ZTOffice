#ifndef PST_SLIDELISTWITHTEXT_H
#define PST_SLIDELISTWITHTEXT_H

#include "pst_base.h"
#include "pst_slidepersistatom.h"
class PST_SlideListWithText : public PST_Base
{
public:
    PST_SlideListWithText(const QByteArray& srcData);

    QList<PST_SlidePersistAtom> slidePerAtomList;
};

#endif // PST_SLIDELISTWITHTEXT_H
