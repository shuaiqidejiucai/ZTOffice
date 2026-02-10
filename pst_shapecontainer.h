#ifndef PST_SHAPECONTAINER_H
#define PST_SHAPECONTAINER_H

#include "pst_base.h"

class PST_OfficeArtFSPGR;
class PST_OfficeArtFSP;
class PST_MSOfbtOPT;
class OfficeArtClientAnchor;
class PST_ShapeClientContainer;
class PST_MSOfbtTertiaryOPT;
class OfficeArtSpContainer;
class PST_ClientTextBox;
class PSTParser_EXPORT PST_ShapeContainer : public PST_Base
{
public:
    PST_ShapeContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr = nullptr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_OfficeArtFSPGR> officeArtFSPGRPtr;
    QSharedPointer<PST_OfficeArtFSP> officeArtFSPPtr;
    QSharedPointer<PST_MSOfbtOPT> msoFbtOPTPtr;
    QSharedPointer<OfficeArtClientAnchor> officeArtClientAnchorPtr;
    QSharedPointer<PST_ShapeClientContainer> shapeClientContainerPtr;

    QSharedPointer<PST_MSOfbtTertiaryOPT> msoTertiaryOPTPtr;
    QSharedPointer<OfficeArtSpContainer> officeArtSpConPtr;
    
    QSharedPointer<PST_ClientTextBox> clientTxtBoxPtr;
};

#endif // PST_SHAPECONTAINER_H
