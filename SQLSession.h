/**
 * @file	SQLSession.h
 * @class	JsCPPDBC::SQLSession
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_SQLSESSION_H__
#define __JSCPPDBC_SQLSESSION_H__

#include "UpgradeHandler.h"
#include "Ptr.h"
#include "EntityBase.h"
#include "EntityList.h"

namespace JsCPPDBC {

	class DriverBase;
	class SQLSession
	{
	private:
		Ptr<DriverBase> m_driver;

		UpgradeHandler *m_upgradeHandler;

		SQLSession();

	public:
		virtual ~SQLSession();

		class Builder {
		private:
			SQLSession *m_sqlSession;
		public:
			Builder() {
				m_sqlSession = new SQLSession();
			}
			~Builder() {
				if (m_sqlSession) {
					delete m_sqlSession;
					m_sqlSession = NULL;
				}
			}

			Builder &attachDriver(Ptr<DriverBase> driver) {
				m_sqlSession->m_driver = driver;
				return *this;
			}
			Builder &upgradeHandler(UpgradeHandler *_upgradeHandler) {
				m_sqlSession->m_upgradeHandler = _upgradeHandler;
				return *this;
			}
			Ptr<SQLSession> build() {
				Ptr<SQLSession> ptr(m_sqlSession);
				m_sqlSession = NULL;
				return ptr;
			}
		};

		DriverBase *getDriver() {
			return m_driver.getPtr();
		}

		int execute(const char *query);
	};

}

#endif /* __JSCPPDBC_SQLSESSION_H__ */
