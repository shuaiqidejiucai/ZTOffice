#ifndef PST_DOCUMENT_H
#define PST_DOCUMENT_H

#include "pst_documentatom.h"
#include "pst_exobjlist.h"
#include "pst_base.h"
#include "pst_environment.h"
#include "pst_ppdrawinggroup.h"
class PST_Document : public PST_Base
{
public:
    PST_Document(const QByteArray& srcData);

    PST_DocumentAtom documentAtom;
    PST_ExObjList exObjListObj;
    PST_Environment envment;
    PST_PPDrawingGroup ppdwGroup;
};

#endif // PST_DOCUMENT_H
