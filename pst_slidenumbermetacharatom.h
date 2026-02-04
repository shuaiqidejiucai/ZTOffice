#ifndef PST_SLIDENUMBERMETACHARATOM_H
#define PST_SLIDENUMBERMETACHARATOM_H

#include "pst_base.h"

class PST_SlideNumberMetaCharAtom : public PST_Base
{
public:
    PST_SlideNumberMetaCharAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr) override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

#endif // PST_SLIDENUMBERMETACHARATOM_H
