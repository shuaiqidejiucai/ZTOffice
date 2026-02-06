#ifndef PST_NORMALVIEWSETINFO_H
#define PST_NORMALVIEWSETINFO_H

#include "pst_base.h"

class PST_NormalViewSetInfo9Atom : public PST_Base
{
public:
    PST_NormalViewSetInfo9Atom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

class PST_NormalViewSetInfo : public PST_Base
{
public:
    PST_NormalViewSetInfo(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_NormalViewSetInfo9Atom> > normalViewSetInfo9AtomList;
};

#endif // PST_NORMALVIEWSETINFO_H
