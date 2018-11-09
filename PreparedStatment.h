/**
 * @file	PreparedStatment.h
 * @class	JsCPPDBC::PreparedStatment
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_PREPAREDSTATMENT_H__
#define __JSCPPDBC_PREPAREDSTATMENT_H__

#include "Ptr.h"
#include "EntityBase.h"
#include "EntityList.h"
#include "exception/SQLException.h"

namespace JsCPPDBC {

	class PreparedStatment
	{
	public:
		enum Type {
			TYPE_FETCH = 1,
			TYPE_UPDATE = 2,
		};

	protected:
		Type m_type;
		std::string m_sql;
		std::list<EntityColumn> m_params;

	public:
		PreparedStatment(Type type, const char *sql) throw(exception::SQLException) { m_type = type, m_sql = sql; }
		virtual ~PreparedStatment() { }

		virtual int close(void) = 0;
		virtual int execute(void) throw(exception::SQLException) = 0;
		virtual int64_t insert_rowid(void) = 0;
		virtual bool fetchRow(EntityBase *entity) throw(exception::SQLException) = 0;
		virtual int fetchRows(EntityListBase *entityList) throw(exception::SQLException) = 0;
		
		virtual int reset() {
			m_params.clear();
			return 0;
		}
		virtual int addParam(EntityColumn element) {
			m_params.push_back(element);
			return 0;
		}
	};

}

#endif /* __JSCPPDBC_PREPAREDSTATMENT_H__ */
