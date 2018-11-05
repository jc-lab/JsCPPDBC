/**
 * @file	EntityList.h
 * @class	JsCPPDBC::EntityList
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_ENTITYLIST_H__
#define __JSCPPDBC_ENTITYLIST_H__

#include "Ptr.h"
#include <list>

namespace JsCPPDBC {

	class EntityListBase {
	public:
		std::list< Ptr<EntityBase> > list;
		virtual ~EntityListBase() { }
		virtual Ptr<EntityBase> createEntity() = 0;
	};

	template<class TEntity>
	class EntityList : public EntityListBase
	{
	public:
		virtual Ptr<EntityBase> createEntity() {
			return Ptr<EntityBase>(new TEntity());
		}
	};

}

#endif /* __JSCPPDBC_ENTITYLIST_H__ */
