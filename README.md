# Hooks

Хуки для EDR в ВКР. Тесты и так далее

## Описание файлов
Dll_injector - директория с основными частями проекта
  - dll - DLL с хуком на OpenProcess
  - injector - DLL-инжектор
  - test_program - программа для тестов
  - production_mv - прокачанная версия проги для тестов, обязательно собирать через cl: `cl.exe test.cpp /MT kernel32.lib /Iinclude`
