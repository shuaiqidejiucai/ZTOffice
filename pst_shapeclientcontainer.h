#ifndef PST_SHAPECLIENTCONTAINER_H
#define PST_SHAPECLIENTCONTAINER_H

#include "pst_base.h"
#include "pst_oeplaceholderatom.h"
#include "pst_roundtriphfplaceholder12atom.h"
#include "pst_externalobjectrefatom.h"
class PST_ShapeClientContainer : public PST_Base
{
public:
    PST_ShapeClientContainer(const QByteArray& srcData);

    QSharedPointer<PST_OEPlaceHolderAtom> oePlaceHolderAtom;
    QSharedPointer<PST_RoundTripHFPlaceholder12Atom> roundTripHF12Atom;
    QSharedPointer<PST_ExternalObjectRefAtom> exObjRefAtom;
};

#endif // PST_SHAPECLIENTCONTAINER_H
