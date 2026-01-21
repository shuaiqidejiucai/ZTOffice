#ifndef PST_BINARYTAGDATA_H
#define PST_BINARYTAGDATA_H

#include "pst_base.h"
#include "pst_roundtripdocflags12atom.h"
#include "pst_slidetime10atom.h"
class PST_BinaryTagData : public PST_Base
{
public:
    PST_BinaryTagData(const QByteArray& srcData);

    QList<PST_RoundTripDocFlags12Atom> roundTripDocFlags12Atom;
    QList<PST_SlideTime10Atom> slideTime10AtomList;
};

#endif // PST_BINARYTAGDATA_H
