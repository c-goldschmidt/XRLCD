# X-Rebirth CLD Panel

This little mod + tool will show X-Rebirth stats on a logitech lcd paenl (currently only mono). 
next to the console application there should be a settings.ini containing the logfile path:

```ini
[main]
logfile=<logfile path>
```

The tool currently only shows shield, hull and player money. to do this, the log needs to be activated (see [this](http://www.egosoft.com:8292/confluence/pages/viewpage.action?pageId=30113925))

To build the executable, you'll need the logitech lcd sdk, obtainable [here](http://gaming.logitech.com/de-de/developers). just extract the `lib` and `include` next to the `src` directory...