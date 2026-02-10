#ifndef PST_SLIDEVIEWINFO_H
#define PST_SLIDEVIEWINFO_H

#include "pst_base.h"
class PST_ViewInfoAtom;
class PSTParser_EXPORT PST_SlideViewInfoAtom : public PST_Base
{
public:
    PST_SlideViewInfoAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;

    virtual void clearParserData()override;

    virtual int priority()override;
};

class PSTParser_EXPORT PST_SlideViewInfo : public PST_Base
{
public:
    PST_SlideViewInfo(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;

    virtual int priority()override;
    QList<QSharedPointer<PST_SlideViewInfoAtom> > slideViewInfoAtomList;
    QList<QSharedPointer<PST_ViewInfoAtom> > viewInfoAtomList;
};

#endif // PST_SLIDEVIEWINFO_H
