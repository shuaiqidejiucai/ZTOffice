#ifndef PST_FONTCOLLECTION_H
#define PST_FONTCOLLECTION_H

#include "pst_base.h"

class PSTParser_EXPORT PST_FontEntityAtom : public PST_Base
{
public:
    PST_FontEntityAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
};

class PSTParser_EXPORT PST_FontCollection : public PST_Base
{
public:
    PST_FontCollection(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QList<QSharedPointer<PST_FontEntityAtom> > fontEntityAtomList;
};

#endif // PST_FONTCOLLECTION_H
