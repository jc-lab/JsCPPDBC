/**
 * @file	SQLSession.cpp
 * @class	JsCPPDBC::SQLSession
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#include "SQLSession.h"
#include "DriverBase.h"

namespace JsCPPDBC {

	SQLSession::SQLSession()
	{
		m_upgradeHandler = NULL;
	}

	SQLSession::~SQLSession()
	{
	}

	int SQLSession::execute(const char *query)
	{
		return m_driver->execute(query);
	}

}
