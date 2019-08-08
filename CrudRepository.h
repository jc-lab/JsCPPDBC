/**
 * @file	CrudRepository.h
 * @class	JsCPPDBC::CrudRepository
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_CRUDREPOSITORY_H__
#define __JSCPPDBC_CRUDREPOSITORY_H__

#include "DriverBase.h"
#include "EntityBase.h"
#include "Repository.h"
#include <stdio.h>
#include <string.h>

namespace JsCPPDBC {

	class SQLSession;

	template <class TEntity>
	class CrudRepository : public Repository
	{
	public:
		CrudRepository(SQLSession *sqlSession) : 
			Repository(sqlSession, sqlSession->getDriver())
		{
			TEntity tempEntity;
			EntityBase *entity = &tempEntity;
			const std::string &tblName = entity->getTblName();
			const EntityColumn *idColName = entity->getIdColumn();
			const char zero = 0;

			char sql[256];

			/******************** Create ********************/
			{
				Ptr<PreparedStatment> stmt = m_driver->createInsertStmt(entity);
				if (stmt.getPtr() != NULL) {
					addMethod("*CRUDREPOSITOREY:insert", stmt);
				}
			}

			/******************** Read ********************/
#ifdef _CRT_INSECURE_DEPRECATE
			sprintf_s(sql, "SELECT * FROM `%s`", tblName.c_str());
#else
			sprintf(sql, "SELECT * FROM `%s`", tblName.c_str());
#endif
			addMethod("*CRUDREPOSITOREY:findAll", PreparedStatment::TYPE_FETCH, sql);

#ifdef _CRT_INSECURE_DEPRECATE
			sprintf_s(sql, "SELECT * FROM `%s` WHERE `%s`=?", tblName.c_str(), idColName->name.c_str());
#else
			sprintf(sql, "SELECT * FROM `%s` WHERE `%s`=?", tblName.c_str(), idColName->name.c_str());
#endif
			addMethod("*CRUDREPOSITOREY:findById", PreparedStatment::TYPE_FETCH, sql);

			/******************** Update ********************/
			{
				Ptr<PreparedStatment> stmt = m_driver->createUpdateStmt(entity);
				if (stmt.getPtr() != NULL) {
					addMethod("*CRUDREPOSITOREY:update", stmt);
				}
			}

			/******************** Delete ********************/
#ifdef _CRT_INSECURE_DEPRECATE
			sprintf_s(sql, "DELETE FROM `%s`", tblName.c_str());
#else
			sprintf(sql, "DELETE FROM `%s`", tblName.c_str());
#endif
			addMethod("*CRUDREPOSITOREY:deleteAll", PreparedStatment::TYPE_UPDATE, sql);

#ifdef _CRT_INSECURE_DEPRECATE
			sprintf_s(sql, "DELETE FROM `%s` WHERE `%s`=?", tblName.c_str(), idColName->name.c_str());
#else
			sprintf(sql, "DELETE FROM `%s` WHERE `%s`=?", tblName.c_str(), idColName->name.c_str());
#endif
			addMethod("*CRUDREPOSITOREY:deleteById", PreparedStatment::TYPE_UPDATE, sql);

			/******************** Save ********************/
			{
				Ptr<PreparedStatment> stmt = m_driver->createSaveStmt(entity);
				if (stmt.getPtr() != NULL) {
					addMethod("*CRUDREPOSITOREY:save", stmt);
				}
			}
		}
		virtual ~CrudRepository()
		{
		}

		Ptr< EntityList<TEntity> > findAll() {
			Ptr< EntityList<TEntity> > result(new EntityList<TEntity>());
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:findAll"];

			stat->reset();
			stat->execute();
			stat->fetchRows(result.getPtr());

			return result;
		}

		bool findById(TEntity *entity) {
			const EntityColumn *idCol = entity->getIdColumn();
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:findById"];
			
			stat->reset();
			stat->addParam(*idCol);
			stat->execute();
			return (stat->fetchRow(entity));
		}

		void deleteAll() {
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:deleteAll"];
			stat->reset();
			stat->execute();
		}

		void deleteById(TEntity *entity) {
			const EntityColumn *idCol = entity->getIdColumn();
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:deleteAll"];
			stat->reset();
			stat->addParam(*idCol);
			stat->execute();
			entity->setPersistStatus(DETACH);
		}

		void insert(TEntity *entity) {
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:insert"];
			int64_t rowid;
			stat->reset();
			m_driver->addParamToStmtForInsert(stat.getPtr(), entity);
			stat->execute();
			rowid = stat->insert_rowid();
			entity->setInsertRowId(rowid);
		}

		void update(TEntity *entity) {
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:update"];
			int64_t rowid;
			stat->reset();
			m_driver->addParamToStmtForUpdate(stat.getPtr(), entity);
			stat->execute();
			rowid = stat->insert_rowid();
			//entity->setInsertRowId(rowid);
		}

		void save(TEntity *entity) {
			if (entity->getPersistStatus() == ATTACH) {
				update(entity);
				return;
			}
			Ptr< PreparedStatment > stat = m_stats["*CRUDREPOSITOREY:save"];
			int64_t rowid;
			stat->reset();
			m_driver->addParamToStmtForSave(stat.getPtr(), entity);
			stat->execute();
			rowid = stat->insert_rowid();
			entity->setInsertRowId(rowid);
		}
	};

}

#endif /* __JSCPPDBC_CRUDREPOSITORY_H__ */
