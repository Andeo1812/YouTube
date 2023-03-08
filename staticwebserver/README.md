# Сервер для отдачи статики
## Архитектура и ЯП
`С++ thread pool`

## Сборка
nginx запускается на `8888` порту, веб-сервер на `8080`.  
важно проверить, чтобы порты были свободны!  
### Запуск сервера
```bash
make build-docker
make docker-Run
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
in proccess
```
## Запуск нагрузочного тестирования  
1. **nginx сервер** 
```bash
make nginx-bench
```
Результат:  
```bash
in proccess
```
2. **static-web-server**
```bash
make bench-static-web-server
```
Результат:  
```bash
in proccess
```
