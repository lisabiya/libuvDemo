#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

typedef struct
{
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req)
{
    write_req_t *wr = (write_req_t *)req;
    free(wr->buf.base);
    free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
    buf->base = (char *)malloc(suggested_size);
    buf->len = suggested_size;
}

void echo_write(uv_write_t *req, int status)
{
    if (status)
    {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_write_req(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread > 0)
    {
        write_req_t *req = (write_req_t *)malloc(sizeof(write_req_t));
        fprintf(stderr, "msg %s\n", buf->base);
        free(buf->base);

        char *word = "你好呀";
        // req->buf = uv_buf_init(word, strlen(word));
        unsigned int size = strlen(word);
        req->buf = uv_buf_init((char *)malloc(size), size);
        memcpy(req->buf.base, word, size);

        uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);

        return;
    }
    if (nread < 0)
    {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t *)client, NULL);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status)
{
    if (status < 0)
    {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    fprintf(stderr, "New connection success %d\n", status);
        
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t *)client) == 0)
    {
        fprintf(stderr, "uv_accept");
        uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
    }
    else
    {
        uv_close((uv_handle_t *)client, NULL);
    }
}

int main()
{
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3333, &addr);

    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    int r = uv_listen((uv_stream_t *)&server, 2, on_new_connection);

    if (r)
    {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}