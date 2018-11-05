/**
 * @file	SQLException.h
 * @class	JsCPPDBC::exception::SQLException
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_EXCEPTION_SQLEXCEPTION_H__
#define __JSCPPDBC_EXCEPTION_SQLEXCEPTION_H__

#include <exception>
#include <string>

namespace JsCPPDBC {
	namespace exception {
		class SQLException : public std::exception 
		{
		protected:
			std::string message;
			int code;

		public:
			SQLException(const char *_message, int _code) {
				this->message = _message;
				this->code = _code;
			}
			virtual ~SQLException() { }
		};
	}
}

#endif /* __JSCPPDBC_EXCEPTION_SQLEXCEPTION_H__ */
