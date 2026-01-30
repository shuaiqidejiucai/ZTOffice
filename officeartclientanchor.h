#ifndef OFFICEARTCLIENTANCHOR_H
#define OFFICEARTCLIENTANCHOR_H

#include "pst_base.h"

struct ST_RectStruct
{
    enum SizeType { Small, Big };
    ST_RectStruct(SizeType stType):type(stType)
    {
        if (type)
        {
            anchoData.smallRect.top = 0;
            anchoData.smallRect.left = 0;
            anchoData.smallRect.right = 0;
            anchoData.smallRect.bottom = 0;
        }
        else 
        {
            anchoData.bigRect.top = 0;
            anchoData.bigRect.left = 0;
            anchoData.bigRect.right = 0;
            anchoData.bigRect.bottom = 0;
        }
    }
    SizeType type;
    union
    {
        struct {
            qint16 top;
            qint16 left;
            qint16 right;
            qint16 bottom;
        } smallRect;
        struct {
            qint32 top;
            qint32 left;
            qint32 right;
            qint32 bottom ;
        } bigRect; // µ± type=false Ê±
    } anchoData;
};

class OfficeArtClientAnchor : public PST_Base
{
public:
    OfficeArtClientAnchor(const QByteArray& srcData, const ST_Variable& var);

    virtual int parser()override;

    virtual void clearParserData() override;

    QSharedPointer<ST_RectStruct> stRectStructPtr;
};

#endif // OFFICEARTCLIENTANCHOR_H
