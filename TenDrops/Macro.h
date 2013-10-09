//
// Module			: Macro.h
// Author			: bss
// Project			: Smart3D
// State			:
// Creation Date	: 2013-04-01
// Last Modification: 2013-10-09
// Description		: Macros.
//

#ifndef _MACRO_H_
#define _MACRO_H_


#ifndef SAFE_DELETE
// ��ȫɾ�����൱�� delete
#define SAFE_DELETE(P) if (P != nullptr) { delete P; P = nullptr; }
#endif


#ifndef SAFE_DELETE_ARRAY
// ��ȫɾ�����൱�� delete[]
#define SAFE_DELETE_ARRAY(P) if  (P != nullptr) { delete[] P; P = nullptr; }
#endif


#ifndef SAFE_DELETE_POINTER_ARRAY
// ��ȫɾ�����൱���� delete ��Ա�� delete[]
#define SAFE_DELETE_POINTER_ARRAY(P, size)	\
    if  (P != nullptr)	\
    {	\
        for (int indexOfP = 0; indexOfP < size; indexOfP++)	\
        {	\
            SAFE_DELETE(P[indexOfP]);	\
        }	\
        delete[] P;\
        P = nullptr;\
    }
#endif


#endif
