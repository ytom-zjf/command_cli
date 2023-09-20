#include "ring_buffer.h"

/// @brief 初始化环形缓冲区
/// @param buf 
void ring_buffer_init(ring_buffer_t *buf)
{
	buf->pW = 0;
	buf->pR = 0;
	memset(buf->buffer, 0, RING_BUFFER_MAX_SIZE);
}

/// @brief 写缓冲区
/// @param c 
/// @param buf 
void ring_buffer_write(char c, ring_buffer_t *buf)
{
	int i = (buf->pW + 1) % RING_BUFFER_MAX_SIZE;		//127->0
	if (i != buf->pR) 		//未写满则继续写入
	{
		buf->buffer[buf->pW] = c;
		buf->pW = i;
	}
}

/// @brief 读缓冲区
/// @param c 
/// @param buf 
/// @return 读取失败返回-1，读取成功返回0
int ring_buffer_read(char *c, ring_buffer_t *buf)
{
	if(buf->pR == buf->pW)	//缓冲区为空
	{
		return -1;
	}
	else
	{
		*c = buf->buffer[buf->pR];
		buf->pR = (buf->pR + 1) % RING_BUFFER_MAX_SIZE;
		return 0;
	}
}