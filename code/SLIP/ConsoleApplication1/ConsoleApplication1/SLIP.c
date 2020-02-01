#include <stdio.h>
#include <stdint.h>

#define END        0xC0
#define ESC        0xDB
#define ESC_END    0xDC
#define ESC_ESC    0xDD

uint32_t t_cnt, r_cnt;
uint8_t t_queue[100] = { 0 };
uint8_t r_buff[100] = { 0 };

uint8_t test_data_1[] = { 1, 2, END, 3, ESC };

void send_char(uint8_t c)
{
    t_queue[t_cnt++] = c;
}

uint8_t recv_char(void)
{
    return t_queue[r_cnt++];
}

void send_packet(uint8_t *p, uint32_t len)
{
    send_char(END);

    while (len--)
    {
        switch (*p)

        {
        case END:
            send_char(ESC);
            send_char(ESC_END);
            break;

        case ESC:
            send_char(ESC);
            send_char(ESC_ESC);
            break;
        
        default:
            send_char(*p);
        }

        p++;
    }
    
    send_char(END);
}

uint32_t recv_packet(uint8_t *p, uint32_t len)
{
    uint8_t c;
    uint32_t received = 0;

    while (1)
    {
        c = recv_char();

        switch (c)
        {
        case END:
            if (received)
                return received;
            else
                break;

        case ESC:
            c = recv_char();

            switch (c)
            {
            case ESC_END:
                c = END;
                break;

            case ESC_ESC:
                c = ESC;
                break;
            }
        
        default:
            if(received < len)
                p[received++] = c;
        }
    }
}

void main(void)
{
    uint32_t r_len = 0;
    
    t_cnt = 0;
    r_cnt = 0;
    
    printf("Serial Line Interface Protocol test\n");

    printf("\ntest_data:\n");
    for (uint32_t idx = 0; sizeof(test_data_1) > idx; idx++)
        printf("%02X ", (uint32_t)test_data_1[idx]);
    printf("\n");

    send_packet(&test_data_1[0], sizeof(test_data_1));

    printf("\nsend data:\n");
    for (uint32_t idx = 0; t_cnt > 0; t_cnt--)
        printf("%02X ", (uint32_t)t_queue[idx++]);
    printf("\n");

    r_len = recv_packet(r_buff, sizeof(test_data_1));

    printf("\nreceived data:\n");
    for (uint32_t idx = 0; r_len > 0; r_len--)
        printf("%02X ", (uint32_t)r_buff[idx++]);
    printf("\n\n");
}
