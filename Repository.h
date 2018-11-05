/**
 * @file	Repository.h
 * @class	JsCPPDBC::Repository
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_REPOSITORY_H__
#define __JSCPPDBC_REPOSITORY_H__

#include "Ptr.h"
#include "PreparedStatment.h"
#include "exception/SQLException.h"

#include <map>
#include <list>
#include <string>

namespace JsCPPDBC {

	class SQLSession;
	class DriverBase;
	class Repository
	{
	protected:
		SQLSession *m_sqlSession;
		DriverBase *m_driver;
		std::map<std::string, Ptr<PreparedStatment> > m_stats;

		void addMethod(const char *methodName, PreparedStatment::Type type, const char *query) throw (exception::SQLException);
		void addMethod(const char *methodName, Ptr<PreparedStatment>& stmt) throw (exception::SQLException);

	public:
		Repository(SQLSession *sqlSession, DriverBase *driver);
		virtual ~Repository();
	};

}

#endif /* __JSCPPDBC_REPOSITORY_H__ */
