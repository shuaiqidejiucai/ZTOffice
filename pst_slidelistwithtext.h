#ifndef PST_SLIDELISTWITHTEXT_H
#define PST_SLIDELISTWITHTEXT_H

#include "pst_base.h"

class PST_SlidePersistAtom;
class PST_SlideListWithText : public PST_Base
{
public:
    PST_SlideListWithText(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_SlidePersistAtom> > slidePerAtomList;
};

#endif // PST_SLIDELISTWITHTEXT_H
