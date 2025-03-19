.DSEG			;начало сегмента данных
.ORG 0x0076		;установка адреса ОЗУ равным 0x0076
ARRAY:.BYTE 5		;резервируем 5 байт для массива ARRAY
.CSEG			;начало программного сегмента
LDI R16, 5			;максимальное количество повторений цикла
LDI R17, 0xCD		;пересылаем число
LDI R30, low(ARRAY)	;младший байт адреса массива ARRAY
LDI R31, high(ARRAY)	;старший байт адреса массива ARRAY
LOOP:			;метка начала тела цикла
ST Z, R17	;занесение числа CD в текущий байт массива ARRAY
INC R30		;адрес следующего байта массива ARRAY
DEC R16		;счетчик числа проходов -1 шаг
BRNE LOOP	;повторить, если счетчик проходов не равен нулю
STOP:			;метка конца программы
JMP STOP		;б/у переход к метке STOP
