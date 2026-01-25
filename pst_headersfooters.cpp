#include "pst_headersfooters.h"

PST_HeadersFooters::PST_HeadersFooters(const QByteArray &srcData):PST_Base(srcData)
{

}

int PST_HeadersFooters::parser()
{
    return 0;
}

PST_HeadsFootersAtom::PST_HeadsFootersAtom(const QByteArray &srcData):PST_Base(srcData)
{

}
