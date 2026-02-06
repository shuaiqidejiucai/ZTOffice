#ifndef PST_DRAWINGCONTAINER_H
#define PST_DRAWINGCONTAINER_H

#include "pst_base.h"

class PST_OfficeArtFDG;
class PST_GroupShapeContainer;
class PST_ShapeContainer;
class PST_DrawingContainer : public PST_Base
{
public:
    PST_DrawingContainer(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser(PSTSearch* pSearchPtr)override;
    virtual void clearParserData()override;
    virtual int priority()override;
    QSharedPointer<PST_OfficeArtFDG> officeArtFDG;
    QSharedPointer<PST_GroupShapeContainer> groupShapeContainer;
    QSharedPointer<PST_ShapeContainer> shapeContainer;
};

#endif // PST_DRAWINGCONTAINER_H
