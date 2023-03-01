[Визитная карточка команды](https://github.com/Legendary2/GB_CommandProgCPP_team3/wiki)

[Инструкция по развертыванию ПО "THare](https://github.com/Legendary2/GB_CommandProgCPP_team3/edit/main/README.MD#%D0%B8%D0%BD%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%86%D0%B8%D1%8F-%D0%BF%D0%BE-%D1%80%D0%B0%D0%B7%D0%B2%D0%B5%D1%80%D1%82%D1%8B%D0%B2%D0%B0%D0%BD%D0%B8%D1%8E-%D0%BF%D0%BE-thare)

[Правила работы с репозиторием](https://github.com/Legendary2/GB_CommandProgCPP_team3/edit/main/README.MD#%D0%BF%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%B0-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D1%8B-%D1%81-%D1%80%D0%B5%D0%BF%D0%BE%D0%B7%D0%B8%D1%82%D0%BE%D1%80%D0%B8%D0%B5%D0%BC)

[Рабочий процесс команды №3](https://drive.google.com/file/d/1KAaR9hctvW2iiWwgqO0asiC_NJ4L_I4n/view?usp=share_link)

[Release Notes](https://github.com/Legendary2/GB_CommandProgCPP_team3/releases/tag/v.0.1.0)

# 1. Инструкция по развертыванию ПО "THare".
## 1.1 Требуемое ПО
Для корректной сборки проекта на рабочей станции должно быть предуставновлено следующее ПО:
### Linux Ubuntu 18.04:
1. Qt v6.2.4 LTS.
2. Git v2.39.2.
3. CMake v3.26.

### Windows 10:
1. Qt v6.2.4 LTS.
2. Git v2.39.2.
3. CMake v3.26.

## 1.2 Установка ПО
### Linux Ubuntu 18.04:
1. Qt v6.2.4 LTS

https://docs.google.com/document/d/1kM6dwnTYJyXO_quz3wDepJl7CVUYDPrBvn453UYi1zo/edit

2. Git v2.39.2

https://git-scm.com/download/linux

3. CMake

https://cmake.org/install/

### Windows 10:
1. Qt v6.2.4 LTS

https://rutracker.org/forum/viewtopic.php?t=6196654 (для доступа может потребоваться VPN в браузере)

2. Git v2.39.2

https://git-scm.com/download/win

3. CMake

https://cmake.org/install/

## 1.3 Развертывание проекта
1.3.1 Для того чтобы развернуть проект на вашей системе, в первую очередь требуется склонировать удаленный репозиторий команды.
```
git clone (http репозитория, либо ssh(у кого настроен))
```
1.3.2 На ветке `main` находится актуальный рабочий релиз, который требуется запустить через QtCreator
![image](https://user-images.githubusercontent.com/78610228/220890872-9cc25359-4a32-40b5-9587-f43309324ba1.png)

1.3.3 Для сборки проекта под Linux компилятор выбираем по умолчанию.
![image](https://user-images.githubusercontent.com/78610228/220891243-f30672eb-76c7-42a0-b9d5-7cddc0c7dca7.png)

1.3.4 Для сборки проекта под Windows выбираем компилятор MSVC.
![image](https://user-images.githubusercontent.com/78610228/220891376-5fb55256-802e-4473-b8d6-c1af8b86f7d6.png)

1.3.4.1 Для проекта на Windows также может понадобится дополнительно скачать сборщик проекта [Ninja](https://drive.google.com/file/d/17m5o9hbwFz5loNbDy6oWGuOKzn1AGMfn/view?usp=share_link) и добавить его в директорию Qt. Затем необходимо добавить путь до файла .exe в переменную среды Windows `PATH`.

1.3.5 Проект готов к работе
![image](https://user-images.githubusercontent.com/78610228/220892078-296232dc-3d29-480a-be4a-09ed384ebad9.png)

# 2. Правила работы с репозиторием
###
2.1 Клонируем репозиторий на локальный компьютер командой:

```
git clone (http репозитория, либо ssh(у кого настроен))
```
http(ssh) берется на главной странице репозитория, нужно нажать зеленую кнопку `Code` и скопировать оттуда http(ssh.
###

2.2 Переходим через консоль `Git bash` в папку со склонированным репозиторием и выполняюм следующую команду для перехода на ветку `develop`:
```
git checkout develop
```
###
2.3 Далее выполняем синхронизацию с удаленным репозиторием, вводя следующие команды:
```
git fetch
git pull
```
Команды `fetch` и `pull` требуется выполнять каждый раз при начале работы с веткой.
###
2.4 Переходим на локальную рабочую ветку.
Если ветка не существует, создаем ее следующее командой:
```
git checkout -b название_ветка
```
Если она существует, осуществляем на нее переход как обычно:
```
git checkout название_ветки
```
###

2.5 Закончив работу на ветке и убедившись в том, что все сделано правильно, добавляй файлы в проект командами:

```
git add .
git commit -m 'Содержание коммита`
```
###
2.6 Далее выполняется загрузка изменений на удаленный репозиторий.
Если ветка на удаленном репозитории не существует, выполняем следующую команду:
```
git push -u origin название_ветки
```
Если ветка уже существует на удаленном репозитории, то выполняем следующую команду
```
git push
```
