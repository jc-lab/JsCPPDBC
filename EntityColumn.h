/**
 * @file	EntityColumn.h
 * @class	JsCPPDBC::EntityColumn
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_ENTITYCOLUMN_H__
#define __JSCPPDBC_ENTITYCOLUMN_H__

namespace JsCPPDBC {

	struct EntityColumn
	{
		enum Type {
			TYPE_BOOL = 0x0001,
			TYPE_SINT8 = 0x0101,
			TYPE_UINT8 = 0x0201,
			TYPE_SINT16 = 0x0102,
			TYPE_UINT16 = 0x0202,
			TYPE_SINT32 = 0x0104,
			TYPE_UINT32 = 0x0204,
			TYPE_SINT64 = 0x0108,
			TYPE_UINT64 = 0x0208,
			TYPE_FLOAT = 0x0404,
			TYPE_DOUBLE = 0x0408,
			TYPE_STRING = 0x0800,
			TYPE_BLOB_VECTOR = 0x1001,
			TYPE_BLOB_BUF = 0x1002
		};

		enum GeneratedValue {
			NO_GENERATE = 0,
			IDENTITY
		};

		std::string name;
		GeneratedValue generatedValue;
		bool isId;
		Type type;
		void *buffer;
		size_t size;

		EntityColumn() {
			this->isId = false;
			this->generatedValue = NO_GENERATE;
			this->type = TYPE_BOOL;
			this->buffer = NULL;
			this->size = 0;
		}

		EntityColumn(const char *_name, Type _type, void *_buffer, size_t _size) {
			this->isId = false;
			this->generatedValue = NO_GENERATE;
			this->name = _name;
			this->type = _type;
			this->buffer = _buffer;
			this->size = _size;
		}

		EntityColumn &Id(bool _isId) {
			this->isId = _isId;
			return *this;
		}

		EntityColumn &setGeneratedValue(GeneratedValue _generatedValue) {
			this->generatedValue = _generatedValue;
			return *this;
		}

		bool isInt() {
			return (this->type & 0x0300) ? true : false;
		}
		bool isUnsigned() {
			return ((this->type & 0x0300) == 0x0200);
		}
		bool isReal() {
			return (this->type & 0x0400) ? true : false;
		}
		bool isFloat() {
			return ((this->type & 0x04ff) == 0x0404);
		}
		bool isDouble() {
			return ((this->type & 0x04ff) == 0x0408);
		}
		bool isString() {
			return (this->type & 0x0800) ? true : false;
		}
	};

}

#endif /* __JSCPPDBC_ENTITYLIST_H__ */
