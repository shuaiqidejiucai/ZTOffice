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

    PST_OfficeArtFSPGR officeArtFSPGR;
    PST_OfficeArtFSP officeArtFSP;
    PST_MSOfbtOPT msoFbtOPT;
    PST_MSOfbtTertiaryOPT msoTertiaryOPT;
    OfficeArtSpContainer officeArtSpCon;
    QList<PST_ShapeClientContainer> shapeClientContainer;
    QList<PST_ClientTextBox> clientTxtBox;
};

#endif // PST_SHAPECONTAINER_H
