/**
 * @file	DriverBase.h
 * @class	JsCPPDBC::DriverBase
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_DRIVERBASE_H_
#define __JSCPPDBC_DRIVERBASE_H_

#include "Ptr.h"
#include "PreparedStatment.h"

namespace JsCPPDBC {

	class EntityBase;
	class EntityListBase;
	class DriverBase
	{
	public:
		virtual ~DriverBase() { }
		virtual int execute(const char *query) = 0;
		virtual int close(void) = 0;

		virtual Ptr<PreparedStatment> createSQLQuery(PreparedStatment::Type type, const char *query) = 0;

		virtual Ptr<PreparedStatment> createInsertStmt(EntityBase *entity) = 0;
		virtual Ptr<PreparedStatment> createUpdateStmt(EntityBase *entity) = 0;
		virtual Ptr<PreparedStatment> createSaveStmt(EntityBase *entity) = 0;
		virtual void addParamToStmtForInsert(PreparedStatment *stmt, EntityBase *entity) = 0;
		virtual void addParamToStmtForUpdate(PreparedStatment *stmt, EntityBase *entity) = 0;
		virtual void addParamToStmtForSave(PreparedStatment *stmt, EntityBase *entity) = 0;
	};

}

#endif /* __JSCPPDBC_DRIVERBASE_H_ */