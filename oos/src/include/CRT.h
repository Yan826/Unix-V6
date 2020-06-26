#ifndef CRT_H
#define CRT_H

#include "TTy.h"

class CRT
{
	/* Const Member */
public:
	/* ��ʾ���ƼĴ���I/O�˿ڵ�ַ */
	static const unsigned short VIDEO_ADDR_PORT = 0x3d4;	/* ��ʾ���������Ĵ����˿ں� */
	static const unsigned short VIDEO_DATA_PORT = 0x3d5;	/* ��ʾ�������ݼĴ����˿ں� */
	
	/* ��Ļ��СΪ80 * 25 */
	static const unsigned int COLUMNS = 80;
	static unsigned int ROWS;
	
	static const unsigned short COLOR = 0x0F00;		/* char in white color */

	/* Functions */
public:
	/* �������������е������������Ļ�� */
	static void CRTStart(TTy* pTTy,int ntty);

	/* �ı���λ�� */
	static void MoveCursor(unsigned int x, unsigned int y);

	/* ���д����ӳ��� */
	static void NextLine(int ntty);

	/* �˸����ӳ��� */
	static void BackSpace(int ntty);
	
	/* Tab�����ӳ��� */
	static void Tab(int ntty);

	/* ��ʾ�����ַ� */
	static void WriteChar(char ch,int ntty);

	/* �����Ļ */
	static void ClearScreen(int ntty);
	/*ctrl + tת���豸*/
	static void FreshCurse(int ntty);

	/* Members */
public:
	static unsigned short* m_VideoMemory;
	static unsigned int m_CursorX;
	static unsigned int m_CursorY;
	static unsigned int m1_CursorX;
	static unsigned int m1_CursorY;

	/* ָ�������������е�ǰҪ������ַ� */
	static char* m_Position;
	static char* m1_Position;
	/* ָ��������������δȷ�ϵ�����ַ��Ŀ�ʼ����������ͨ��Backspace��ɾ�������ݣ�
	 * ���һ���س�֮ǰ������Ϊ��ȷ�����ݣ����ɱ�Backspace��ɾ����
	 */
	static char* m_BeginChar;
	static char* m1_BeginChar;
};

#endif