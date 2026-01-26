#ifndef PST_BINARYTAGDATA_H
#define PST_BINARYTAGDATA_H

#include "pst_base.h"
#include "pst_roundtripdocflags12atom.h"
#include "pst_slidetime10atom.h"
#include "pst_styletextprop9atom.h"
#include "pst_roundtripheaderfooterdefaults12atom.h"
#include "pst_gridspacing10atom.h"
class PST_BinaryTagData : public PST_Base
{
public:
    PST_BinaryTagData(const QByteArray& srcData);

    virtual int parser()override;

    QList<QSharedPointer<PST_RoundTripDocFlags12Atom> > roundTripDocFlags12Atom;
    QList<QSharedPointer<PST_GridSpacing10Atom> > roundTripDocFlags12Atom;
    QList<QSharedPointer<PST_SlideTime10Atom> > slideTime10AtomList;
    QList<QSharedPointer<PST_StyleTextProp9Atom> > styleTxtProp9AtomList;
    QList<QSharedPointer<PST_RoundTripHeaderFooterDefaults12Atom> > RTHFD12AtomList;
};

#endif // PST_BINARYTAGDATA_H
