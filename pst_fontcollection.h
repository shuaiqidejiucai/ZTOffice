#ifndef PST_FONTCOLLECTION_H
#define PST_FONTCOLLECTION_H

#include "pst_base.h"

class PST_FontEntityAtom : public PST_Base
{
public:
    PST_FontEntityAtom(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    virtual void clearParserData()override;
};

class PST_FontCollection : public PST_Base
{
public:
    PST_FontCollection(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;
    virtual void clearParserData()override;
    QList<QSharedPointer<PST_FontEntityAtom> > fontEntityAtomList;
};

#endif // PST_FONTCOLLECTION_H
