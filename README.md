# YouTube

HighLoad system project

## Содержание

* ### [Тема и целевая аудитория](#1)
* ### [Расчет нагрузки](#2)
* ### [Логическая схема](#3)
* ### [Физическая схема](#4)
* ### [Технологии](#5)
* ### [Схема проекта](#6)
* ### [Список серверов](#7)
* ### [Источники](#8)

## 1. Тема и целевая аудитория <a name="1"></a>

**YouTube** — видеохостинг, предоставляющий пользователям услуги воспроизведения, хранения,
комментирования, оценивания видео.

### MVP

- Просмотр видео
- Регистрация
- Рекомендаций видео
- Загрузка видео
- Комментирование видео
- Лайки

### Целевая аудитория

( Из ссылок убрать убрать косвенные статьи сразу отсылать к первоисточнику)

[Статистика](https://xmldatafeed.com/statistika-youtube-stoimost-aktivnye-polzovateli-luchshie-kanaly-i-tendenczii-2022/)
(доп. источники [источник](https://www.businessofapps.com/data/youtube-statistics/),
[источник](https://ictnews.uz/03/11/2022/youtube/))
показывают, что более 2,6 миллиардов активных пользователей в месяц

В связи с отсутствием данных примем допущение о DAU на
основе [данных](https://www.statista.com/statistics/256896/frequency-with-which-us-internet-users-visit-youtube/).
98% - 2600 млн, а DAU - 62% - 1644 млн. То есть примем пропорцию между DAU и MAU для всех стран на основе соотношении
этих параметров для 1 страны - США

В целях упрощения CDN возьмем только топ-3 страны с количеством пользователей онлайн

| **Страна** | **Количество пользователей в месяц, млн** |
|------------|-------------------------------------------|
| India      | 467                                       |
| USA        | 240                                       |
| Indonesia  | 127                                       |

Месячная аудитория с упрощением:

> 467 + 240 + 127 = 834 млн

Промасштабируем дневную аудиторию с упрощением:

> 834 / 2600 * 1644 = 524 млн

## 2. Расчет нагрузки <a name="2"></a>

### Продуктовые метрики

* Месячная аудитория - 834 млн
* Дневная аудитория - 524 млн
* Усредненные метрики:

(Рассмотреть метрики сколько 1 пользователь смотрит 1 видео)

Хранилище пользователя: аватар и личные данные - 15 КБ + 5 КБ = 20 [КБ]

Картинки в webp ужимаются до такого порядка и немного данных о пользователе

[Пользовтаели тратят 23,2 часа в месяц на просмотр видео.](https://lpgenerator.ru/blog/2021/10/07/statistika-youtube-kotoruyu-nuzhno-znat-v-2021/#:~:text=YouTube%20%E2%80%94%20%D0%BB%D1%83%D1%87%D1%88%D0%B5%D0%B5%20%D0%BF%D1%80%D0%B8%D0%BB%D0%BE%D0%B6%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%B4%D0%BB%D1%8F%20%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9%20%D0%BF%D0%B5%D1%80%D0%B5%D0%B4%D0%B0%D1%87%D0%B8%20%D0%B2%D0%B8%D0%B4%D0%B5%D0%BE.%20%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B8%D0%B9%20%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%20%D1%82%D1%80%D0%B0%D1%82%D0%B8%D1%82%2023%2C2%20%D1%87%D0%B0%D1%81%D0%B0%20%D0%B2%20%D0%BC%D0%B5%D1%81%D1%8F%D1%86%20%D0%BD%D0%B0%20%D0%BF%D1%80%D0%BE%D1%81%D0%BC%D0%BE%D1%82%D1%80%20%D0%BA%D0%BE%D0%BD%D1%82%D0%B5%D0%BD%D1%82%D0%B0)

> 23,2 * 60 / 30 = 46,4 [мин/день] - просмотры

[Cредняя длительность видео на YouTube 8.4 минуты.](https://exlibris.ru/news/statistika-youtube-2019-infografika/#:~:text=%D0%9F%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D0%B8%20%D1%81%D0%BC%D0%BE%D1%82%D1%80%D1%8F%D1%82%20%D0%B2%D0%B8%D0%B4%D0%B5%D0%BE%20%D0%BA%D0%B0%D0%B6%D0%B4%D1%8B%D0%B9%20%D0%B4%D0%B5%D0%BD%D1%8C&text=%D0%92%20%D1%81%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BC%20%D0%BD%D0%B0%20%D0%BA%D0%B0%D0%B6%D0%B4%D0%BE%D0%B3%D0%BE%20%D1%87%D0%B5%D0%BB%D0%BE%D0%B2%D0%B5%D0%BA%D0%B0,%D0%BF%D0%BE%D1%8D%D1%82%D0%BE%D0%BC%D1%83%20%D1%81%D1%80%D0%B5%D0%B4%D0%BD%D0%B8%D0%B5%20%D0%BF%D0%BE%D0%BA%D0%B0%D0%B7%D0%B0%D1%82%D0%B5%D0%BB%D0%B8%20%D1%82%D0%B0%D0%BA%D0%B8%D0%B5%20%D0%B2%D0%BF%D0%B5%D1%87%D0%B0%D1%82%D0%BB%D1%8F%D1%8E%D1%89%D0%B8%D0%B5.)

> 46.4 / 8.4 = 5.5 [штук] - видео просматривает один пользователь за сутки

[Пользователи в среднем ставят 4 лайка на 100 видео.](https://tubularlabs.com/blog/3-metrics-youtube-success/#:~:text=Tips%20for%20YouTube%20Success%3A%20Aim%20for%20at%20least%2040%20Likes%20for%20every%201000%20views%20of%20your%20video)

> 5.5 * 30 = 165 [штук] - среднее число просмотров в месяц
>
> 165 / 100 * 4 = 6 [штук/месяц] - лайков в месяц ставит пользователь

[Пользователи в среднем оставляют 5 комментариев на 1000 видео.](https://tubularlabs.com/blog/3-metrics-youtube-success/#:~:text=Tips%20for%20YouTube%20Success%3A%20Aim%20for%20at%20least%205%20comments%20for%20every%201000%20video%20views)

> 165 / 1000 * 5 = 1 [штук] - комментариев оставляет пользователь в месяц

[Пользователи в среднем загружают 500 видео в минуту](https://exlibris.ru/news/statistika-youtube-2019-infografika/#:~:text=500%20%D1%87%D0%B0%D1%81%D0%BE%D0%B2%20%D0%B2%D0%B8%D0%B4%D0%B5%D0%BE%20%D0%B7%D0%B0%D0%B3%D1%80%D1%83%D0%B6%D0%B0%D0%B5%D1%82%D1%81%D1%8F%20%D0%BD%D0%B0%20YouTube%20%D0%BF%D0%BE%20%D0%B2%D1%81%D0%B5%D0%BC%D1%83%20%D0%BC%D0%B8%D1%80%D1%83%20%D0%B2%D1%81%D0%B5%D0%B3%D0%BE%20%D0%B7%D0%B0%20%D0%BC%D0%B8%D0%BD%D1%83%D1%82%D1%83.)

> 500 * 60 * 24 * 30 = 21 600 000 [штук/месяц] - загруженных видео в месяц
>
> 21 600 000 * 834 / 2600 = 6 928 615 [штук/месяц] - загруженных видео в месяц с учетом упрощения по CDN (см. выше)
>
> 6 928 615 / 834 000 000 = 0,008 [штук/месяц] - видео в месяц загружает 1 пользователь
>
> 165 / 0,008 = 20625 - раз поток просмотра превышает поток загрузок видео

Таблица действий - число операций в месяц для одного пользователя:

| **Действие**      | **Среднее количество в месяц [штук]** |
|-------------------|---------------------------------------|
| Лайк              | 6                                     |
| Комментарий       | 1                                     |
| Просмотрено видео | 165                                   |
| Загружено видео   | 0,008                                 |

### Технические метрики

#### Размер хранения

#### Видео

[1 час видео весит 8 Гб для 1080p.](https://7youtube.ru/news/skolko-vesit-video.html#:~:text=%D0%92%D1%81%D0%B5%20%D0%B2%D0%BF%D0%BE%D0%BB%D0%BD%D0%B5%20%D0%BB%D0%BE%D0%B3%D0%B8%D1%87%D0%BD%D0%BE%20%E2%80%93%20%D1%82%D0%B0%D0%BA%D0%B8%D0%B5%20%D1%84%D0%B0%D0%B9%D0%BB%D1%8B%20%D0%B8%D0%BC%D0%B5%D1%8E%D1%82%20%D0%B8%D0%B4%D0%B5%D0%B0%D0%BB%D1%8C%D0%BD%D0%BE%D0%B5%20%D1%81%D0%BE%D0%BE%D1%82%D0%BD%D0%BE%D1%88%D0%B5%D0%BD%D0%B8%D1%8F%20%E2%80%93%20%D0%B2%D0%B5%D1%81/%D0%BA%D0%B0%D1%87%D0%B5%D1%81%D1%82%D0%B2%D0%BE.%20%D0%94%D0%BB%D1%8F%20%D0%B1%D1%8B%D1%81%D1%82%D1%80%D0%BE%D0%B3%D0%BE%20%D0%BF%D0%BE%D1%82%D0%BE%D0%BA%D0%BE%D0%B2%D0%BE%D0%B3%D0%BE%20%D0%B2%D0%BE%D1%81%D0%BF%D1%80%D0%BE%D0%B8%D0%B7%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D1%8F%20%E2%80%93%20%D1%8D%D1%82%D0%BE%20%D0%B8%D0%B4%D0%B5%D0%B0%D0%BB%D1%8C%D0%BD%D0%BE%D0%B5%20%D1%80%D0%B5%D1%88%D0%B5%D0%BD%D0%B8%D0%B5.)

> 6 928 615 / 30 = 32 333 [ГБ] - в сутки
>
> 32 333 * 30 = 970 006 [ГБ] - в месяц
>
> 970 006 * 12 = 11 367 [ПБ] - за год
>
> 11 367 * 5 = 58 836 [ПБ] - за 5 лет
>
> 58 836 * 2 = 113 672 [ПБ] - с учетом сохранности данных и других причин, нужно хранить в 2 экземплярах по меньшей мере.

#### RPS в разбивке по типам запросов

Примем сценарий использования сервиса, по которому пользователи выбирают видео для просмотра двумя способами:

1. С главной страницы с рекомендациями: home page -> video
2. 2 Через поиск:                       home page -> search -> video

Таблица - число запросов при загрузке конкретной страницы для 1 пользователя: (добавить логин, регистрацию)

Будем отдельно вести учет работы WEB-сервера и Backend. 
Т.к. приложение в 99% случаев имеет дело с публичным данными и их можно отдать WEB-сервером. WEB-сервер в данном понимании 
это отдача статики в 100% случаев. Backend - имеется ввиду именно API.
Ввести конкретику по API (упростить и задать конкретно что к чему)

(Проконтролировать статику детальнее)

| **Страница**                | **Число запросов** | **к API** | **За статикой** |
|-----------------------------|--------------------|-----------|-----------------|
| Home page + recommendations | 91                 | 11        | 80              |
| Search                      | 23                 | 1         | 23              |
| Video                       | 100                | 6         | 94              |
| Load video                  | 2                  | 2         | 0               |

Примем сценарий использования сервиса, по которому пользователь смотрит видео 4 раза из главной страницы - рекомендаций
и 2 раза через поиск. 

(Переделать от общих запросов к конкретно статике)

1. С главной страницы

Всего запросов:

> 91 + 100 = 191 - запросы к главной странице + видео
>
> 191 * 4 = 764 - за 4 видео
>
> 764 * 524 = 400 336 [зап/сутки млн]

Запросы на бэк:

> 11 + 6 = 17 Запросов на бэк для просмотра одного видео с главной страницы
>
> 17 * 4 = 68 - за 4 видео
>
> 68 * 524 = 35 621 [зап/сутки млн]

2. Через поиск

Всего запросов:

> 91 + 23 + 100 = 214 Для просмотра одного видео через поиск
>
> 214 * 2 = 428 - за 2 видео
>
> 428 * 524 = 224 272 [зап/сутки млн]

Запросы на бэк:

> 11 + 1 + 6 = 18 Запросов на бэк для просмотра одного видео с помощью поиска
>
> 18 * 2 = 36 - за 2 видео
>
> 36 * 524 = 18 864 [зап/сутки млн]

##### Запросы на WEB-server

> 400 336 + 224 272 = 624 608 [зап/сутки млн]
>
> 624 608 / (24 * 60 * 60) = 7 229 259 [RPS]

##### Запросы на бэк

> 35 621 + 18 864 = 54 485 [зап/сутки млн]

> 54 485 / (24 * 60 * 60) = 630 613 [RPS]

#### Лайки, комментарии, загрузки

> 524 * 5.5 = 2882 [видео/сутки млн]

> 2882 млн * 4% = 115,28 [лайки/сутки млн]
>
> 115,28 млн / (24 * 60 * 60) = 1334 [RPS]

> 2882 млн * 0.5% = 14,41 [комментариев/сутки млн]
>
> 3.355 млн / (24 * 60 * 60) = 166 [RPS]


> 6 928 615 / 30 / 24 / 60 / 60 = 2,67 = 3 [видео/сутки] - на загрузку
>
> 3 * 2 = 6 RPS.

#### Суммарный RPS:

> 630 613 + 1334 + 166 + 6 = 632 119 [RPS] - на бэк
>
> 7 229 259 + 1334 + 166 + 6 = 7 230 765 [RPS] - на WEB-server

(WEB-server - Backend = 7 230 765 - 632 119)

| **Действие** | **RPS**   |
|--------------|-----------|
| WEB-server   | 7 230 765 |
| Backend      | 632 119   |

## 3. Логическая схема <a name="3"></a>

In process...
