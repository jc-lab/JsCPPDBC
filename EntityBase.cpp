/**
 * @file	EntityBase.h
 * @class	JsCPPDBC::EntityBase
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#include "EntityBase.h"

namespace JsCPPDBC {

	EntityBase::EntityBase(const char *tableName)
		: _persist_status(DETACH)
	{
		_jsh_tblname = tableName;
		_jsh_idCol = NULL;
	}

	EntityBase::~EntityBase()
	{
	}

	std::string &EntityBase::getTblName()
	{
		return this->_jsh_tblname;
	}

	const EntityColumn* EntityBase::getIdColumn()
	{
		for (std::map<std::string, EntityColumn>::const_iterator iter = _jsh_columns.begin(); iter != _jsh_columns.end(); iter++)
		{
			if (iter->second.isId)
			{
				_jsh_idCol = &iter->second;
				return _jsh_idCol;
			}
		}
		return NULL;
	}

	void EntityBase::setInsertRowId(int64_t rowid)
	{
		const EntityColumn *idCol = getIdColumn();
		switch (idCol->type) {
		case EntityColumn::TYPE_SINT8:
		case EntityColumn::TYPE_UINT8:
		{
			int8_t *buffer = (int8_t*)idCol->buffer;
			*buffer = (int8_t)rowid;
			break;
		}
		case EntityColumn::TYPE_SINT16:
		case EntityColumn::TYPE_UINT16:
		{
			int16_t *buffer = (int16_t*)idCol->buffer;
			*buffer = (int16_t)rowid;
			break;
		}
		case EntityColumn::TYPE_SINT32:
		case EntityColumn::TYPE_UINT32:
		{
			int32_t *buffer = (int32_t*)idCol->buffer;
			*buffer = (int32_t)rowid;
			break;
		}
		case EntityColumn::TYPE_SINT64:
		case EntityColumn::TYPE_UINT64:
		{
			int64_t *buffer = (int64_t*)idCol->buffer;
			*buffer = rowid;
			break;
		}
		}
	}

	void EntityBase::setPersistStatus(PersistStatus status)
	{
		this->_persist_status = status;
	}

	PersistStatus EntityBase::getPersistStatus()
	{
		return this->_persist_status;
	}

	EntityColumn &EntityBase::setColumn(const char *name, bool &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_BOOL, &object, sizeof(object));
		object = false;
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, int8_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_SINT8, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, uint8_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_UINT8, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, int16_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_SINT16, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, uint16_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_UINT16, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, int32_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_SINT32, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, uint32_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_UINT32, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, int64_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_SINT64, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, uint64_t &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_UINT64, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, float &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_FLOAT, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, double &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_DOUBLE, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, std::string &object) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_STRING, &object, sizeof(object));
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, std::vector<char> &object, size_t size) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_BLOB_VECTOR, &object, size);
		return _jsh_columns[name];
	}
	EntityColumn &EntityBase::setColumn(const char *name, void* &buffer, size_t size) {
		_jsh_columns[name] = EntityColumn(name, EntityColumn::TYPE_BLOB_BUF, &buffer, size);
		return _jsh_columns[name];
	}

}
