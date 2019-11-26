#include "RIPEMD160.h"                                                                     

unsigned int RIPEMD_160::F(unsigned int j, unsigned int x, unsigned int y, unsigned int z)  
{
	if (j <= 15)
		return x ^ y^ z;
	else if (j <= 31)
		return (x & y) | (~x & z);
	else if (j <= 47)
		return (x | ~y) ^ z;
	else if (j <= 63)
		return (x & z) | (y & ~z);
	else if (j <= 79)
		return x ^ (y | ~z);
	else
		return 0;
}

unsigned int RIPEMD_160::K1(unsigned int j)                                                 
{
	if (j <= 15)
		return 0x00000000;
	else if (j <= 31)
		return 0x5A827999;
	else if (j <= 47)
		return 0x6ED9EBA1;
	else if (j <= 63)
		return 0x8F1BBCDC;
	else if (j <= 79)
		return 0xA953FD4E;
	else
		return 0;
}

unsigned int RIPEMD_160::K2(unsigned int j)                                                 
{
	if (j <= 15)
		return 0x50A28BE6;
	else if (j <= 31)
		return 0x5C4DD124;
	else if (j <= 47)
		return 0x6D703EF3;
	else if (j <= 63)
		return 0x7A6D76E9;
	else if (j <= 79)
		return 0x00000000;
	else
		return 0;
}

unsigned int RIPEMD_160::inv(unsigned int value)                                            
{
	unsigned int res = 0;                                                                   

	res |= ((value >> 0) & 0xFF) << 24;                                                     
	res |= ((value >> 8) & 0xFF) << 16;                                                     
	res |= ((value >> 16) & 0xFF) << 8;                                                     
	res |= ((value >> 24) & 0xFF) << 0;                                                     

	return res;                                                                             
}

unsigned int RIPEMD_160::bytes_to_uint(char* bytes)                                         
{
	unsigned int res = 0;                                                                   

	res |= ((unsigned int)bytes[3] << 24) & 0xFF000000;                                     
	res |= ((unsigned int)bytes[2] << 16) & 0xFF0000;                                       
	res |= ((unsigned int)bytes[1] << 8) & 0xFF00;                                          
	res |= ((unsigned int)bytes[0] << 0) & 0xFF;                                            

	return res;                                                                             
}

void RIPEMD_160::extension()                                                                //Шаг 1 - Расширение сообщения
{
	bitlen = message.size() * 8;                                                            //Исходная длина сообщения в битах (нужна для шага 2)

	message.push_back((unsigned char)0x80);                                                 //Добавляем в конец сообщения единичный бит

	while ((message.size() * 8) % 512 != 448)                                               //До тех пор, пока длина сообщения не станет равной 448 по модулю 512,
		message.push_back(0);                                                               //Заполняем сообщение нулями

	blocks = (unsigned int)(message.size() / 64) + 1;                                       //Количество блоков для обработки (+1 нужно для блока из 8 байт, в который добавится bitlen)
}

void RIPEMD_160::adding_length()                                                            //Шаг 2 - Добавление длины сообщения
{
	X = new unsigned int*[blocks];                                                          //Выделяем память под массив массивов блоков

	for (unsigned int i = 0; i < blocks; i++)                                               //Пока не кончились блоки                                                
	{
		X[i] = new unsigned int[16];                                                        //Выделяем память под текущий блок

		for (int j = 0; j < (i == blocks - 1 ? 14 : 16); j++)                               //Если это не последний блок, то переносим преобразованное messgae в X,
			X[i][j] = bytes_to_uint(&message[(j * 4) + 64 * i]);                            //Если блок послений, то делаем то же самое, но оставляем 8 байт под bitlen

		if (i == blocks - 1)                                                                //Если это последний блок
		{
			X[i][14] = bitlen & 0xFFFFFFFF;                                                 //То добавляем в него bitlen, причем в виде двух 4-байтовых слов,
			X[i][15] = bitlen >> 32 & 0xFFFFFFFF;                                           //Где первым добавляется слово, содержащее младшие разряды.
		}
	}
}

void RIPEMD_160::initialize_ripemd()                                                        //Шаг 3 - Инициализация RIPEMD буфера
{
	H0 = 0x67452301, H1 = 0xEFCDAB89, H2 = 0x98BADCFE, H3 = 0x10325476, H4 = 0xC3D2E1F0;    //Инициализиуем регистры
}

unsigned int R1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13 };

unsigned int R2[] = { 5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11 };

unsigned int S1[] = { 11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6 };

unsigned int S2[] = { 8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11 };

void RIPEMD_160::message_processing()                                                       //Шаг 4 - Обработка сообщения в блоках
{
	for (unsigned int i = 0; i < blocks; i++)                                               //Цикл блоков сообщения
	{
		A1 = H0, B1 = H1, C1 = H2, D1 = H3, E1 = H4;                                        //Сохраняем значения значения регистров на каждом этапе цикла
		A2 = H0, B2 = H1, C2 = H2, D2 = H3, E2 = H4;                                        //Для двух потоков

																							//Магия
		for (unsigned int j = 0; j < 80; j++)
		{
			T = ROTATE_LEFT((A1 + F(j, B1, C1, D1) + X[i][R1[j]] + K1(j)), S1[j]) + E1;

			A1 = E1, E1 = D1, D1 = ROTATE_LEFT(C1, 10), C1 = B1, B1 = T;

			T = ROTATE_LEFT((A2 + F(79 - j, B2, C2, D2) + X[i][R2[j]] + K2(j)), S2[j]) + E2;

			A2 = E2, E2 = D2, D2 = ROTATE_LEFT(C2, 10), C2 = B2, B2 = T;
		}
		//Конец магии

		T = H1 + C1 + D2;                                                                   //Обновляем значения регистров 
		H1 = H2 + D1 + E2, H2 = H3 + E1 + A2, H3 = H4 + A1 + B2, H4 = H0 + B1 + C2;         //На каждом этапе цикла
		H0 = T;                                                                             //Для двух потоков
	}

	for (unsigned int i = 0; i < blocks; i++)                                               //Пока не кончились блоки
		delete[] X[i];                                                                     //Освобождаем память, выделенную под текущий блок

	delete[] X;                                                                            //Освобождаем память, выделенную под весь массив массивов блоков
}

string RIPEMD_160::ripemd_160(string msg)                                                      
{
	message = msg;
	extension();                                                                            

	adding_length();                                                                        

	initialize_ripemd();                                                                    

	message_processing();                                                                   

	result << hex << inv(H0) << inv(H1) << inv(H2) << inv(H3) << inv(H4);                   

	return result.str();                                                                    
}