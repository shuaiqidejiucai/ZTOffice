#ifndef PST_NORMALVIEWSETINFO_H
#define PST_NORMALVIEWSETINFO_H

#include "pst_base.h"

class PST_NormalViewSetInfo9Atom : public PST_Base
{
public:
    PST_NormalViewSetInfo9Atom(const QByteArray& srcData);
};

class PST_NormalViewSetInfo : public PST_Base
{
public:
    PST_NormalViewSetInfo(const QByteArray& srcData);

    QList<QSharedPointer<PST_NormalViewSetInfo9Atom> > normalViewSetInfo9AtomList;
};

#endif // PST_NORMALVIEWSETINFO_H
