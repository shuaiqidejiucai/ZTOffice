#include "pst_base.h"

PST_Base::PST_Base(const QByteArray& srcData, const ST_Variable& var):m_STVar(var), m_srcData(srcData), m_isParser(false){}


int PST_Base::parserData()
{
	if (m_isParser)
	{
		clearData();
	}
	m_isParser = true;
	return parser();
}

void PST_Base::clearData()
{
	m_isParser = false;
	clearParserData();
	clearTreeData();
}

bool PST_Base::addChildNodePtr(const QSharedPointer<PST_Base>& childPtr)
{
	if (!childPtr)
	{
		return false;
	}
	QSharedPointer<PST_Base> parentPtr = childPtr->m_parentWeakPtr.lock();
	if (parentPtr)
	{
		if (parentPtr == childPtr)
		{
			return false;
		}
		int index = parentPtr->m_childNodeWeakPtrList.indexOf(childPtr->m_parentWeakPtr);
		if (index != -1)
		{
			parentPtr->m_childNodeWeakPtrList.removeAt(index);
		}
	}

	childPtr->m_parentWeakPtr = sharedFromThis();
	m_childNodeWeakPtrList.append(childPtr.toWeakRef());
	return true;
}

void PST_Base::clearTreeData()
{
	m_childNodeWeakPtrList.clear();
	m_parentWeakPtr.clear();
}
