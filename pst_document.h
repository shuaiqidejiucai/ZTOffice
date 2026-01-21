#ifndef PST_DOCUMENT_H
#define PST_DOCUMENT_H

#include "pst_documentatom.h"
#include "pst_exobjlist.h"
#include "pst_base.h"
#include "pst_environment.h"
#include "pst_ppdrawinggroup.h"
#include "pst_slidelistwithtext.h"
#include "pst_list.h"
#include "pst_headersfooters.h"
#include "pst_roundtripcustomtablestyles12.h"
#include "pst_enddocumentatom.h"
class PST_Document : public PST_Base
{
public:
    PST_Document(const QByteArray& srcData);

    PST_DocumentAtom documentAtom;
    QList<PST_ExObjList> exObjListObjList;
    QList<PST_Environment> envmentList;
    QList<PST_PPDrawingGroup> ppdwGroupList;
    QList<PST_SlideListWithText> slideListWithTxtList;
    QList<PST_List> PSTList;
    QList<PST_HeadersFooters> headersFootersList;
    QList<PST_RoundTripCustomTableStyles12> roundTripTableStyleList;
    PST_EndDocumentAtom endDocumentAtom;
};

#endif // PST_DOCUMENT_H
