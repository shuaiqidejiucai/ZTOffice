#ifndef PST_PPDRAWING_H
#define PST_PPDRAWING_H

#include "pst_base.h"
#include "pst_drawingcontainer.h"

class PST_PPDrawing : public PST_Base
{
public:
    PST_PPDrawing(const QByteArray& srcData);

    QSharedPointer<PST_DrawingContainer> dwingContiner;
};

#endif // PST_PPDRAWING_H
