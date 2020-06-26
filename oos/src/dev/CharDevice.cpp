#include "CharDevice.h"
#include "Utility.h"
#include "Kernel.h"
#include"CRT.h"
#include"TTy.h"
#include "video.h"
/*==============================class CharDevice===============================*/
CharDevice::CharDevice()
{
	this->m_TTy[0] = NULL;
	this->m_TTy[1] = NULL;
}

CharDevice::~CharDevice()
{
	//nothing to do here
}

void CharDevice::Open(short dev, int mode)
{
	Utility::Panic("ERROR! Base Class: CharDevice::Open()!");
}

void CharDevice::Close(short dev, int mode)
{
	Utility::Panic("ERROR! Base Class: CharDevice::Close()!");
}

void CharDevice::Read(short dev)
{
	Utility::Panic("ERROR! Base Class: CharDevice::Read()!");
}

void CharDevice::Write(short dev)
{
	Utility::Panic("ERROR! Base Class: CharDevice::Write()!");
}

void CharDevice::SgTTy(short dev, TTy* pTTy)
{
	Utility::Panic("ERROR! Base Class: CharDevice::SgTTy()!");
}


/*==============================class ConsoleDevice===============================*/
/* 
 * ���ﶨ��������ConsoleDevice�Ķ���ʵ����
 * ��ʵ��������override���ַ��豸������
 * Open(), Close(), Read(), Write()���麯����
 */
ConsoleDevice g_ConsoleDevice;

extern TTy g_TTy[2];
ConsoleDevice::ConsoleDevice()
{
	//nothing to do here
}

ConsoleDevice::~ConsoleDevice()
{
	//nothing to do here
}
void ConsoleDevice::Open(short dev, int mode)
{
	short minor = Utility::GetMinor(dev);//��ȡ���豸��
	User& u = Kernel::Instance().GetUser();
	if ( minor != 0 && minor != 1 )	/* �ж�console */
	{
		return;
	}
/* ��ʼ��TTy */
	if ( NULL == this->m_TTy[minor] )
	{
		this->m_TTy[minor] = &g_TTy[minor];
		m_TTy[minor]->ntty = minor;
	}
/*�����һ�δ�����豸*/
	if(NULL == u.u_procp->p_ttyp)
	{
		u.u_procp->p_ttyp = this->m_TTy[minor];
	}


	/* �ַ��豸ģʽ */
	if ( (this->m_TTy[minor]->t_state & TTy::ISOPEN) == 0 )
	{
		this->m_TTy[minor]->t_state = TTy::ISOPEN | TTy::CARR_ON;
		this->m_TTy[minor]->t_flags = TTy::ECHO;
		this->m_TTy[minor]->t_erase = TTy::CERASE;
		this->m_TTy[minor]->t_kill = TTy::CKILL;
	}
}

void ConsoleDevice::Close(short dev, int mode)
{
	//nothing to do here
}

void ConsoleDevice::Read(short dev)
{
	short minor = Utility::GetMinor(dev);
	if ( 0 == minor || 1 == minor)
		this->m_TTy[minor]->TTRead();	/* �ж�console */

}

void ConsoleDevice::Write(short dev)
{
	short minor = Utility::GetMinor(dev);
	if ( 0 == minor || 1 == minor)
		this->m_TTy[minor]->TTWrite();	/*�ж�console */
}

void ConsoleDevice::SgTTy(short dev, TTy *pTTy)
{
}
