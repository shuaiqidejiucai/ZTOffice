#ifndef PST_SHAPECONTAINER_H
#define PST_SHAPECONTAINER_H

#include "pst_base.h"
#include "pst_officeartfspgr.h"
#include "pst_officeartfsp.h"
#include "pst_msofbtopt.h"
#include "officeartspcontainer.h"
#include "pst_shapeclientcontainer.h"
#include "pst_clienttextbox.h"
#include "pst_msofbttertiaryopt.h"
class PST_ShapeContainer : public PST_Base
{
public:
    PST_ShapeContainer(const QByteArray& srcData);

    QSharedPointer<PST_OfficeArtFSPGR> officeArtFSPGRPtr;
    QSharedPointer<PST_OfficeArtFSP> officeArtFSPPtr;
    QSharedPointer<PST_MSOfbtOPT> msoFbtOPTPtr;
    QSharedPointer<PST_MSOfbtTertiaryOPT> msoTertiaryOPTPtr;
    QSharedPointer<OfficeArtSpContainer> officeArtSpConPtr;
    QList<QSharedPointer<PST_ShapeClientContainer> > shapeClientContainer;
    QList<QSharedPointer<PST_ClientTextBox> > clientTxtBox;
};

#endif // PST_SHAPECONTAINER_H
