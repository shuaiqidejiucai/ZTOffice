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

    QSharedPointer<PST_DocumentAtom> documentAtom;
    QList<QSharedPointer<PST_ExObjList> > exObjListObjList;
    QList<QSharedPointer<PST_Environment> > envmentList;
    QList<QSharedPointer<PST_PPDrawingGroup> > ppdwGroupList;
    QList<QSharedPointer<PST_SlideListWithText> > slideListWithTxtList;
    QList<QSharedPointer<PST_List> > PSTList;
    QList<QSharedPointer<PST_HeadersFooters> > headersFootersList;
    QList<QSharedPointer<PST_RoundTripCustomTableStyles12> > roundTripTableStyleList;
    QSharedPointer<PST_EndDocumentAtom> endDocumentAtom;
};

#endif // PST_DOCUMENT_H
