#ifndef PST_SLIDEVIEWINFO_H
#define PST_SLIDEVIEWINFO_H

#include "pst_base.h"
#include "pst_viewinfoatom.h"
class PST_SlideViewInfoAtom : public PST_Base
{
public:
    PST_SlideViewInfoAtom(const QByteArray& srcData);

    virtual int parser()override;
};

class PST_SlideViewInfo : public PST_Base
{
public:
    PST_SlideViewInfo(const QByteArray& srcData);

    virtual int parser()override;

    QList<QSharedPointer<PST_SlideViewInfoAtom> > slideViewInfoAtomList;
    QList<QSharedPointer<PST_ViewInfoAtom> > viewInfoAtomList;
};

#endif // PST_SLIDEVIEWINFO_H
