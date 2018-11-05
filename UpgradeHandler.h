/**
 * @file	UpgradeHandler.h
 * @class	JsCPPDBC::UpgradeHandler
 * @author	Jichan (development@jc-lab.net / http://ablog.jc-lab.net/category/JsCPPDBC )
 * @date	2018/11/05
 * @copyright Apache License 2.0
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#ifndef __JSCPPDBC_UPGRADEHANDLER_H__
#define __JSCPPDBC_UPGRADEHANDLER_H__

namespace JsCPPDBC {

	class UpgradeHandler
	{
	public:
		virtual ~UpgradeHandler() { }

		/**
		* Upgrade scheme
		* @return newVersion. if newVersion less than DBVERSION, Will be recalled onUpgradeScheme method after reopening the database.
		*/
		virtual int onUpgradeScheme(int oldversion, int DBVERSION) { }

		/**
		* Upgrade data
		* The method will be called once after called when all of onUpgradeScheme methods.
		*/
		virtual void onUpgradeData(int oldversion) { }
	};

}

#endif /* __JSCPPDBC_UPGRADEHANDLER_H__ */
