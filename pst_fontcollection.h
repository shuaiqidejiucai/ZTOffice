#ifndef PST_FONTCOLLECTION_H
#define PST_FONTCOLLECTION_H

#include "pst_base.h"

class PST_FontEntityAtom : public PST_Base
{
public:
    PST_FontEntityAtom(const QByteArray& srcData);
};

class PST_FontCollection : public PST_Base
{
public:
    PST_FontCollection(const QByteArray& srcData);
    QList<QSharedPointer<PST_FontEntityAtom> > fontEntityAtomList;
};

#endif // PST_FONTCOLLECTION_H
