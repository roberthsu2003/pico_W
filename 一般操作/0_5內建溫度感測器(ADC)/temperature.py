from machine import WDT

#取得目前日期

wdt = WDT(timeout=2000)
wdt.feed()