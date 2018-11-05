/**
 * @file	EntityBase.cpp
 * @class	JsCPPDBC::EntityBase
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_ENTITYBASE_H__
#define __JSCPPDBC_ENTITYBASE_H__

#include <string>
#include <vector>
#include <stdint.h>

#include <map>
#include <string>

#include "EntityColumn.h"

namespace JsCPPDBC {

	class EntityBase
	{
	protected:
		std::string _jsh_tblname;
		std::string _jsh_nil;
		const EntityColumn *_jsh_idCol;

	public:
		std::map<std::string, EntityColumn> _jsh_columns;

		EntityBase(const char *tableName);
		virtual ~EntityBase();
		std::string &getTblName();
		const EntityColumn* getIdColumn();

		void setInsertRowId(int64_t rowid);

		EntityColumn &setColumn(const char *name, bool &object);
		EntityColumn &setColumn(const char *name, int8_t &object);
		EntityColumn &setColumn(const char *name, uint8_t &object);
		EntityColumn &setColumn(const char *name, int16_t &object);
		EntityColumn &setColumn(const char *name, uint16_t &object);
		EntityColumn &setColumn(const char *name, int32_t &object);
		EntityColumn &setColumn(const char *name, uint32_t &object);
		EntityColumn &setColumn(const char *name, int64_t &object);
		EntityColumn &setColumn(const char *name, uint64_t &object);
		EntityColumn &setColumn(const char *name, float &object);
		EntityColumn &setColumn(const char *name, double &object);
		EntityColumn &setColumn(const char *name, std::string &object);
		EntityColumn &setColumn(const char *name, std::vector<char> &object, size_t size);
		EntityColumn &setColumn(const char *name, void* &buffer, size_t size);
	};

}

#endif /* __JSCPPDBC_ENTITYBASE_H__ */
