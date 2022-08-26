#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"

#define ACK_TIMER 300     //ACK��ʱ��
#define MAX_SEQ 7         //�������� 
#define DATA_TIMER 2800   //�ط���ʱ��

struct FRAME { 
    unsigned char kind; //FRAME_DATA/FRAME_ACK/FRAME_NAK
    unsigned char ack;  //ACK���
    unsigned char seq;	//����֡���
    unsigned char data[PKT_LEN]; 
    unsigned int  padding;
};

static int phl_ready = 0;						//�����
static int no_nak = 1;
static unsigned char ack_expected = 0;          //���ʹ����½�
static unsigned char next_frame_to_send = 0;    //���ʹ����Ͻ� + 1
static unsigned char frame_expected = 0;        //���մ���
static unsigned char nbuffered = 0;             //��ǰ���ͻ�����Ŀ��nbuffered����С�ڵ���MAX_SEQ
static unsigned char out_buf[MAX_SEQ + 1][PKT_LEN], in_buf[PKT_LEN]; //���ͻ���ͽ��ջ���

static int between(unsigned char a, unsigned char b, unsigned char c) 
{//�ж�b�Ƿ�����a��c������
	return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}

static void put_frame(unsigned char *frame, int len)
{//���CRCУ��λ���������
    *(unsigned int *)(frame + len) = crc32(frame, len);
    send_frame(frame, len + 4);
    phl_ready = 0;
}

static void send_3frame(unsigned char frame_kind, 
					    unsigned char frame_nr, 
					    unsigned char frame_expected, 
					    unsigned char buffer[][PKT_LEN])
{
    struct FRAME s;
	s.kind = frame_kind;
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);//�����ϴ��յ���֡���

	if (frame_kind == FRAME_DATA)
	{//��������֡
		s.seq = frame_nr;//����֡�����
		memcpy(s.data, buffer[frame_nr], PKT_LEN);//��֡��������ֵ
		dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.data);
		put_frame((unsigned char *)&s, 3 + PKT_LEN);//����3���������ֽڣ����֡���ȼ�3
		start_timer(frame_nr, DATA_TIMER);
	}
	else if (frame_kind == FRAME_NAK)
	{//����NAK֡
		no_nak = 0;
		dbg_frame("Send NAK  %d\n", s.ack);
		put_frame((unsigned char *)&s, 2); // kind+ack,1+1=2
	}
	else if (frame_kind == FRAME_ACK)
	{//����ACK֡
		dbg_frame("Send ACK  %d\n", s.ack);
		put_frame((unsigned char *)&s, 2); // kind+ack,1+1=2
	}

	phl_ready = 0;
	stop_ack_timer(); //ACK��ʱ��ֹͣ,�Ͼ��Ѿ�����ȥ��
}

int main(int argc, char **argv)
{
    int event, arg;
    struct FRAME f;
    int len = 0;
	int i = 0;//iterator

    protocol_init(argc, argv); 
    lprintf("Designed by LXS, build: " __DATE__"  "__TIME__"\n");
    enable_network_layer();

    while(1) 
	{
        event = wait_for_event(&arg);
        switch (event) 
		{
			case NETWORK_LAYER_READY://���������ķ���
				dbg_event("Network_Layer_Ready;\n");
				get_packet(out_buf[next_frame_to_send]); //����������һ�����ݰ�
				nbuffered++;
				dbg_frame("----Send DATA %d %d ;\n", next_frame_to_send, (frame_expected + MAX_SEQ) % (MAX_SEQ + 1));
				send_3frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
				next_frame_to_send = (next_frame_to_send + 1) % (MAX_SEQ + 1);
				break;

			case PHYSICAL_LAYER_READY:
				phl_ready = 1;
				break;

			case FRAME_RECEIVED: 
				dbg_event("Frame_Received;\n");
				len = recv_frame((unsigned char *)&f, sizeof f); //��������յ�һ֡,lenΪ�յ���֡�ĳ���
				if (len < 5 || crc32((unsigned char *)&f, len) != 0) 
				{//���ִ���
					dbg_frame("****Receiver Error , Bad CRC checksum;\n");
					if (no_nak)
					{
						dbg_frame("----Send NAK %d ;\n", (frame_expected + MAX_SEQ) % (MAX_SEQ + 1));
						send_3frame(FRAME_NAK, 0, frame_expected, out_buf);
					}
					break;
				}
				while (between(ack_expected, f.ack, next_frame_to_send)) 
				{//�ۼ�ȷ��
					nbuffered--;
					stop_timer(ack_expected);
					ack_expected = (ack_expected + 1) % (MAX_SEQ + 1);
				}
				
				if (f.kind == FRAME_DATA)
				{//�յ���������֡
					dbg_frame("----Recv DATA %d %d , ID %d\n", f.seq, f.ack, *(short *)f.data);
					if ((f.seq != frame_expected) && no_nak) // ����֡������Ҫ������֡��δ���͹�NAK������NAK֡
					{
						dbg_frame("----Send NAK %d ;\n", (frame_expected + MAX_SEQ) % (MAX_SEQ + 1));
						send_3frame(FRAME_NAK, 0, frame_expected, out_buf);
					}
					else
						start_ack_timer(ACK_TIMER);
					if (f.seq == frame_expected) //�յ���֡���ڽ��ܴ�����
					{
						dbg_frame("Recv DATA %d %d, ID %d\n", f.seq, f.ack, *(short *)f.data);
						memcpy(in_buf, f.data, len - 7); //Ҫ�õ�֡�е����ݣ�Ҫȥ��3�ֽڵĿ����ֶκ�4�ֽڵ�CRCУ���
						put_packet(in_buf, len - 7); //�����ݰ����������
						no_nak = 1;
						frame_expected = (frame_expected + 1) % (MAX_SEQ + 1);
						start_ack_timer(ACK_TIMER);
					}
				}
				
				if ((f.kind == FRAME_NAK) 
					 && 
				     between(ack_expected,(f.ack + 1) % (MAX_SEQ + 1), next_frame_to_send)) 
				{//�յ���NAK֡�������е�֡Ҫȫ���ط�
					dbg_frame("Recv NAK %d\n", f.ack);
					next_frame_to_send = ack_expected;
					for (i = 1; i <= nbuffered; i++)
					{
						send_3frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
						next_frame_to_send = (next_frame_to_send + 1) % (MAX_SEQ + 1);
					}
				}
				
				if (f.kind == FRAME_ACK) 
				//�յ�����ACK֡����ACK�Ĵ��������������
					dbg_frame("Recv ACK  %d\n", f.ack);
				break;

			case DATA_TIMEOUT://��ʱ����ʱ�������ڻ�������֡Ҫ�ط�
				dbg_event("---- DATA %d timeout\n", arg); 
				next_frame_to_send = ack_expected;//����
				for (i = 1; i <= nbuffered; i++)
				{//�������ڲ�ȫ���ط�
					send_3frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
					next_frame_to_send = (next_frame_to_send + 1) % (MAX_SEQ + 1);
				}
				break;
				
			case ACK_TIMEOUT://ACK��ʱ
				dbg_event("**** ACK %d timeout\n",arg);
				send_3frame(FRAME_ACK, 0, frame_expected, out_buf);//�ط�
				break;
				
		}

        if (nbuffered < MAX_SEQ && phl_ready)
            enable_network_layer();
        else
            disable_network_layer();
   }
}
