/*
 * service.hh
 *
 *  Created on: 19/03/2018
 *      Author: joao
 */

#ifndef INC_PROCMGR_HH_
#define INC_PROCMGR_HH_

class procMgr
{
public:
		virtual void start();
		virtual ~procMgr();
private:
		procMgr();

};



#endif /* SERVICE_HH_ */
