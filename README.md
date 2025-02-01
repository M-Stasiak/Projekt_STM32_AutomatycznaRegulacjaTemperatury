# Projekt STM32 Automatyczna Regulacja Temperatury 🌡️

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/) [![MIT License](https://img.shields.io/badge/Language-C-blue)](https://pl.wikipedia.org/wiki/C_(j%C4%99zyk_programowania)) [![MIT License](https://img.shields.io/badge/Platform-STM32H7-orange)](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html) [![STM32CubeIDE](https://img.shields.io/badge/IDE-STM32CubeIDE%201.17.0-lightblue)](https://www.st.com/en/development-tools/stm32cubeide.html)

Projekt implementuje automatyczny system regulacji temperatury oparty na regulatorze PID. Do sterowania wykorzystano mikrokontroler STM32 na płytce Nucleo H755ZI-Q. System monitoruje temperaturę i dynamicznie dostosowuje parametry sterowania, zapewniając stabilność i precyzję.


## 📜 Licencja

Ten projekt jest objęty licencją [MIT License](LICENSE).

**Uwaga:** Jest to projekt edukacyjny, stworzony wyłącznie do celów nauki i nieprzeznaczony do komercyjnego wykorzystania.

## 🛠️ Sprzęt i komponenty

- **Płytka rozwojowa:** NUCLEO H755ZI-Q - główny element sterujący systemu. 
- **Czujnik temperatury:** LM35 - analogowy czujnik temperatury z liniową charakterystyką 10mV/°C.
- **Rezystor:** 5W 47Ω – pełniący rolę obciążenia termicznego, zasilany napięciem 12V.
- **Tranzystory:** Sterujące rezystorem przy użyciu sygnału PWM.
- **Dioda LED:** Wskaźnik pracy układu.
- **Wyświetlacz LCD I2C:** Prezentujący informacje o temperaturze, zadanej temperaturze i wartościach PWM.
- **Potencjometr i przycisk:** Umożliwiające zmianę wartości zadanej temperatury przez użytkownika.

## 🚀 Funkcjonalności systemu
- Odczyt temperatury z czujnika LM35 z okresem próbkowania 10Hz.
- Implementacja regulatora PID do automatycznej regulacji temperatury.
- Komunikacja UART do przesyłania danych między systemem a innymi urządzeniami.
- Wyświetlanie informacji na wyświetlaczu LCD: aktualna temperatura, zadana temperatura, wartość PWM.
- Umożliwienie użytkownikowi ustawienia zadanej temperatury za pomocą potencjometru i przycisku.
