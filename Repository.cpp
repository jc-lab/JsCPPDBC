/**
 * @file	Repository.cpp
 * @class	JsCPPDBC::Repository
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#include "Repository.h"
#include "DriverBase.h"

namespace JsCPPDBC {

	Repository::Repository(SQLSession *sqlSession, DriverBase *driver) {
		m_sqlSession = sqlSession;
		m_driver = driver;
	}

	Repository::~Repository() {

	}

	void Repository::addMethod(const char *methodName, PreparedStatment::Type type, const char *query) throw (exception::SQLException)
	{
		m_stats[methodName] = m_driver->createSQLQuery(type, query);
	}

	void Repository::addMethod(const char *methodName, Ptr<PreparedStatment>& stmt) throw (exception::SQLException)
	{
		m_stats[methodName] = stmt;
	}
}
