# Сервер для отдачи статики

## Архитектура и ЯП

`С++ thread pool`

## Сборка

nginx запускается на `8888` порту, веб-сервер на `8080`.  
важно проверить, чтобы порты были свободны!

### Запуск сервера

```bash
make build-docker
make docker-run
```

Остановка сервера:

```bash
make docker-stop
```

Удаление контейнера(чтобы запустить новый):

```bash
make docker-rm
```

### Запуск nginx

```bash
make build-docker-nginx
make docker-Run-nginx
```

Остановка nginx(a):

```bash
make docker-stop-nginx
```

Удаление контейнера nginx(a)(чтобы запустить новый):

```bash
make docker-rm-nginx
```  

### Запуск функциональных тестов

```bash
make func-test
```

Результат:

```bash
./functest.py
test_directory_index (__main__.HttpServer)
directory index file exists ... ok
test_document_root_escaping (__main__.HttpServer)
document root escaping forbidden ... ok
test_empty_request (__main__.HttpServer)
Send empty line ... ok
test_file_in_nested_folders (__main__.HttpServer)
file located in nested folders ... ok
test_file_not_found (__main__.HttpServer)
absent file returns 404 ... ok
test_file_type_css (__main__.HttpServer)
Content-Type for .css ... ok
test_file_type_gif (__main__.HttpServer)
Content-Type for .gif ... ok
test_file_type_html (__main__.HttpServer)
Content-Type for .html ... ok
test_file_type_jpeg (__main__.HttpServer)
Content-Type for .jpeg ... ok
test_file_type_jpg (__main__.HttpServer)
Content-Type for .jpg ... ok
test_file_type_js (__main__.HttpServer)
Content-Type for .js ... ok
test_file_type_png (__main__.HttpServer)
Content-Type for .png ... ok
test_file_type_swf (__main__.HttpServer)
Content-Type for .swf ... ok
test_file_urlencoded (__main__.HttpServer)
urlencoded filename ... ok
test_file_with_dot_in_name (__main__.HttpServer)
file with two dots in name ... ok
test_file_with_query_string (__main__.HttpServer)
query string with get params ... ok
test_file_with_slash_after_filename (__main__.HttpServer)
slash after filename ... ok
test_file_with_spaces (__main__.HttpServer)
filename with spaces ... ok
test_head_method (__main__.HttpServer)
head method support ... ok
test_index_not_found (__main__.HttpServer)
directory index file absent ... ok
test_large_file (__main__.HttpServer)
large file downloaded correctly ... ok
test_post_method (__main__.HttpServer)
post method forbidden ... ok
test_request_without_two_newlines (__main__.HttpServer)
Send GET without to newlines ... ok
test_server_header (__main__.HttpServer)
Server header exists ... ok

----------------------------------------------------------------------
Ran 24 tests in 0.096s

OK
```

## Запуск нагрузочного тестирования

[Инструмент](https://github.com/wg/wrk)

Все тесты проведены в Docker c ограничением использования оперативной памяти в 2 GB

1. **nginx сервер - worker_processes 4**

```bash
make nginx-bench
```

Результат:

```bash
wrk -t12 -c400 -d30s 'http://127.0.0.1:8888/tests/splash.css'
Running 30s test @ http://127.0.0.1:8888/tests/splash.css
  12 threads and 400 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    77.12ms  111.50ms 520.43ms   81.84%
    Req/Sec     2.26k     1.50k   10.19k    52.61%
  559871 requests in 30.09s, 51.55GB read
Requests/sec:  18604.93
Transfer/sec:      1.71GB

```

2. **static-web-server - thread pool 16**

```bash
make bench-static-web-server
```

Результат:

```bash
wrk -t12 -c400 -d30s 'http://127.0.0.1:8080/tests/splash.css'
Running 30s test @ http://127.0.0.1:8080/tests/splash.css
  12 threads and 400 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   232.06ms  327.64ms   1.84s    79.82%
    Req/Sec     1.17k   452.85     3.36k    67.21%
  417713 requests in 30.09s, 38.42GB read
  Socket errors: connect 0, read 0, write 0, timeout 198
Requests/sec:  13880.40
Transfer/sec:      1.28GB

```

3. **Сравнительный анализ**

> 13880.40 / 18604.93 * 100 = 74.6 [%] - дает кастомный веб сервер по сравнению c Nginx

4. **Динамика роста - RPS/count_workers**

| **Count workers** | **Nginx [RPS]** | **Static WEB server [RPS]** |
|-------------------|-----------------|-----------------------------|
| 4                 | 17775.54        | 14432.26                    |
| 8                 | 18826.28        | 14362.46                    |
| 16                | 17169.51        | 14300.69                    |