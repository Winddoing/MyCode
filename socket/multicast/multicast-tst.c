/*#############################################################
 *     File Name	: multicast-tst.c
 *     Author		: wqshao
 *     Created Time	: 2018年06月14日 星期四 14时10分05秒
 *     Description	:
 *############################################################*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFLEN 255

#if 0
#define VX_RTP_MUL_IP	"239.0.0.11"
#define VX_RTP_LOCAL_PORT 15550
#else
#define VX_RTP_MUL_IP	"225.0.0.37"
#define VX_RTP_LOCAL_PORT 12345
#endif

static int socket_set_nonblock(int s)
{
	int flags, res;

	flags = fcntl(s, F_GETFL, 0);
	if (flags < 0) {
		flags = 0;
	}

	res = fcntl(s, F_SETFL, flags | O_NONBLOCK);
	if (res < 0) {
		printf( "fcntl return err:%d!\n", res);
		return -1;
	}

	return 0;
}

int main (int argc, char **argv)
{
	int fd = -1;
	int ret = -1, n = 0, sock_len = 0;
	char recmsg[BUFLEN + 1];
	fd_set rfds;
	struct sockaddr_in addr;
	struct timeval tv;
	struct ip_mreq mreq;
	int yes=1;
	int loop = 0;

	/*UDP*/
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1) {
		printf("create udp socket error %d", -errno);
		return -1;
	}

	socket_set_nonblock(fd);

	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(VX_RTP_LOCAL_PORT);

	ret = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		printf("===> func: %s, line: %d, bind err %d\n", __func__, __LINE__, -errno);
		goto failed;
	}

	ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(yes));
	if (ret < 0) {
		printf("===> func: %s, line: %d xxxxxxxxxxxxxx\n", __func__, __LINE__);
		goto failed;
	}

	if( setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop)) < 0 ){
		printf("===> func: %s, line: %d xxxxxxxxxxxxxx\n", __func__, __LINE__);
		goto failed;
	}

	mreq.imr_multiaddr.s_addr=inet_addr(VX_RTP_MUL_IP);
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);

	ret = setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	if (ret < 0)
	{
		printf("===> func: %s, line: %d, setsockopt err %d\n", __func__, __LINE__, ret);
		goto failed;
	}
	printf("create rtp udp socket %d ok\n",fd);

	sock_len = sizeof(addr);
	tv.tv_sec = 10; //加大超时时间 1s timeout
	tv.tv_usec = 0;

#if 0
	ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
	if (ret) {
		printf("set socket rcv timeout err %d\n", -errno);
		goto failed;
	}
#endif

	/* 循环接收网络上来的组播消息 */
	for (;;)
	{
#if 1
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		ret = select(fd + 1, &rfds, NULL, NULL, &tv);
		if(-1 == ret) {
			printf("===> func: %s, line: %d, Socket select error\n", __func__, __LINE__);
			return -1;
		}
		if(0 == ret) {
			printf("===> func: %s, line: %d, select timeout\n", __func__, __LINE__);
			continue;
		}
#endif
		struct sockaddr_in tmp_addr;
		socklen_t addr_len = sizeof(tmp_addr);
		bzero (recmsg, BUFLEN + 1);

eagain:
/*		n = recvfrom(fd, recmsg, BUFLEN, 0, (struct sockaddr*) &addr, (socklen_t*)&sock_len);*/
/*		n = recvfrom(fd, recmsg, BUFLEN, 0, (struct sockaddr*) &tmp_addr, &addr_len);*/
		n = recv(fd, recmsg, BUFLEN, 0);
		if (n < 0) {
			printf("recvfrom err in udptalk!, n: %d, errno: %d\n", n, -errno);
			if(EAGAIN == errno)
				goto eagain;
			else
				return -1;
		} else if (n == 0) {
			printf("recv data siez: %d\n", n);
		} else {
			/* 成功接收到数据报 */
			recmsg[n] = 0;
			printf ("s: %d, peer:%s\n", n, recmsg);
		}

	}

	return 0;

failed:
	if(fd > 0)
		close(fd);
	return -1;
}
