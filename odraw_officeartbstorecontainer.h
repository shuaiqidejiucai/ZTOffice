#ifndef ODRAW_OFFICEARTBSTORECONTAINER_H
#define ODRAW_OFFICEARTBSTORECONTAINER_H

#include "pst_base.h"
#include "pst_msofbtbse.h"
class ODRAW_OfficeArtBStoreContainer : public PST_Base
{
public:
    ODRAW_OfficeArtBStoreContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    QList<QSharedPointer<PST_MSOfbtBSE> > msoBtBsePtrList;
};

#endif // ODRAW_OFFICEARTBSTORECONTAINER_H
