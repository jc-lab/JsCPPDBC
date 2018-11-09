/**
 * @file	Ptr.h
 * @class	JsCPPDBC::Ptr
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_PTR_H__
#define __JSCPPDBC_PTR_H__

#include <assert.h>
#include <stdio.h>

namespace JsCPPDBC {

	namespace Internal {
		class PtrManager {
		public:
			int refcnt;
			virtual void destroy() = 0;
			PtrManager() { this->refcnt = 1; }
			virtual ~PtrManager() { }
			int addRef() const {
				int *prefcnt = (int*)(&this->refcnt);
				return ++(*prefcnt);
			}
		};
		template <typename U>
		class PtrManagerImpl : public PtrManager {
		public:
			U *ptr;
			void destroy() override {
				if (ptr != NULL) {
					delete ptr;
					ptr = NULL;
				}
			}
			PtrManagerImpl(U *_ptr) {
				this->ptr = _ptr;
			}
			virtual ~PtrManagerImpl() {
				destroy();
			}
		};
	};

	class PtrBase {
	protected:
		virtual ~PtrBase() {}
		Internal::PtrManager *m_manager;
		void setManagedPointer(const PtrBase &object) {
			m_manager = object.m_manager;
			if (object.m_manager)
				object.m_manager->addRef();
		}
		int delRef() {
			if (m_manager)
			{
				int refcnt = --m_manager->refcnt;
				if (refcnt == 0)
				{
					delete m_manager;
					m_manager = NULL;
				}
				return refcnt;
			}
			else
				return 0;
		}
	};

	template<typename T>
	class Ptr : public PtrBase
	{
	private:
		T *m_ptr;

	public:
		Ptr() {
			m_manager = NULL;
			m_ptr = NULL;
		}
		virtual ~Ptr() {
			resetPtr();
		}

		/*Ptr(Ptr &object) {
			m_ptr = NULL;
			m_manager = NULL;
			setManagedPointer(object);
			if (m_manager)
				m_ptr = ((Internal::PtrManagerImpl<T>*)m_manager)->ptr;
		}*/
		Ptr(const Ptr &object) {
			m_ptr = NULL;
			m_manager = NULL;
			setManagedPointer(object);
			if (m_manager)
				m_ptr = ((Internal::PtrManagerImpl<T>*)m_manager)->ptr;
		}
		Ptr& operator=(Ptr &object) {
			resetPtr();
			setManagedPointer(object);
			if (m_manager)
				m_ptr = ((Internal::PtrManagerImpl<T>*)m_manager)->ptr;
			return *this;
		}

		template<class U>
		Ptr(Ptr<U> &object) {
			m_ptr = NULL;
			m_manager = NULL;
			setManagedPointer(object);
			if(m_manager)
				m_ptr = ((Internal::PtrManagerImpl<U>*)m_manager)->ptr;
		}
		template<class U>
		Ptr<U>& operator=(Ptr<U> &object) {
			resetPtr();
			setManagedPointer(object);
			if (m_manager)
				m_ptr = ((Internal::PtrManagerImpl<U>*)m_manager)->ptr;
			return *this;
		}

		template<class U>
		explicit Ptr(U *ptr) {
			m_ptr = ptr;
			m_manager = new Internal::PtrManagerImpl<U>(ptr);
		}
		template<class U>
		Ptr<U>& operator=(U *ptr) {
			resetPtr();
			m_ptr = ptr;
			m_manager = new Internal::PtrManagerImpl<U>(ptr);
			return *this;
		}
		explicit Ptr(int ptr) {
			assert(ptr == 0);
			m_ptr = NULL;
			m_manager = NULL;
		}
		
		T* operator->() const { return (T*)m_ptr; }
		T& operator*() const { return *(T*)m_ptr; }
		//explicit T* operator() { return m_ptr; }
		T* getPtr() const { return m_ptr; }

		void resetPtr() {
			delRef();
			this->m_ptr = NULL;
			this->m_manager = NULL;
		}

	private:
		explicit Ptr(Ptr *ptr) {
			assert(false);
		}
	};

}

#endif /* __JSCPPDBC_PTR_H__ */
